#pragma once
#include "afxcmn.h"


// CSelectIpcDialog �Ի���
#define IPC_DIALOG_TYPE_SELECT 1
#define IPC_DIALOG_TYPE_DELETE 2

class CSelectIpcDialog : public CDialog
{
	DECLARE_DYNAMIC(CSelectIpcDialog)

public:
	CSelectIpcDialog(int type, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSelectIpcDialog();

// �Ի�������
	enum { IDD = IDD_DIALOG_SELECTIPC };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
private:
	CListCtrl m_ListCtrl;
	int m_type;
public:
	afx_msg void OnNMDblclkListIpc(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedDelete();
};
