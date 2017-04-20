//StreamMediaPlayer:

#pragma once

#ifdef STREAMMEDIAPLAYER_EXPORTS
#define AJB_SMP_API extern "C" __declspec(dllexport)
#else
#define AJB_SMP_API extern "C" __declspec(dllimport)
#endif

//���󷵻���
#define ERR_IPC_CONNECT								0xf0000000 // IPC����ʧ��
#define ERR_IPC_URL									0xf0000001 // IPC��Դ·������
#define ERR_IPC_AUTHORIZE							0xf0000002 // IPC��֤ʧ��

typedef int (__stdcall *CALLBACK_DIRECTION)(int direction, void *pParam);

AJB_SMP_API long AJB_SMP_GetHandle();
AJB_SMP_API void AJB_SMP_CloseHandle(long handle);
AJB_SMP_API int AJB_SMP_Play(long handle, const char* url, const char* username, const char* pswd, HWND hWnd);
AJB_SMP_API int AJB_SMP_Stop(long handle);
AJB_SMP_API int AJB_SMP_SnapShot(long handle, const char* path);
AJB_SMP_API int AJB_SMP_Record(long handle, bool bRecord = true, const char* pathname = NULL);
AJB_SMP_API int AJB_SMP_SetCallback_direction(int handle, CALLBACK_DIRECTION pfn, void* pParam);
AJB_SMP_API int AJB_SMP_SetDirArea(long handle, const RECT& rc);