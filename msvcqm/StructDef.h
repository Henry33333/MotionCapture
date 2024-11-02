#ifndef STRUCTDEF_H
#define STRUCTDEF_H

#include <string.h>

#define X_ERRCODE_MAX    20
#define X_MODE_AUTO      2        /* 自动模式 */
#define X_MODE_MANUAL    3        /* 手动示教模式 */
#define X_MODE_DEBUG     5        /* 调试模式 */
#define X_MODE_AUTOCMD   100      /* 自动命令模式 */

/* POS位置点坐标 */
typedef struct
{
    double X, Y, Z, A, B, C, E1, E2, E3;
} XPOSE;

/* JPOS位置点坐标 */
typedef struct
{
    double J1, J2, J3, J4, J5, J6, E1, E2, E3;
} XJOINT;

typedef struct _XPOINT{
    XPOSE PosData;         /*位姿数据*/
    int   UFNo;            /*用户坐标系编号*/
    int   TFNo;            /*工具坐标系编号*/
    int   Conf[4];         /*形态+旋转数(CFX)*/
}XPOINT;

typedef struct _XMOVPOINTADD{
    int    Vel;              /*速度值*/
    int    Cnt;              /*定位类型(-1:fine; 0~100:cnt)*/
    int    Acc;              /*加速度百分比*/
    int    Dec;              /*减速度百分比*/
    int    Offset;           /*位置补偿(-2:不使用; -1:offset常量; 0~31:offset变量PR编号)*/
    int    TOffset;          /*刀具补偿(-2:不使用; -1:offset常量; 0~31:offset变量PR编号)*/
    int    VisionNum;          /*偏移位置(-1:不使用; 0~7:视觉变量编号)*/
    int    TrackNum;         /*跟踪工艺编号(-1:不使用; 0~7:跟踪工艺编号)*/
    int    Wrist;            /*腕部动作(0:不使用; 1~:腕部动作类型)*/
    int    Inc;              /*增量动作(0:不使用; 1~:使用)*/
    int    Search;              /*搜索动作(0:不使用; 1~:使用)*/
    int    RTCP;             /*RTCP设置(0:不使用; 1~:使用*/
    XPOSE OffsetData;    /*Offset当前点参数*/
    XPOSE TOffsetData;   /*Toffset当前点参数*/

    void DataInit()
    {
        Vel = 100;
        Cnt = 0;
        Acc = 100;
        Dec = 100;
        Offset = -2;
        TOffset = -2;
        VisionNum = -1;
        TrackNum = -1;
        Wrist = 0;
        Inc = 0;
        Search = 0;
        RTCP = 0;
        memset(&OffsetData,0,sizeof(XPOSE));
        memset(&TOffsetData,0,sizeof(XPOSE));
    }
}XMOVPOINTADD;

typedef struct
{
    int ErrLevel;        /*报警等级*/
    int ErrType;         /*报警类别码*/
    int ErrIndex;        /*具体报警码*/
} XSYSERRPARAM;

/*报警信息链表*/
typedef struct
{
    XSYSERRPARAM ErrIndex[X_ERRCODE_MAX];
} XSYSERRINDEX;

/* 系统状态结构体 */
typedef struct
{
    int RunState;        /* 运行状态 */
    int Mode;            /* 系统模式*/
    int InPos;           /* 到位信号 */
    int Err;             /* 错误状态 */
    int Remote;          /* 远程状态 */
    int LinkStat;        /* 通信链接状态 */
    int Enable;          /* 系统使能状态 */
    int CmdQueFull;      /* 运动队列满标识位 */
} XSYSTEMSTATE;

#endif // STRUCTDEF_H