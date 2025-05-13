#include "pch.h"
#include "CAuftragsnehmer.h"


#include "GAEB_V2Doc.h"
#include "GAEB_V2View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include <vector>

using namespace std;


#define IDC_STATICTEXT_OZ 1001


// CGAEBV2View

IMPLEMENT_DYNCREATE(CAuftragsnehmer, CView)

BEGIN_MESSAGE_MAP(CAuftragsnehmer, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CAuftragsnehmer::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_CREATE()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

CAuftragsnehmer::CAuftragsnehmer() noexcept
{
}

void CAuftragsnehmer::OnDraw(CDC* pDC)
{
	CGAEBV2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	// TODO: add draw code for native data here
}

BOOL CAuftragsnehmer::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.style |= WS_MAXIMIZE;
	return CView::PreCreateWindow(cs);
}

BOOL CAuftragsnehmer::OnPreparePrinting(CPrintInfo* pInfo)
{
	return DoPreparePrinting(pInfo);
}

void CAuftragsnehmer::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
}

void CAuftragsnehmer::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
}

CAuftragsnehmer::~CAuftragsnehmer()
{
}
#ifdef _DEBUG
void CAuftragsnehmer::AssertValid() const
{
	CView::AssertValid();
}

void CAuftragsnehmer::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}


CGAEBV2Doc* CAuftragsnehmer::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGAEBV2Doc)));
	return (CGAEBV2Doc*)m_pDocument;
}
#endif //_DEBUG

void CAuftragsnehmer::OnFilePrintPreview()
{

#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

void CAuftragsnehmer::OnContextMenu(CWnd* pWnd, CPoint point)
{
}

int CAuftragsnehmer::OnCreate(LPCREATESTRUCT lpCreateStruct)
{

	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
}
int CAuftragsnehmer::OnCreate_Auftragsnehmer_View(LPCREATESTRUCT lpCreateStruct)
{
	CPoint pt(400, 430);
	CSize sz(70, 30);

	//m_GroupBox_Adresse_Daten_AN.Create(_T("Adressedaten"), WS_CHILD | WS_VISIBLE | BS_GROUPBOX, CRect(CPoint(50, 40), CSize(1000, 500)), this);

	m_staticText_Name1_AN.Create(_T("Name"), WS_CHILD | WS_VISIBLE, CRect(CPoint(60, 50), CSize(80, 20)), this, 1001);
	m_edit_Name1_AN.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | SS_LEFT, CRect(CPoint(120, 50), CSize(250, 20)), this, 1002);
	m_edit_Name2_AN.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, CRect(CPoint(120, 90), CSize(250, 20)), this, 1002);
	m_edit_Name3_AN.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, CRect(CPoint(120, 130), CSize(250, 20)), this, 1002);



	m_staticText_Strasse_AN.Create(_T("Strasse"), WS_CHILD | WS_VISIBLE, CRect(CPoint(60, 170), CSize(80, 20)), this, 1001);
	m_edit_Srasse_AN.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, CRect(CPoint(120, 170), CSize(250, 20)), this, 1002);

	m_staticText_PLZ_AN.Create(_T("PLZ"), WS_CHILD | WS_VISIBLE, CRect(CPoint(60, 210), CSize(80, 20)), this, 1001);
	m_edit_PLZ_AN.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, CRect(CPoint(120, 210), CSize(150, 20)), this, 1002);


	m_staticText_Ort_AN.Create(_T("Ort"), WS_CHILD | WS_VISIBLE, CRect(CPoint(60, 250), CSize(80, 20)), this, 1001);
	m_edit_Ort_AN.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, CRect(CPoint(120, 250), CSize(250, 20)), this, 1002);



	m_staticText_Land_AN.Create(_T("Land"), WS_CHILD | WS_VISIBLE, CRect(CPoint(60, 290), CSize(80, 20)), this, 1001);
	m_edit_Land_AN.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, CRect(CPoint(120, 290), CSize(250, 20)), this, 1002);


	m_staticText_Ansprechpartner_AN.Create(_T("Ansprechpartner"), WS_CHILD | WS_VISIBLE, CRect(CPoint(500, 50), CSize(120, 20)), this, 1001);
	m_edit_Ansprechpartner_AN.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, CRect(CPoint(650, 50), CSize(250, 20)), this, 1002);



	m_staticText_Telefon_AN.Create(_T("Telefon"), WS_CHILD | WS_VISIBLE, CRect(CPoint(500, 90), CSize(120, 20)), this, 1001);
	m_edit_Tel_AN.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, CRect(CPoint(650, 90), CSize(250, 20)), this, 1002);



	m_staticText_Fax_AN.Create(_T("Fax"), WS_CHILD | WS_VISIBLE, CRect(CPoint(500, 130), CSize(120, 20)), this, 1001);
	m_edit_Fax_AN.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, CRect(CPoint(650, 130), CSize(250, 20)), this, 1002);


	m_staticText_Email_AN.Create(_T("Email"), WS_CHILD | WS_VISIBLE, CRect(CPoint(500, 170), CSize(120, 20)), this, 1001);
	m_edit_Email_AN.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, CRect(CPoint(650, 170), CSize(250, 20)), this, 1002);


	m_staticText_IL_Num_AN.Create(_T("IL-Nummer"), WS_CHILD | WS_VISIBLE, CRect(CPoint(500, 210), CSize(120, 20)), this, 1001);
	m_edit_IL_Num_AN.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, CRect(CPoint(650, 210), CSize(250, 20)), this, 1002);


	m_staticText_Steuer_AN.Create(_T("UmsatzsteuerID"), WS_CHILD | WS_VISIBLE, CRect(CPoint(500, 250), CSize(120, 20)), this, 1001);
	m_edit_Steuer_AN.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, CRect(CPoint(650, 250), CSize(250, 20)), this, 1002);


	return 0;
}
