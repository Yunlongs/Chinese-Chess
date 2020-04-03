
// Chinese ChessView.h : CChineseChessView 类的接口
//

#pragma once
#include "afxwin.h"
afx_msg void OnBtnDown();	//开始游戏
afx_msg void OnBtnDown1();	//悔棋
afx_msg void OnBtnDown2();	//认输
afx_msg void OnBtnDown3();	//结束游戏
afx_msg void OnBtnDown4();	//和棋


class  QZ			//棋子
{
public:
	QZ()
	{
		x = -100, y = -100;
	}
	CString fileName;	// = curPath;
	CImage image;		
	int x, y, s;
};

class  STEP
{
public:
	STEP()
	{
		x = 0, y = 0, n = 0;
	}
	int x, y, n;
};


class CChineseChessView : public CView
{
protected: // 仅从序列化创建
	CChineseChessView();
	DECLARE_DYNCREATE(CChineseChessView)

// 特性
public:
	CChineseChessDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 实现
public:
	virtual ~CChineseChessView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
private:
	CButton btn, btn1, btn2, btn3, btn4;
	TCHAR curPath[500];		// 获取当前路径  
	int nLength;
	CString BGMFileName1, BGMFileName2;
	CString pointx, pointy;

public:
	void OnBtnDown();
	void OnBtnDown1();
	void OnBtnDown2();
	void OnBtnDown3();
	void OnBtnDown4();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
private:
	bool Rules();
public:
	void PlayBGM();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void ConsoleGame(int NewX, int NewY);
	void LANGame(int NewX, int NewY);
};

#ifndef _DEBUG  // Chinese ChessView.cpp 中的调试版本
inline CChineseChessDoc* CChineseChessView::GetDocument() const
   { return reinterpret_cast<CChineseChessDoc*>(m_pDocument); }
#endif

