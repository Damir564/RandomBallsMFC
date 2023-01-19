
// MFCApplication2View.h: интерфейс класса CMFCApplication2View
//

#pragma once
#include "MFCApplication2Doc.h" // 2


class CMFCApplication2View : public CView
{
protected: // создать только из сериализации
	CMFCApplication2View() noexcept;
	DECLARE_DYNCREATE(CMFCApplication2View)

// Атрибуты
public:
	CMFCApplication2Doc* GetDocument() const;
	CRect rect;
// Операции
public:

// Переопределение
public:
	virtual void OnDraw(CDC* pDC);  // переопределено для отрисовки этого представления
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Реализация
public:
	virtual ~CMFCApplication2View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Созданные функции схемы сообщений
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
//	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
//	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // версия отладки в MFCApplication2View.cpp
inline CMFCApplication2Doc* CMFCApplication2View::GetDocument() const
   { return reinterpret_cast<CMFCApplication2Doc*>(m_pDocument); }
#endif

