// CProgressDialog.cpp : implementation file
//

#include "pch.h"
#include "GAEB_V2.h"
#include "afxdialogex.h"
#include "CProgressDialog.h"


// CProgressDialog dialog

IMPLEMENT_DYNAMIC(CProgressDialog, CDialogEx)

CProgressDialog::CProgressDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PROGRESS, pParent)
{

}

CProgressDialog::~CProgressDialog()
{
}

void CProgressDialog::SetMessage(const CString& msg)
{
	SetDlgItemText(IDC_STATIC_INFO, msg);
}

void CProgressDialog::SetProgress(int percent)
{
	m_progressCtrl.SetPos(percent);
}

void CProgressDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BOOL CProgressDialog::OnInitDialog()
{
	m_progressCtrl.SubclassDlgItem(IDC_PROGRESS_BAR, this);
	m_progressCtrl.SetRange(0, 100);
	m_progressCtrl.SetPos(0);

	CenterWindow(GetParent());
	return true;
}


BEGIN_MESSAGE_MAP(CProgressDialog, CDialogEx)
END_MESSAGE_MAP()


// CProgressDialog message handlers
