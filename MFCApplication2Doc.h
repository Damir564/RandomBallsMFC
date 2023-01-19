
// MFCApplication2Doc.h: интерфейс класса CMFCApplication2Doc 
//

#pragma once
#include <vector>
#include "MyTreeView.h"
#include "MFCApplication2View.h"

// class CMFCApplication2View;

class CMyTreeView;
class CMFCApplication2View;
// class CMainFrame;

class CMyCircle
{
public:
	CMyCircle();
	CMyCircle(int x, int y, int r, int mx, int my);

	int m_iX, m_iY, m_iR, m_moveX, m_moveY, m_iIndex, m_counter = 999999;
	int m_moveStep, m_moveRotate;
	std::vector<CMyCircle> * pm_circles;
	void Draw(CDC* pDC);
	void Move(CRect& rect);
	int CalculateRandomValue( );
	void CalculateNextMove();
	void OnInitialize(std::vector<CMyCircle>*);
	bool CirclesCollided();
};

class CMFCApplication2Doc : public CDocument
{
protected: // создать только из сериализации
	CMFCApplication2Doc() noexcept;
	DECLARE_DYNCREATE(CMFCApplication2Doc)



// Атрибуты
public:
	int m_currentColor, m_currentThickness;
	std::vector <CMyCircle> m_circles;
	int m_circlesAmount;

	int m_iThickness = 1;
	COLORREF m_color = RGB(255, 0, 14);

	CMyTreeView* m_pTreeView;
	CMFCApplication2View* m_pView;
	
// Операции
public:

// Переопределение
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Реализация
public:
	virtual ~CMFCApplication2Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Созданные функции схемы сообщений
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Вспомогательная функция, задающая содержимое поиска для обработчика поиска
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
//	afx_msg void OnOptionsColor();
//	afx_msg void OnOptionsThickness();
//	afx_msg void OnThicknessBig();
//	afx_msg void OnThicknessGiant();
//	afx_msg void OnThicknessNormal();
//	afx_msg void OnColorBlack();
//	afx_msg void OnColorBlue();
//	afx_msg void OnColorRed();
};
