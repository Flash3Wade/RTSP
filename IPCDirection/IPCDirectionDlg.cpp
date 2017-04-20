
// IPCDirectionDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "IPCDirection.h"
#include "IPCDirectionDlg.h"
#include "RTSPDialog.h"
#include "InsertIPCDialog.h"
#include "SelectIpcDialog.h"
#include "..\\StreamMediaPlayer\StreamMediaPlayer.h"
#pragma comment(lib, "..\\Debug\\StreamMediaPlayer.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CIPCDirectionDlg �Ի���
/////////////////////////////////////////////////////////////////////////////////////////
bool CIPCDirectionDlg::IsCursorInControl(CPoint point, UINT ID)
{
	ClientToScreen(&point);
	CRect rc;
	GetDlgItem(ID)->GetClientRect(rc);
	GetDlgItem(ID)->ClientToScreen(rc);

	if (rc.PtInRect(point))
		return true;

	return false;
}
//////////////////////////////////////////////////////////////////////////////////////////


int __stdcall cb_direction(int direction, void *pParam)
{
	CIPCDirectionDlg* pObj = (CIPCDirectionDlg*)pParam;

	IPCINFO info = {0};
	SelectIPC(pObj->m_szIP, info);
	char ip[16] = {0};

	switch (direction)
	{
	case 1:
		OutputDebugStringA("����\n");
		if (strlen(info.left) == 0)
			return -1;
		strcpy(ip, info.left);
		break;
	case 2:
		OutputDebugStringA("�ҡ�\n");
		if (strlen(info.right) == 0)
			return -1;
		strcpy(ip, info.right);
		break;
	case 3:
		OutputDebugStringA("��\n");
		if (strlen(info.top) == 0)
			return -1;
		strcpy(ip, info.top);
		break;
	case 4:
		OutputDebugStringA("��\n");
		if (strlen(info.bottom) == 0)
			return -1;
		strcpy(ip, info.bottom);
		break;
	default:
		break;
	}

	pObj->play(ip);

	return 0;
}

bool CIPCDirectionDlg::play(const char* ip)
{
	IPCINFO info = {0};
	if (!SelectIPC(ip, info))
		return false;

	int ret = AJB_SMP_Play(m_handle1, info.url, "admin", "admin123", GetDlgItem(IDC_VIDEO)->GetSafeHwnd());
	if (ret != 0)
	{
		if (ret == ERR_IPC_AUTHORIZE)
		{
			CRTSPDialog dlg;
			if (dlg.DoModal() == IDOK)
			{
				AJB_SMP_Play(m_handle1, info.url, dlg.m_szUser, dlg.m_szPswd, GetDlgItem(IDC_VIDEO)->GetSafeHwnd());
				strcpy(m_szIP, ip);
				SetDlgItemText(IDC_EDIT_IP, ip);
				return true;
			}
		}

		return false;
	}

	strcpy(m_szIP, ip);
	SetDlgItemText(IDC_EDIT_IP, ip);
	return true;
}

CIPCDirectionDlg::CIPCDirectionDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIPCDirectionDlg::IDD, pParent)
	, m_bLButtonDown(false)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_handle1 = AJB_SMP_GetHandle();

	AJB_SMP_SetCallback_direction(m_handle1, cb_direction, this);

	CreateXml();
}

CIPCDirectionDlg::~CIPCDirectionDlg()
{
	AJB_SMP_CloseHandle(m_handle1);
}

void CIPCDirectionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CIPCDirectionDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_PLAY, &CIPCDirectionDlg::OnBnClickedButtonPlay)
	ON_BN_CLICKED(IDC_BUTTON_STOP, &CIPCDirectionDlg::OnBnClickedButtonStop)
	ON_COMMAND(ID_INSERT_IPC, &CIPCDirectionDlg::OnInsertIpc)
	ON_COMMAND(ID_SELECT_IPC, &CIPCDirectionDlg::OnSelectIpc)
	ON_COMMAND(ID_DELETE_IPC, &CIPCDirectionDlg::OnDeleteIpc)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// CIPCDirectionDlg ��Ϣ�������

BOOL CIPCDirectionDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CIPCDirectionDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CIPCDirectionDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CIPCDirectionDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

////////////////////////////////////////////////////////////////////////////////////////////////


void CIPCDirectionDlg::OnBnClickedButtonPlay()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	char ip[16] = {0};
	GetDlgItemText(IDC_EDIT_IP, ip, sizeof(ip));
	play(ip);
}

void CIPCDirectionDlg::OnBnClickedButtonStop()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	AJB_SMP_Stop(m_handle1);
}

void CIPCDirectionDlg::OnInsertIpc()
{
	// TODO: �ڴ���������������
	CInsertIPCDialog dlg(IPC_DIALOG_TYPE_INSERT);
	if (dlg.DoModal() == IDOK)
	{
		InsertIPC(dlg.m_IpcInfo);	
		MessageBox("��ӳɹ�");
	}
}

void CIPCDirectionDlg::OnSelectIpc()
{
	// TODO: �ڴ���������������
	CSelectIpcDialog dlg(IPC_DIALOG_TYPE_SELECT);
	dlg.DoModal();
}

void CIPCDirectionDlg::OnDeleteIpc()
{
	// TODO: �ڴ���������������
	CSelectIpcDialog dlg(IPC_DIALOG_TYPE_DELETE);
	dlg.DoModal();
}

void CIPCDirectionDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CDialog::OnLButtonDown(nFlags, point);

	if (IsCursorInControl(point, IDC_VIDEO))
	{
		if (m_bLButtonDown == false)
		{
			m_bLButtonDown = true;
			m_PointDown = point;
		}
	}
}

void CIPCDirectionDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CDialog::OnLButtonUp(nFlags, point);

	if (IsCursorInControl(point, IDC_VIDEO))
	{
		if (m_bLButtonDown)
		{
			m_bLButtonDown = false;
			CRect rc(m_PointDown, point);
			rc.NormalizeRect();
			ClientToScreen(&rc);
			GetDlgItem(IDC_VIDEO)->ScreenToClient(&rc);
			AJB_SMP_SetDirArea(m_handle1, rc);
		}
	}
}

void CIPCDirectionDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	
	if (IsCursorInControl(point, IDC_VIDEO))
	{
		HCURSOR hCur = LoadCursor(NULL, IDC_CROSS);
		SetCursor(hCur);
		if (m_bLButtonDown)
		{
			CClientDC dc(this);
			
			CBrush* pOldBrush = (CBrush*)dc.SelectStockObject(NULL_BRUSH);
			CPen* pPenGreen = new CPen(PS_SOLID, 1, RGB(0,255,0));
			CPen* pOldPen = dc.SelectObject(pPenGreen);
			int oldRop = dc.SetROP2(R2_NOTXORPEN);
			dc.Rectangle(&m_Rect);

			dc.SetROP2(oldRop);
			CRect rc(m_PointDown, point);
			rc.NormalizeRect();
			m_Rect = rc;
			dc.Rectangle(&rc);

			dc.SelectObject(pOldPen);
			dc.SelectObject(pOldBrush);
			delete pPenGreen;
		}
	}

	CDialog::OnMouseMove(nFlags, point);
}
