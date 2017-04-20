
#pragma once
#ifdef IA_API
#else
#define IA_API _declspec(dllimport)
#endif
#include <vector>

typedef struct m_mat
{
	unsigned char* data;
	int rows;
	int cols;
}m_mat;

typedef struct m_Point
{
	int x;
	int y;
}m_Point;

typedef struct m_Rect
{
	int x;
	int y;
	int width;
	int height;
}m_Rect;

typedef struct m_Line
{
	m_Point pt[2];
}m_Line;

/************************************
������
lDetectionHandle��������Ϣ
srcimg������ĵ�ǰ֡ͼƬ
m_Rect ROI������Ȥ����
double mscale:�²�������
int &direction:����Ŀ���Ƴ��ķ��򣬷���1 Ϊ����Ƴ��� ����2Ϊ�ұ��Ƴ�,����3Ϊ�϶��Ƴ�������4Ϊ�¶��Ƴ�������-1��ʾû��Ŀ���Ƴ�����
*˵��:�ж���Ұ���Ƿ���Ŀ���˶�����Ŀ���˶�ʱ����1������Ϊ0��

���ӣ�
m_Rect ROI;
ROI.x = frame.cols/4;
ROI.y =frame.rows/4;
ROI.width =frame.cols*1/2;
ROI.height =frame.rows*1/2;
bool tmpflag=getmoveDirection(lDetectionHandle,  imgdata,ROI, 2,direction);
************************************/
extern "C" IA_API bool __stdcall getmoveDirection(long lDetectionHandle, m_mat srcmat,m_Rect ROI,double mscale,int &direction);
extern "C" IA_API long __stdcall StartgetmoveDirection();
extern "C" IA_API long __stdcall StopgetmoveDirection(long lDetectionHandle);







