#pragma once

#include "afxcview.h"
// #include "MFCApplication2Doc.h"

// CMyTreeView view

class CMFCApplication2Doc;
class CMyTreeView : public CTreeView
{
	DECLARE_DYNCREATE(CMyTreeView)

protected:
	CMyTreeView();           // protected constructor used by dynamic creation
	virtual ~CMyTreeView();
	HTREEITEM m_hColorRoot, m_hColor1, m_hColor2, m_hColor3;
	HTREEITEM m_hThicknessRoot, m_hThickness1, m_hThickness2, m_hThickness3;
public:
	CMFCApplication2Doc* m_pDoc;
	void FillTree();
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnThicknessNormal();
	afx_msg void OnColorBlack();
	afx_msg void OnColorBlue();
	afx_msg void OnThicknessBig();
	afx_msg void OnThicknessGiant();
	afx_msg void OnColorRed();
};


