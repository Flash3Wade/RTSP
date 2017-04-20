// SelectIpcDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "IPCDirection.h"
#include "SelectIpcDialog.h"
#include "InsertIPCDialog.h"


// CSelectIpcDialog �Ի���

IMPLEMENT_DYNAMIC(CSelectIpcDialog, CDialog)

CSelectIpcDialog::CSelectIpcDialog(int type, CWnd* pParent /*=NULL*/)
	: CDialog(CSelectIpcDialog::IDD, pParent)
{
	m_type = type;
}

CSelectIpcDialog::~CSelectIpcDialog()
{
}

void CSelectIpcDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_IPC, m_ListCtrl);
}

BOOL CSelectIpcDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	if (m_type == IPC_DIALOG_TYPE_SELECT)
	{
		SetWindowText("��ѯIPC");
	}
	else if (m_type == IPC_DIALOG_TYPE_DELETE)
	{
		SetWindowText("ɾ��IPC");
		GetDlgItem(IDC_DELETE)->SetWindowText("ɾ��");
	}

	m_ListCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_ListCtrl.InsertColumn(0, "�к�", LVCFMT_CENTER, 50);
	m_ListCtrl.InsertColumn(1, "IP", LVCFMT_CENTER, 150);
	m_ListCtrl.InsertColumn(2, "����", LVCFMT_CENTER, 300);

	vector<IPCINFO> vctIPC;
	SelectAllIPC(vctIPC);

	for (unsigned int i = 0; i < vctIPC.size(); i++)
	{
		char tmp[10];
		sprintf(tmp,"%d",i+1);
		m_ListCtrl.InsertItem(i,tmp);
		m_ListCtrl.SetItemText(i, 1, vctIPC[i].ip);
		m_ListCtrl.SetItemText(i, 2, vctIPC[i].descibe);
	}

	return true;
}


BEGIN_MESSAGE_MAP(CSelectIpcDialog, CDialog)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_IPC, &CSelectIpcDialog::OnNMDblclkListIpc)
	ON_BN_CLICKED(IDC_DELETE, &CSelectIpcDialog::OnBnClickedDelete)
END_MESSAGE_MAP()


// CSelectIpcDialog ��Ϣ�������

void CSelectIpcDialog::OnNMDblclkListIpc(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;

	POSITION pos = m_ListCtrl.GetFirstSelectedItemPosition();
	int item = m_ListCtrl.GetNextSelectedItem(pos);
	char ip[16];
	IPCINFO info;
	m_ListCtrl.GetItemText(item, 1, ip, sizeof(ip));
	if (SelectIPC(ip, info))
	{
		CInsertIPCDialog dlg(IPC_DIALOG_TYPE_UPDATE);
		memcpy(&dlg.m_IpcInfo, &info, sizeof(IPCINFO));
		if (dlg.DoModal() == IDOK)
		{
			UpdateIPC(dlg.m_IpcInfo.ip, dlg.m_IpcInfo);
			MessageBox("�޸ĳɹ�");
		}
	}
}

void CSelectIpcDialog::OnBnClickedDelete()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_type == IPC_DIALOG_TYPE_SELECT)
	{
		OnOK();
	}
	else if (m_type == IPC_DIALOG_TYPE_DELETE)
	{
		char ip[16];
		POSITION pos = m_ListCtrl.GetFirstSelectedItemPosition();
		while (pos)
		{
			int item = m_ListCtrl.GetNextSelectedItem(pos);
			m_ListCtrl.GetItemText(item, 1, ip, sizeof(ip));
			DeleteIPC(ip);
			m_ListCtrl.DeleteItem(item);
		}
		MessageBox("ɾ���ɹ�");
	}
}
