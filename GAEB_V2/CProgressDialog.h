#pragma once
#include "afxdialogex.h"


// CProgressDialog dialog

class CProgressDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CProgressDialog)

public:
	CProgressDialog(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CProgressDialog();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PROGRESS };
#endif

	void SetMessage(const CString& msg);
	void SetProgress(int percent);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	CStatic m_msgCtrl;
	CProgressCtrl m_progressCtrl;

	DECLARE_MESSAGE_MAP()
};
