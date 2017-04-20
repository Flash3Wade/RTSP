
#pragma once
#pragma warning(disable: 4251)
#pragma warning(disable: 4273)

#define AJB_CV_DIR_API_DLL_LIBRARY

#ifdef AJB_CV_DIR_API_DLL_LIBRARY
#define AJB_IVS_API _declspec(dllexport)
#else
#define AJB_IVS_API _declspec(dllimport)
#endif

//////////////////////////////////////////////////////////////////////////////////////
enum emDIRECTION
{
	DIR_UNKNOWN		= 0,  
	DIR_LEFT	    = 1,
	DIR_RIGHT	    = 2,
	DIR_TOP			= 3,
	DIR_BOTTOM		=4
};

// Rect�ṹ��
typedef struct stRect
{
	int left;
	int top;
	int right;
	int down;
	stRect()
	{
		left = top = right = down =0;
	}
	stRect(int _left, int _top, int _right, int _down)
	{
		left = _left;
		top = _top;
		right = _right;
		down = _down;
	}
	stRect operator=(const stRect& r)
	{
		left = r.left;
		right = r.right;
		top = r.top;
		down = r.down;
		return(*this);
	}
}stRect;


typedef void*  AJB_DIR_Handle;                   //�㷨ϵͳȫ�־��

/*****************************************************************************
*
*Description:
*
*		��ʼ���㷨ϵͳ��
*
*Parameters:
*
*		IN    areaParam  �쳣�¼������㷨�Ĳ�����
*
*       IN    algoParam  �˶�Ŀ���⡢����������㷨�Ĳ�����
*
*Return:
*
*       �㷨ϵͳȫ�־����
*
******************************************************************************/

AJB_DIR_Handle AJB_IVS_API AJB_Dir_InitSys();


/*****************************************************************************
*
*Description:
*
*		��������ÿһ֡��Ƶͼ�������������
*
*Parameters:
*
*		IN	  IVS_Handle	   �㷨ϵͳȫ�־����
*
*		IN	  box			   ����Ŀ������
*
******************************************************************************/
void AJB_IVS_API  AJB_Dir_InitParams(const AJB_DIR_Handle IVS_Handle, const stRect& box);


/*****************************************************************************
*
*Description:
*
*		��������ÿһ֡��Ƶͼ�������������
*
*Parameters:
*
*		IN	  IVS_Handle	   �㷨ϵͳȫ�־����
*
*       IN    pColorImage      ����Ϊ24λBGR��ɫͼ�����ݣ��㷨�����ò�ɫͼ����Ϣ�Ա������н�ģ��
*                              ������ͼ�������ڴ�ķֱ��ʱ������㷨��ʼ��ʱ�����ú���AVT_IVSInitSys������AnalyseParam�����õ�������Ƶͼ��ķֱ���һ�¡�
*		IN	  width			   ͼ���ȡ�
*
*		IN	  height		   ͼ��߶ȡ� 
*
*Return:
*		Ŀ����ʧ����
*       0 ===>> ���ԣ�Ŀ���ڳ����ڣ�    1 ===>> �������ʧ    2===>>���Ҳ���ʧ
*       3 ===>> ���϶���ʧ				4 ===>> ��������ʧ
*
******************************************************************************/

int AJB_IVS_API  AJB_Dir_ProcessFrame(const AJB_DIR_Handle IVS_Handle, const BYTE* pColorImage, int width,  int height);


/*****************************************************************************
*
*Description:
*
*		�ͷ��㷨ϵͳ�������ڴ档
*
*Parameters:
*
*		IN	  IVS_Handle	       �㷨ϵͳȫ�־����	
*
******************************************************************************/
void AJB_IVS_API  AJB_Dir_ReleaseSys(AJB_DIR_Handle IVS_Handle);