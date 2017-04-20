
// IPCDirectionDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CIPCDirectionDlg �Ի���
class CIPCDirectionDlg : public CDialog
{
// ����
public:
	CIPCDirectionDlg(CWnd* pParent = NULL);	// ��׼���캯��
	~CIPCDirectionDlg();

// �Ի�������
	enum { IDD = IDD_IPCDIRECTION_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

	bool play(const char* ip);
	friend int __stdcall cb_direction(int direction, void *pParam);
	bool IsCursorInControl(CPoint point, UINT ID);

private:
	long m_handle1;
	char m_szIP[16];
	bool m_bLButtonDown;
	CPoint m_PointDown;
	CRect m_Rect;

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonPlay();
	afx_msg void OnBnClickedButtonStop();
	afx_msg void OnInsertIpc();
	afx_msg void OnSelectIpc();
	afx_msg void OnDeleteIpc();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};
