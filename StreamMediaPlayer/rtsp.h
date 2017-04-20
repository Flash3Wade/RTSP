//rtsp.h:

#pragma once

#include "socket.h"
#include <string>
#include <map>
#include <process.h>
using namespace std;

typedef enum
{
	RTSP_REQUEST_TYPE_OPTIONS = 0,
	RTSP_REQUEST_TYPE_DESCRIBE,
	RTSP_REQUEST_TYPE_SETUP,
	RTSP_REQUEST_TYPE_PLAY,
	RTSP_REQUEST_TYPE_PAUSE,
	RTSP_REQUEST_TYPE_TEARDOWN,
}RTSP_REQUEST_TYPE;

class CRtspClient
{
public:
	CRtspClient();
	~CRtspClient();

public:
	int ConnectSrv(const char* url);
	//bool ConnectSrv(const char* ip, int port);
	bool Authorize(const char* username, const char* pswd);
	bool BeginStream();
	bool EndStream();
	int GetStreamData(char* buf, int len);

protected:
	int SendRequest(RTSP_REQUEST_TYPE eType);
	int RecvResponse(RTSP_REQUEST_TYPE eType);
	int ParseHeader(const char* pHeader, map<string,string>& mapHeader);
	int ParseUrl(const char* url, char* ip, int& port);

	friend void thread_keepalive(void* pParam); //ÿ1s����һ��������

private:
	CIntractSocket* m_pIntract; //�����׽���

	int m_nSeq; //�������к�
	bool m_bNeedAuth;//��֤��־

	bool m_bWorking;
	HANDLE m_hThread_keepalive;

	//������IP��ַ���˿ںš���Դ·��
	char m_szIp[16];
	int m_nPort; 
	char m_szUrl[128]; 

	//��֤�����û���������
	char m_szName[32];
	char m_szPswd[32];

	//DESCRIBE�������ص��������������������֤��ͨ�������ڽ�������
	char m_szNonce[64];
	char m_szRealm[64];
	char m_szTrack[64];

	//SETUP�������صĻỰ��
	char m_szSession[64];
};