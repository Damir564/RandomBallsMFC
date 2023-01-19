
// MFCApplication2Doc.cpp: реализация класса CMFCApplication2Doc 
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "MFCApplication2.h"
#endif

#include "MFCApplication2Doc.h"

#include <propkey.h>
#include <cstdlib>
#include <time.h>
// #include <Windows.h>
#include "MainFrm.h"
#include "MyTreeView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


using namespace std;

// CMFCApplication2Doc

IMPLEMENT_DYNCREATE(CMFCApplication2Doc, CDocument)

BEGIN_MESSAGE_MAP(CMFCApplication2Doc, CDocument)
//	ON_COMMAND(ID_OPTIONS_COLOR, &CMFCApplication2Doc::OnOptionsColor)
//	ON_COMMAND(ID_OPTIONS_THICKNESS, &CMFCApplication2Doc::OnOptionsThickness)
//	ON_COMMAND(ID_THICKNESS_BIG, &CMFCApplication2Doc::OnThicknessBig)
//	ON_COMMAND(ID_THICKNESS_GIANT, &CMFCApplication2Doc::OnThicknessGiant)
//	ON_COMMAND(ID_THICKNESS_NORMAL, &CMFCApplication2Doc::OnThicknessNormal)
//	ON_COMMAND(ID_COLOR_BLACK, &CMFCApplication2Doc::OnColorBlack)
//	ON_COMMAND(ID_COLOR_BLUE, &CMFCApplication2Doc::OnColorBlue)
//	ON_COMMAND(ID_COLOR_RED, &CMFCApplication2Doc::OnColorRed)
END_MESSAGE_MAP()

CMyCircle::CMyCircle()
{
	m_iX = 0;
	m_iY = 0;
	m_iR = 0;
	m_moveX = 4;
	m_moveY = 4;
	// srand(time(0));
}
CMyCircle::CMyCircle(int x, int y, int r, int mx = 4, int my = 4)
{
	m_iX = x;
	m_iY = y;
	m_iR = r;
	m_moveX = mx;
	m_moveY = my;
	// srand(time(0));
}
void CMyCircle::OnInitialize(std::vector<CMyCircle> * p_circles)
{
	//std::random_device rndDevice;
	//std::mt19937 rng(rndDevice());
	// srand(time(0));
	pm_circles = p_circles;
	m_iIndex = pm_circles->size();

	m_iR = 20 + rand() % 31;
	m_moveX = 6 + rand() % 10;
	m_moveY = 5 + rand() % 9;
	m_moveStep = 1 + rand() % 14;
	m_moveRotate = 2 + rand() % 24;
	int dx, dy, ss, sr;
	m_iX = 60 + rand() % 600;
	m_iY = 70 + rand() % 500;
	if (pm_circles->size() > 1)
	{
		for (int i = 0; i != pm_circles->size() - 1; ++i)
		{
			dx = m_iX - (pm_circles->begin() + i)->m_iX;
			dy = m_iY - (pm_circles->begin() + i)->m_iY;
			ss = pow(dx, 2) + pow(dy, 2);
			sr = pow(m_iR + (pm_circles->begin() + i)->m_iR, 2);
			if (ss <= sr)
			{
				m_iX = (m_iX + 40) % 1100;
				m_iY = (m_iY + 40) % 550;
				i = -1;
			}
		}
	}
	//m_iX = 80 + rand() % 700;
	//m_iY = 80 + rand() % 700;
	//m_iR = 20 + rand() % 31;
	//m_moveX = rand() % 5;
	//m_moveY = rand() % 5;
}
void CMyCircle::Draw(CDC* pDC)
{
	pDC->MoveTo(m_iX + m_iR, m_iY);
	pDC->AngleArc(m_iX, m_iY, m_iR, 0, 360);
}
int CMyCircle::CalculateRandomValue()
{
	return (m_moveStep / 2 - rand() % m_moveStep);
}
void CMyCircle::CalculateNextMove()
{
	m_moveX = CalculateRandomValue();
	m_moveY = CalculateRandomValue();
}
bool CMyCircle::CirclesCollided()
{
	for (int i = 0; i != pm_circles->size(); ++i)
	{
		if (i == m_iIndex)
			continue;
		double xx = pow((m_iX - (pm_circles->begin() + i)->m_iX), 2);
		double yy = pow((m_iY - (pm_circles->begin() + i)->m_iY), 2);
		double ss = xx + yy;
		double rr = pow((m_iR + (pm_circles->begin() + i)->m_iR), 2);
		if (ss <= rr)
		{
			return true;
		}
	}
	
	return false;
}
void CMyCircle::Move(CRect& rect)
{
	if (m_counter > 8 + rand() % m_moveRotate)
	{
		CalculateNextMove();
		m_counter = 0;
	}
	++m_counter;
	m_iX += m_moveX;
	m_iY += m_moveY;
	while (true)
	{
		// CalculateNextMove();
		if ((m_iX + m_moveX + m_iR) >= rect.Width() || (m_iY + m_moveY + m_iR) >= rect.Height() || CirclesCollided())
		{
			m_iX -= m_moveX;
			m_iY -= m_moveY;
			m_moveX *= -1;
			m_moveY *= -1;

		}
		else if ((m_iY - m_iR) < 0)
		{
			if (m_moveY < 0)
				m_moveY *= -1;
			m_iY += m_moveY;
			
		}
		else if ((m_iX - m_iR) < 0)
		{
			if (m_moveX < 0)
				m_moveX *= -1;
			m_iX += m_moveX;
		}
		if (!((m_iX + m_moveX + m_iR) >= rect.Width() ||
			(m_iX - m_iR) < 0 ||
			(m_iY + m_moveY + m_iR) >= rect.Height() ||
			(m_iY - m_iR) < 0 ||
			CirclesCollided()))
			break;
	}
}



// Создание или уничтожение CMFCApplication2Doc

CMFCApplication2Doc::CMFCApplication2Doc() noexcept
{
}

CMFCApplication2Doc::~CMFCApplication2Doc()
{
}

BOOL CMFCApplication2Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	CWnd* MainWnd = AfxGetMainWnd();

	if (MainWnd)
	{

		m_pTreeView = (CMyTreeView*)((CMainFrame*)MainWnd)->m_wndSplitter.GetPane(0, 0);

		m_pTreeView->m_pDoc = this;
		m_pView = (CMFCApplication2View*)((CMainFrame*)MainWnd)->m_wndSplitter.GetPane(0, 1);

	}

	m_pTreeView->FillTree();

	m_currentColor = 0;
	m_currentThickness = 1;
	// srand(time(NULL));
	//std::random_device rd;
	//std::mt19937 gen(rd());
	//std::uniform_int_distribution<> dis(1, 10000);
	// TODO: добавьте код для одноразового вызова конструктора
	for (int i = 0; i != 5 + rand() % 7; ++i)
	{
		CMyCircle tempCircle;
		tempCircle.OnInitialize(&m_circles);
		while (tempCircle.CirclesCollided())
			tempCircle.OnInitialize(&m_circles);
		m_circles.push_back(tempCircle);
	}
	m_circlesAmount = m_circles.size();
	// m_circle.OnInitialize();
	// TODO: добавьте код повторной инициализации
	// (Документы SDI будут повторно использовать этот документ)


	return TRUE;
}




// Сериализация CMFCApplication2Doc

void CMFCApplication2Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: добавьте код сохранения
	}
	else
	{
		// TODO: добавьте код загрузки
	}
}

#ifdef SHARED_HANDLERS

// Поддержка для эскизов
void CMFCApplication2Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Измените этот код для отображения данных документа
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Поддержка обработчиков поиска
void CMFCApplication2Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// Задание содержимого поиска из данных документа.
	// Части содержимого должны разделяться точкой с запятой ";"

	// Например:  strSearchContent = _T("точка;прямоугольник;круг;объект ole;");
	SetSearchContent(strSearchContent);
}

void CMFCApplication2Doc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// Диагностика CMFCApplication2Doc

#ifdef _DEBUG
void CMFCApplication2Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMFCApplication2Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG