#pragma once


// CRTSPDialog �Ի���

class CRTSPDialog : public CDialog
{
	DECLARE_DYNAMIC(CRTSPDialog)

public:
	CRTSPDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CRTSPDialog();

// �Ի�������
	enum { IDD = IDD_DIALOG_AUTHORIZE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	char m_szUser[32];
	char m_szPswd[32];
};
