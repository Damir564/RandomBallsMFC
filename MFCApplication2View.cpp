
// MFCApplication2View.cpp: реализация класса CMFCApplication2View
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "MFCApplication2.h"
#endif

#include "MFCApplication2Doc.h"
#include "MFCApplication2View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCApplication2View

IMPLEMENT_DYNCREATE(CMFCApplication2View, CView)

BEGIN_MESSAGE_MAP(CMFCApplication2View, CView)
	// Стандартные команды печати
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_TIMER()
//	ON_WM_RBUTTONUP()
//ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()



// Создание или уничтожение CMFCApplication2View

CMFCApplication2View::CMFCApplication2View() noexcept
{
	// TODO: добавьте код создания
	srand(time(NULL));
}

CMFCApplication2View::~CMFCApplication2View()
{
}

BOOL CMFCApplication2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: изменить класс Window или стили посредством изменения
	//  CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// Рисование CMFCApplication2View

void CMFCApplication2View::OnDraw(CDC* pDC)
{
	CMFCApplication2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CPen pen;
	if(pDoc->m_currentColor == 0)
		pen.CreatePen(PS_SOLID, pDoc->m_currentThickness, RGB(0, 0, 0));
	else if(pDoc->m_currentColor == 1)
		pen.CreatePen(PS_SOLID, pDoc->m_currentThickness, RGB(0, 0, 255));
	else
		pen.CreatePen(PS_SOLID, pDoc->m_currentThickness, RGB(255, 0, 0));

	pDC->SelectObject(&pen);
	
	for (int i = 0; i != pDoc->m_circlesAmount; ++i)
	{
		pDoc->m_circles[i].Draw(pDC);
	}

	// pDC->LineTo(rect.Width(), rect.Height());
}


// Печать CMFCApplication2View

BOOL CMFCApplication2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// подготовка по умолчанию
	return DoPreparePrinting(pInfo);
}

void CMFCApplication2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: добавьте дополнительную инициализацию перед печатью
}

void CMFCApplication2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: добавьте очистку после печати
}


// Диагностика CMFCApplication2View

#ifdef _DEBUG
void CMFCApplication2View::AssertValid() const
{
	CView::AssertValid();
}

void CMFCApplication2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCApplication2Doc* CMFCApplication2View::GetDocument() const // встроена неотлаженная версия
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCApplication2Doc)));
	return (CMFCApplication2Doc*)m_pDocument;
}
#endif //_DEBUG


// Обработчики сообщений CMFCApplication2View


void CMFCApplication2View::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	
	SetTimer(0, 1, NULL);
}


void CMFCApplication2View::OnTimer(UINT_PTR nIDEvent)
{
	CMFCApplication2Doc* pDoc = GetDocument();
	
	GetClientRect(&rect);
	//pDoc->m_circle.m_iX += 1;
	//pDoc->m_circle.m_iY += 1;
	for (int i = 0; i != pDoc->m_circlesAmount; ++i)
	{
		pDoc->m_circles[i].Move(rect);
	}
	// pDoc->m_circle.m_iR += 1;

	Invalidate();

	CView::OnTimer(nIDEvent);
}

