// MyTreeView.cpp : implementation file
//

#include "pch.h"
#include "MFCApplication2.h"
#include "MyTreeView.h"
#include "MFCApplication2Doc.h"

// CMyTreeView

IMPLEMENT_DYNCREATE(CMyTreeView, CTreeView)

CMyTreeView::CMyTreeView()
{

}

CMyTreeView::~CMyTreeView()
{
}

void CMyTreeView::FillTree()
{
	CTreeCtrl& tree = GetTreeCtrl();
	tree.DeleteAllItems();

	m_hThicknessRoot = tree.InsertItem(L"Толщина", -1, -1, NULL, TVI_FIRST);

	m_hThickness1 = tree.InsertItem(L"Обычный", -1, -1, m_hThicknessRoot, TVI_LAST);
	m_hThickness2 = tree.InsertItem(L"Большой", -1, -1, m_hThicknessRoot, TVI_LAST);
	m_hThickness3 = tree.InsertItem(L"Огромный", -1, -1, m_hThicknessRoot, TVI_LAST);

	tree.Expand(m_hThicknessRoot, TVE_EXPAND);

	tree.SetItemData(m_hThickness1, 10);
	tree.SetItemData(m_hThickness2, 20);
	tree.SetItemData(m_hThickness3, 40);

	m_hColorRoot = tree.InsertItem(L"Цвет", -1, -1, NULL, TVI_FIRST);

	m_hColor1 = tree.InsertItem(L"Черный", -1, -1, m_hColorRoot, TVI_LAST);
	m_hColor2 = tree.InsertItem(L"Синий", -1, -1, m_hColorRoot, TVI_LAST);
	m_hColor3 = tree.InsertItem(L"Красный", -1, -1, m_hColorRoot, TVI_LAST);

	tree.Expand(m_hColorRoot, TVE_EXPAND);

	tree.SetItemData(m_hColor1, 0);
	tree.SetItemData(m_hColor2, 1);
	tree.SetItemData(m_hColor3, 2);
	// int n = tree.GetItemData(m_hColor1);
}

BEGIN_MESSAGE_MAP(CMyTreeView, CTreeView)
	ON_WM_CREATE()
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(ID_THICKNESS_NORMAL, &CMyTreeView::OnThicknessNormal)
	ON_COMMAND(ID_COLOR_BLACK, &CMyTreeView::OnColorBlack)
	ON_COMMAND(ID_COLOR_BLUE, &CMyTreeView::OnColorBlue)
	ON_COMMAND(ID_THICKNESS_BIG, &CMyTreeView::OnThicknessBig)
	ON_COMMAND(ID_THICKNESS_GIANT, &CMyTreeView::OnThicknessGiant)
	ON_COMMAND(ID_COLOR_RED, &CMyTreeView::OnColorRed)
END_MESSAGE_MAP()


// CMyTreeView diagnostics

#ifdef _DEBUG
void CMyTreeView::AssertValid() const
{
	CTreeView::AssertValid();
}

#ifndef _WIN32_WCE
void CMyTreeView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}
#endif
#endif //_DEBUG


// CMyTreeView message handlers


int CMyTreeView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CTreeView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here

	return 0;
}


void CMyTreeView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CTreeCtrl& tree = GetTreeCtrl();

	HTREEITEM sel = tree.GetSelectedItem();

	if (tree.GetItemData(sel) < 10)
		m_pDoc->m_currentColor = tree.GetItemData(sel);
	else
		m_pDoc->m_currentThickness = tree.GetItemData(sel) / 10;

	m_pDoc->m_pView->Invalidate(FALSE);

	CTreeView::OnLButtonDown(nFlags, point);
}


void CMyTreeView::OnThicknessBig()
{
	// TODO: Add your command handler code here

	m_pDoc->m_currentThickness = 20;
}


void CMyTreeView::OnThicknessGiant()
{
	// TODO: Add your command handler code here
	m_pDoc->m_currentThickness = 40;
}


void CMyTreeView::OnThicknessNormal()
{
	// TODO: Add your command handler code here
	m_pDoc->m_currentThickness = 10;
}


void CMyTreeView::OnColorBlack()
{
	// TODO: Add your command handler code here
	m_pDoc->m_currentColor = 0;
}


void CMyTreeView::OnColorBlue()
{
	// TODO: Add your command handler code here
	m_pDoc->m_currentColor = 1;
}


void CMyTreeView::OnColorRed()
{
	// TODO: Add your command handler code here
	m_pDoc->m_currentColor = 2;
}

//void CMyTreeView::OnColorBlack()
//{
//	// TODO: Add your command handler code here
//}
//
//
//void CMyTreeView::OnColorBlue()
//{
//	// TODO: Add your command handler code here
//}
//
//void CMyTreeView::OnColorRed()
//{
//	// TODO: Add your command handler code here
//}
//
//
//void CMyTreeView::OnThicknessNormal()
//{
//	// TODO: Add your command handler code here
//}
//
//
//
//void CMyTreeView::OnThicknessBig()
//{
//	// TODO: Add your command handler code here
//}
//
//
//void CMyTreeView::OnThicknessGiant()
//{
//	// TODO: Add your command handler code here
//}


