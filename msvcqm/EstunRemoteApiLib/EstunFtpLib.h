#ifndef __ESTUNFTPLIB_H__
#define __ESTUNFTPLIB_H__

#include "EstunRemoteApiLib_global.h"
#include "EstunRemoteApiLib_struct.h"
using namespace EstunRobot;

struct ESTUNREMOTEAPILIBAPI FtpFileInfo
{
	FtpFileInfo()
	{
		name = "";
		isFolder = false;
	}

	FtpFileInfo(const FtpFileInfo& t)
	{
		this->name = t.name;
		this->isFolder = t.isFolder;
	}

	FtpFileInfo& operator = (const FtpFileInfo& t)
	{
		if (this != &t)
		{
			this->name = t.name;
			this->isFolder = t.isFolder;
		}
		return *this;
	}

	//�ļ�����
	ESString name;
	//�Ƿ���Ŀ¼
	bool isFolder;
};

class ESTUNREMOTEAPILIBAPI EstunFtpLib
{
public:
	EstunFtpLib();
	~EstunFtpLib();

	/**
	 * ����Ftp����.
	 * 
	 * \param ip_port ����IP:port
	 * \return �ɹ�����true
	 */
	bool Connect(ESString ip_port);

	/**
	 * �Ͽ�����.
	 * 
	 * \return �ɹ�����true
	 */
	bool DisConnect();

	/**
	 * ���뵽Ŀ¼��������Ŀ¼�޸ĵ���ǰ.
	 * 
	 * \param path Զ��Ŀ¼
	 * \return �ɹ�����true
	 */
	bool EntryFolder(ESString path);

	/**
	 * ��ȡ��ǰԶ��·��.
	 * 
	 * \param char�����ַ���ɵ���������
	 * \param char��������
	 * \return �ɹ�����true
	 */
	bool PWD(char* path, int max);

	/**
	 * ��ȡ�ӵ�ǰĿ¼��ʼ�����·���µ������б�.
	 * 
	 * \param path ���·��
	 * \param infoArray �ļ��б�����ָ�룬������ǰ���ϼ�������
	 * \param infoNum �ļ��б�����Ԫ�ظ���
	 * \return ��ȡ�ɹ�����true
	 */
	bool ListDir(ESString path, FtpFileInfo*& infoArray, int& infoNum);

	/**
	 * ����Զ��·��.
	 * 
	 * \param path ���·��
	 * \return �ɹ�����true
	 */
	bool CreateDir(ESString path);

	/**
	 * ɾ��Զ���ļ�.
	 * 
	 * \param path ���·��
	 * \return �ɹ�����true
	 */
	bool RemoveFile(ESString path);

	/**
	 * ɾ��Զ��Ŀ¼.
	 *
	 * \param path ���·��
	 * \return �ɹ�����true
	 */
	bool RemoveDir(ESString path);

	/**
	 * ��ȡԶ���ļ�������.
	 * 
	 * \param localPath ���ر����ļ�·�������ļ���
	 * \param remotePath Զ���ļ�·��
	 * \return �ɹ�����true
	 */
	bool GetFile(ESString localPath, ESString remotePath);

	/**
	 * ��ȡԶ��Ŀ¼���ݵ�����Ŀ¼.
	 * 
	 * \param localPath ���ر���·��
	 * \param remotePath Զ��·��
	 * \return �ɹ�����true
	 */
	bool GetFolder(ESString localPath, ESString remotePath);

	/**
	 * �ϴ������ļ���Զ��.
	 * 
	 * \param localPath �����ļ�·��
	 * \param remotePath Զ�˱����ļ�·�������ļ���
	 * \return �ɹ�����true
	 */
	bool PutFile(ESString localPath, ESString remotePath);

	/**
	 * �ϴ�����Ŀ¼���ݵ�Զ��Ŀ¼.
	 * 
	 * \param localPath ����·��
	 * \param remotePath Զ�˱���·��
	 * \return �ɹ�����true
	 */
	bool PutFolder(ESString localPath, ESString remotePath);

	/**
	 * ��ȡ���һ��ִ�нӿڴ�����Ϣ.
	 * 
	 * \return ������Ϣ
	 */
	ESString GetLastErr();

private:
	struct EstunFtpLibPrivate;
	EstunFtpLibPrivate* _p;
};

#endif