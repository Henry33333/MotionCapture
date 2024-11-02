#include "Worker.h"



Worker::Worker(QObject *parent)
    : QObject(parent)
    , api(nullptr)
{

}

void Worker::setRob(EstunRemoteApiLib *a)
{
    api = a;

}

void Worker::setRes(std::vector<std::vector<QVariant>> r)
{
    res = r;
}


void Worker::on_doSomething()
{
//    int RobHandle = Rob;

//    XSYSTEMSTATE sys;
//    memset(&sys,0,sizeof(XSYSTEMSTATE));
//    XGetSystemState(RobHandle, &sys);

//    XPOINT MPos;
//    memset(&MPos,0,sizeof(XPOINT));
//    XGetWPoint(RobHandle, &MPos); // 初始化


//    XMOVPOINTADD Data;
//    Data.DataInit();
//    Data.Cnt = -1;



//    for (size_t i = 0; i < res.size(); i++)
//    {

//        XGetSystemState(RobHandle, &sys);
//        XWaitCmdSendDone(RobHandle);
//        if (sys.CmdQueFull != 2)
//        {
//            MPos.PosData.X = res[i][0].toDouble();
//            MPos.PosData.Y = res[i][1].toDouble();
//            MPos.PosData.Z = res[i][2].toDouble();

//            MPos.PosData.A = res[i][3].toDouble();
//            MPos.PosData.B = res[i][4].toDouble();
//            MPos.PosData.C = res[i][5].toDouble();

//            //            Data.Vel = ; // 速度待设置100% 250mm/s fps15计算
//            if (i==0)
//            {
//                Data.Vel = 100;
//            }
//            else
//            {
//                double v = 0;
//                v = std::hypot( res[i][0].toDouble()-res[i-1][0].toDouble(), res[i][1].toDouble()-res[i-1][1].toDouble(),res[i][2].toDouble()-res[i-1][2].toDouble());
//                v = v * 15;
//                double percent = v/250*100;
//                if (percent > 100)
//                {
//                    Data.Vel = 100;
//                }
//                else
//                {
//                    Data.Vel = (int)percent;
//                    Data.Vel = Data.Vel+1;
//                }
//            }

//            XMovLAdd(RobHandle, MPos, Data);
//        }
//        else
//        {
//            i--;
//        }
//    }

//    emit resultReady();


    E_ROB_POSCFG cfg;
    api->E_GetCurWPos().GetCfgValue(cfg);
    E_ROB_SPEED vel;
    E_ROB_POS mpos;
    E_ROB_ZONE zone(1, 100, 50, 0);


    int num = res.size()-1;
    int times = num/500;
    int left = num%500;

    Trajectory2Pos points[5][500];

    for (size_t i = 0; i < res.size(); i++)
    {

        mpos = E_ROB_POS(cfg, res[i][0].toDouble(), res[i][1].toDouble(),res[i][2].toDouble(), res[i][5].toDouble(), res[i][4].toDouble(), res[i][3].toDouble());


        if (i==0)
        {
            vel.set_Tcp(200);
        }
        else
        {
            double v = 0;
            v = std::hypot( res[i][0].toDouble()-res[i-1][0].toDouble(), res[i][1].toDouble()-res[i-1][1].toDouble(),res[i][2].toDouble()-res[i-1][2].toDouble());
            v = v * 45;

            vel.set_Tcp(v);
        }

//        api->E_MovL2(mpos, vel);

        points[i/500][i%500].payloadId = 0;
        points[i/500][i%500].coordId = 0;
        points[i/500][i%500].toolId = 0;
        points[i/500][i%500].m_zone = zone;
        points[i/500][i%500].m_Pos = mpos;
        points[i/500][i%500].m_speed = vel;

    }

    for (int j = 0; j <= times; j++)
    {

        if (j == times)
        {
            api->E_MovL2_Trajectory2(points[j],left+1,1, E_ROB_APIBUFF(),0.0,true);
        }
        else
        {
            api->E_MovL2_Trajectory2(points[j],500,1, E_ROB_APIBUFF(),0.0,true);
        }

    }





    emit resultReady();
}
