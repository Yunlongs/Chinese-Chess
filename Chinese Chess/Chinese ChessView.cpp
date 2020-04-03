
// Chinese ChessView.cpp : CChineseChessView 类的实现
//

#include "stdafx.h"
#include <stdlib.h>
#include<winsock2.h>///////////
#pragma comment(lib,"ws2_32.lib")////////
#include <mmsystem.h>
#pragma comment(lib, "WINMM.LIB")
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Chinese Chess.h"
#endif

#include "Chinese ChessDoc.h"
#include "Chinese ChessView.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#define Qx 53		//棋盘左顶点长
#define Qy 31		//棋盘左顶点宽
#define QL 57		//棋盘格子边长


QZ qz[50];		//棋子
bool IfTick=true;
HDC hdc;

CImage BGMImage1, BGMImage2;
CString SoundfileName[9];
void G_Show();
void kehu();
int killking();
void GameOver();
bool IfGameBegin = false, IfGameOver = true;
CString ip;
CString pointx, pointy, pointn, point01, pointbtn, pointbtn1, pointbtn2, pointbtn3, pointbtn4;
int ifbtn = 0,ifbtn1 = 0, ifbtn2 = 0, ifbtn3 = 0, ifbtn4 = 0/*	1是发送请求对话框，2是同意，3是不同意	*/ ;
int right = 2;		//0是没有棋子接收，1是对方选棋成功，2是对方下子成功轮到己方下子,3是按下按钮,4是重新选棋
int Sendright=0;

int StepCount = 0;
CList <STEP> step;
STEP step1/*当前*/, step2/*前两步*/;


int MoShi = 0;
// CChineseChessView

IMPLEMENT_DYNCREATE(CChineseChessView, CView)

BEGIN_MESSAGE_MAP(CChineseChessView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_CREATE()
	ON_BN_CLICKED(IDB_BTN, OnBtnDown)
	ON_BN_CLICKED(IDB_BTN1, OnBtnDown1)
	ON_BN_CLICKED(IDB_BTN2, OnBtnDown2)
	ON_BN_CLICKED(IDB_BTN3, OnBtnDown3)
	ON_BN_CLICKED(IDB_BTN4, OnBtnDown4)
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_TIMER()
END_MESSAGE_MAP()

// CChineseChessView 构造/析构

CChineseChessView::CChineseChessView()
{
	// TODO: 在此处添加构造代码
}

CChineseChessView::~CChineseChessView()
{

}

BOOL CChineseChessView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CChineseChessView 绘制


void CChineseChessView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);

#endif
}

// CChineseChessView 诊断

#ifdef _DEBUG
void CChineseChessView::AssertValid() const
{
	CView::AssertValid();
}

void CChineseChessView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CChineseChessDoc* CChineseChessView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CChineseChessDoc)));
	return (CChineseChessDoc*)m_pDocument;
}
#endif //_DEBUG

// CChineseChessView 消息处理程序

void CChineseChessView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CView::OnMouseMove(nFlags, point);
}

BOOL CChineseChessView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	return true;
}

void CChineseChessView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CView::OnRButtonDown(nFlags, point);
}

void CChineseChessView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}


//初始化界面
void CChineseChessView::OnDraw(CDC* /* pDC*/)
{
	CChineseChessDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	nLength = ::GetCurrentDirectory(500, curPath);		// 设置文件路径  

	hdc = GetDC()->m_hDC;

	for (int i = 0; i < 50; i++)
	{
		qz[i].fileName += curPath;
	}

	// 文件名 
	qz[0].fileName += "//res//背景.bmp";
	qz[1].fileName += "//棋//棋盘.png";
	qz[2].fileName += "//棋//帅.png";
	qz[3].fileName += "//棋//仕.png";
	qz[4].fileName += "//棋//仕.png";
	qz[5].fileName += "//棋//相.png";
	qz[6].fileName += "//棋//相.png";
	qz[7].fileName += "//棋//马.png";
	qz[8].fileName += "//棋//马.png";
	qz[9].fileName += "//棋//车.png";
	qz[10].fileName += "//棋//车.png";
	qz[11].fileName += "//棋//砲.png";
	qz[12].fileName += "//棋//砲.png";
	qz[13].fileName += "//棋//兵.png";
	qz[14].fileName += "//棋//兵.png";
	qz[15].fileName += "//棋//兵.png";
	qz[16].fileName += "//棋//兵.png";
	qz[17].fileName += "//棋//兵.png";
	qz[18].fileName += "//棋//将.png";
	qz[19].fileName += "//棋//士.png";
	qz[20].fileName += "//棋//士.png";
	qz[21].fileName += "//棋//象.png";
	qz[22].fileName += "//棋//象.png";
	qz[23].fileName += "//棋//馬.png";
	qz[24].fileName += "//棋//馬.png";
	qz[25].fileName += "//棋//車.png";
	qz[26].fileName += "//棋//車.png";
	qz[27].fileName += "//棋//炮.png";
	qz[28].fileName += "//棋//炮.png";
	qz[29].fileName += "//棋//卒.png";
	qz[30].fileName += "//棋//卒.png";
	qz[31].fileName += "//棋//卒.png";
	qz[32].fileName += "//棋//卒.png";
	qz[33].fileName += "//棋//卒.png";

	qz[34].fileName += "//棋//帅1.png";
	qz[35].fileName += "//棋//仕1.png";
	qz[36].fileName += "//棋//相1.png";
	qz[37].fileName += "//棋//马1.png";
	qz[38].fileName += "//棋//车1.png";
	qz[39].fileName += "//棋//砲1.png";
	qz[40].fileName += "//棋//兵1.png";
	qz[41].fileName += "//棋//将1.png";
	qz[42].fileName += "//棋//士1.png";
	qz[43].fileName += "//棋//象1.png";
	qz[44].fileName += "//棋//馬1.png";
	qz[45].fileName += "//棋//車1.png";
	qz[46].fileName += "//棋//炮1.png";
	qz[47].fileName += "//棋//卒1.png";
	qz[48].fileName += "//棋//1.png";


	//选择后加框图片对应序号
	qz[2].s = 34;
	qz[3].s = 35;
	qz[4].s = 35;
	qz[5].s = 36;
	qz[6].s = 36;
	qz[7].s = 37;
	qz[8].s = 37;
	qz[9].s = 38;
	qz[10].s = 38;
	qz[11].s = 39;
	qz[12].s = 39;
	qz[13].s = 40;
	qz[14].s = 40;
	qz[15].s = 40;
	qz[16].s = 40;
	qz[17].s = 40;
	qz[18].s = 41;
	qz[19].s = 42;
	qz[20].s = 42;
	qz[21].s = 43;
	qz[22].s = 43;
	qz[23].s = 44;
	qz[24].s = 44;
	qz[25].s = 45;
	qz[26].s = 45;
	qz[27].s = 46;
	qz[28].s = 46;
	qz[29].s = 47;
	qz[30].s = 47;
	qz[31].s = 47;
	qz[32].s = 47;
	qz[33].s = 47;


	for (int i = 0; i < 49; i++)
		qz[i].image.Load(qz[i].fileName);

	//背景音乐字样图片
	BGMFileName1 += curPath;
	BGMFileName2 += curPath;
	BGMFileName1 += "//res//BGM1.png";
	BGMFileName2 += "//res//BGM2.png";
	BGMImage1.Load(BGMFileName1);
	BGMImage2.Load(BGMFileName2);

	//初始化棋盘
	G_Show();

	for (int i = 0; i < 9; i++)
	{
		SoundfileName[i] = curPath;
	}

	//音乐文件地址
	SoundfileName[0] += "//声音//NEWGAME.WAV";
	SoundfileName[1] += "//声音//WIN.WAV";
	SoundfileName[2] += "//声音//LOSS.WAV";
	SoundfileName[3] += "//声音//DRAW.WAV";
	SoundfileName[4] += "//声音//CLICK.WAV";
	SoundfileName[5] += "//声音//CAPTURE2.WAV";
	SoundfileName[6] += "//声音//MOVE2.WAV";
	SoundfileName[7] += "//声音//CHECK2.WAV";
	SoundfileName[8] += "//声音//KILLKING.WAV";

	SetTimer(2, 1, NULL);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}

//绘制棋盘
void G_Show()
{
	CImage m_Screen;

	m_Screen.Create(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), qz[0].image.GetBPP());
	qz[0].image.Draw(m_Screen.GetDC(), CRect(0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN)));
	m_Screen.ReleaseDC();

	qz[1].image.Draw(m_Screen.GetDC(), 50, 30);
	m_Screen.ReleaseDC();

	qz[2].image.Draw(m_Screen.GetDC(), qz[2].x + Qx, qz[2].y + Qy, QL, QL);
	m_Screen.ReleaseDC();

	qz[3].image.Draw(m_Screen.GetDC(), qz[3].x + Qx, qz[3].y + Qy, QL, QL);
	m_Screen.ReleaseDC();
	qz[4].image.Draw(m_Screen.GetDC(), qz[4].x + Qx, qz[4].y + Qy, QL, QL);
	m_Screen.ReleaseDC();


	qz[5].image.Draw(m_Screen.GetDC(), qz[5].x + Qx, qz[5].y + Qy, QL, QL);
	m_Screen.ReleaseDC();
	qz[6].image.Draw(m_Screen.GetDC(), qz[6].x + Qx, qz[6].y + Qy, QL, QL);
	m_Screen.ReleaseDC();

	qz[7].image.Draw(m_Screen.GetDC(), qz[7].x + Qx, qz[7].y + Qy, QL, QL);
	m_Screen.ReleaseDC();
	qz[8].image.Draw(m_Screen.GetDC(), qz[8].x + Qx, qz[8].y + Qy, QL, QL);
	m_Screen.ReleaseDC();

	qz[9].image.Draw(m_Screen.GetDC(), qz[9].x + Qx, qz[9].y + Qy, QL, QL);
	m_Screen.ReleaseDC();
	qz[10].image.Draw(m_Screen.GetDC(), qz[10].x + Qx, qz[10].y + Qy, QL, QL);
	m_Screen.ReleaseDC();

	qz[11].image.Draw(m_Screen.GetDC(), qz[11].x + Qx, qz[11].y + Qy, QL, QL);
	m_Screen.ReleaseDC();
	qz[12].image.Draw(m_Screen.GetDC(), qz[12].x + Qx, qz[12].y + Qy, QL, QL);
	m_Screen.ReleaseDC();

	qz[13].image.Draw(m_Screen.GetDC(), qz[13].x + Qx, qz[13].y + Qy, QL, QL);
	m_Screen.ReleaseDC();
	qz[14].image.Draw(m_Screen.GetDC(), qz[14].x + Qx, qz[14].y + Qy, QL, QL);
	m_Screen.ReleaseDC();
	qz[15].image.Draw(m_Screen.GetDC(), qz[15].x + Qx, qz[15].y + Qy, QL, QL);
	m_Screen.ReleaseDC();
	qz[16].image.Draw(m_Screen.GetDC(), qz[16].x + Qx, qz[16].y + Qy, QL, QL);
	m_Screen.ReleaseDC();
	qz[17].image.Draw(m_Screen.GetDC(), qz[17].x + Qx, qz[17].y + Qy, QL, QL);
	m_Screen.ReleaseDC();

	qz[18].image.Draw(m_Screen.GetDC(), qz[18].x + Qx, qz[18].y + Qy, QL, QL);
	m_Screen.ReleaseDC();

	qz[19].image.Draw(m_Screen.GetDC(), qz[19].x + Qx, qz[19].y + Qy, QL, QL);
	m_Screen.ReleaseDC();
	qz[20].image.Draw(m_Screen.GetDC(), qz[20].x + Qx, qz[20].y + Qy, QL, QL);
	m_Screen.ReleaseDC();

	qz[21].image.Draw(m_Screen.GetDC(), qz[21].x + Qx, qz[21].y + Qy, QL, QL);
	m_Screen.ReleaseDC();
	qz[22].image.Draw(m_Screen.GetDC(), qz[22].x + Qx, qz[22].y + Qy, QL, QL);
	m_Screen.ReleaseDC();

	qz[23].image.Draw(m_Screen.GetDC(), qz[23].x + Qx, qz[23].y + Qy, QL, QL);
	m_Screen.ReleaseDC();
	qz[24].image.Draw(m_Screen.GetDC(), qz[24].x + Qx, qz[24].y + Qy, QL, QL);
	m_Screen.ReleaseDC();

	qz[25].image.Draw(m_Screen.GetDC(), qz[25].x + Qx, qz[25].y + Qy, QL, QL);
	m_Screen.ReleaseDC();
	qz[26].image.Draw(m_Screen.GetDC(), qz[26].x + Qx, qz[26].y + Qy, QL, QL);
	m_Screen.ReleaseDC();

	qz[27].image.Draw(m_Screen.GetDC(), qz[27].x + Qx, qz[27].y + Qy, QL, QL);
	m_Screen.ReleaseDC();
	qz[28].image.Draw(m_Screen.GetDC(), qz[28].x + Qx, qz[28].y + Qy, QL, QL);
	m_Screen.ReleaseDC();

	qz[29].image.Draw(m_Screen.GetDC(), qz[29].x + Qx, qz[29].y + Qy, QL, QL);
	m_Screen.ReleaseDC();
	qz[30].image.Draw(m_Screen.GetDC(), qz[30].x + Qx, qz[30].y + Qy, QL, QL);
	m_Screen.ReleaseDC();
	qz[31].image.Draw(m_Screen.GetDC(), qz[31].x + Qx, qz[31].y + Qy, QL, QL);
	m_Screen.ReleaseDC();
	qz[32].image.Draw(m_Screen.GetDC(), qz[32].x + Qx, qz[32].y + Qy, QL, QL);
	m_Screen.ReleaseDC();
	qz[33].image.Draw(m_Screen.GetDC(), qz[33].x + Qx, qz[33].y + Qy, QL, QL);
	m_Screen.ReleaseDC();

	qz[34].image.Draw(m_Screen.GetDC(), qz[34].x + Qx, qz[34].y + Qy, QL, QL);
	m_Screen.ReleaseDC();
	qz[35].image.Draw(m_Screen.GetDC(), qz[35].x + Qx, qz[35].y + Qy, QL, QL);
	m_Screen.ReleaseDC();
	qz[36].image.Draw(m_Screen.GetDC(), qz[36].x + Qx, qz[36].y + Qy, QL, QL);
	m_Screen.ReleaseDC();
	qz[37].image.Draw(m_Screen.GetDC(), qz[37].x + Qx, qz[37].y + Qy, QL, QL);
	m_Screen.ReleaseDC();
	qz[38].image.Draw(m_Screen.GetDC(), qz[38].x + Qx, qz[38].y + Qy, QL, QL);
	m_Screen.ReleaseDC();
	qz[39].image.Draw(m_Screen.GetDC(), qz[39].x + Qx, qz[39].y + Qy, QL, QL);
	m_Screen.ReleaseDC();
	qz[40].image.Draw(m_Screen.GetDC(), qz[40].x + Qx, qz[40].y + Qy, QL, QL);
	m_Screen.ReleaseDC();
	qz[41].image.Draw(m_Screen.GetDC(), qz[41].x + Qx, qz[41].y + Qy, QL, QL);
	m_Screen.ReleaseDC();
	qz[42].image.Draw(m_Screen.GetDC(), qz[42].x + Qx, qz[42].y + Qy, QL, QL);
	m_Screen.ReleaseDC();
	qz[43].image.Draw(m_Screen.GetDC(), qz[43].x + Qx, qz[43].y + Qy, QL, QL);
	m_Screen.ReleaseDC();
	qz[44].image.Draw(m_Screen.GetDC(), qz[44].x + Qx, qz[44].y + Qy, QL, QL);
	m_Screen.ReleaseDC();
	qz[45].image.Draw(m_Screen.GetDC(), qz[45].x + Qx, qz[45].y + Qy, QL, QL);
	m_Screen.ReleaseDC();
	qz[46].image.Draw(m_Screen.GetDC(), qz[46].x + Qx, qz[46].y + Qy, QL, QL);
	m_Screen.ReleaseDC();
	qz[47].image.Draw(m_Screen.GetDC(), qz[47].x + Qx, qz[47].y + Qy, QL, QL);
	m_Screen.ReleaseDC();
	qz[48].image.Draw(m_Screen.GetDC(), qz[48].x + Qx, qz[48].y + Qy, QL, QL);
	m_Screen.ReleaseDC();

	BGMImage1.Draw(m_Screen.GetDC(), 600,50);
	m_Screen.ReleaseDC();
	if (IfTick)
	{
		BGMImage2.Draw(m_Screen.GetDC(), 600, 50);
		m_Screen.ReleaseDC();
	}

	m_Screen.Draw(hdc, 0, 0);
}

//创建按钮
int CChineseChessView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	if (MoShi == 1)
	{
		btn.Create("开始", WS_CHILD | WS_VISIBLE | WS_BORDER, CRect(600, 200, 700, 250), GetParent(), IDB_BTN);
	}
	else
	{
		btn.Create("准备", WS_CHILD | WS_VISIBLE | WS_BORDER, CRect(600, 200, 700, 250), GetParent(), IDB_BTN);
	}
	btn.ShowWindow(SW_SHOWNORMAL);
	btn1.Create("悔棋", WS_CHILD | WS_VISIBLE | WS_BORDER, CRect(600, 280, 700, 330), GetParent(), IDB_BTN1);
	btn1.ShowWindow(SW_SHOWNORMAL);
	btn2.Create("认输", WS_CHILD | WS_VISIBLE | WS_BORDER, CRect(600, 440, 700, 490), GetParent(), IDB_BTN2);
	btn2.ShowWindow(SW_SHOWNORMAL);
	btn3.Create("退出", WS_CHILD | WS_VISIBLE | WS_BORDER, CRect(600, 520, 700, 570), GetParent(), IDB_BTN3);
	btn3.ShowWindow(SW_SHOWNORMAL);
	btn4.Create("求和", WS_CHILD | WS_VISIBLE | WS_BORDER, CRect(600, 360, 700, 410), GetParent(), IDB_BTN4);
	btn4.ShowWindow(SW_SHOWNORMAL);

	return 0;
}

//比赛开始
void CChineseChessView::OnBtnDown()
{
	if (!IfGameOver)
	{
	}
	else if (IfGameBegin)
	{
	}
	else
	{
		sndPlaySound(SoundfileName[0], SND_ASYNC | SND_NODEFAULT);

		qz[2].x = 4 * QL, qz[2].y = 9 * QL;
		qz[3].x = 3 * QL, qz[3].y = 9 * QL;
		qz[4].x = 5 * QL, qz[4].y = 9 * QL;
		qz[5].x = 2 * QL, qz[5].y = 9 * QL;
		qz[6].x = 6 * QL, qz[6].y = 9 * QL;
		qz[7].x = 1 * QL, qz[7].y = 9 * QL;
		qz[8].x = 7 * QL, qz[8].y = 9 * QL;
		qz[9].x = 0 * QL, qz[9].y = 9 * QL;
		qz[10].x = 8 * QL, qz[10].y = 9 * QL;
		qz[11].x = 1 * QL, qz[11].y = 7 * QL;
		qz[12].x = 7 * QL, qz[12].y = 7 * QL;
		qz[13].x = 0 * QL, qz[13].y = 6 * QL;
		qz[14].x = 2 * QL, qz[14].y = 6 * QL;
		qz[15].x = 4 * QL, qz[15].y = 6 * QL;
		qz[16].x = 6 * QL, qz[16].y = 6 * QL;
		qz[17].x = 8 * QL, qz[17].y = 6 * QL;
		qz[18].x = 4 * QL, qz[18].y = 0 * QL;
		qz[19].x = 3 * QL, qz[19].y = 0 * QL;
		qz[20].x = 5 * QL, qz[20].y = 0 * QL;
		qz[21].x = 2 * QL, qz[21].y = 0 * QL;
		qz[22].x = 6 * QL, qz[22].y = 0 * QL;
		qz[23].x = 1 * QL, qz[23].y = 0 * QL;
		qz[24].x = 7 * QL, qz[24].y = 0 * QL;
		qz[25].x = 0 * QL, qz[25].y = 0 * QL;
		qz[26].x = 8 * QL, qz[26].y = 0 * QL;
		qz[27].x = 1 * QL, qz[27].y = 2 * QL;
		qz[28].x = 7 * QL, qz[28].y = 2 * QL;
		qz[29].x = 0 * QL, qz[29].y = 3 * QL;
		qz[30].x = 2 * QL, qz[30].y = 3 * QL;
		qz[31].x = 4 * QL, qz[31].y = 3 * QL;
		qz[32].x = 6 * QL, qz[32].y = 3 * QL;
		qz[33].x = 8 * QL, qz[33].y = 3 * QL;
		//带蓝框的棋子
		qz[34].x = -100, qz[34].y = -100;
		qz[34].x = -100, qz[34].y = -100;
		qz[36].x = -100, qz[36].y = -100;
		qz[37].x = -100, qz[37].y = -100;
		qz[38].x = -100, qz[38].y = -100;
		qz[39].x = -100, qz[39].y = -100;
		qz[40].x = -100, qz[40].y = -100;
		qz[41].x = -100, qz[41].y = -100;
		qz[42].x = -100, qz[42].y = -100;
		qz[43].x = -100, qz[43].y = -100;
		qz[44].x = -100, qz[44].y = -100;
		qz[45].x = -100, qz[45].y = -100;
		qz[46].x = -100, qz[46].y = -100;
		qz[47].x = -100, qz[47].y = -100;
		qz[48].x = -100, qz[48].y = -100;
		G_Show();

		StepCount = 0;		//步数清零
		IfGameOver = false;
		IfGameBegin = true;
		step.RemoveAll();

		if (MoShi == 2)
		{
			Sendright = 3;
			step1.x = 0;
			step1.y = 0;
			step1.n = 0;
			kehu();
		}
	}
}

//悔棋
void CChineseChessView::OnBtnDown1()
{
	if (!IfGameOver && ((MoShi == 1 && IfGameBegin) || (MoShi == 2 && ifbtn == 1 && IfGameBegin == 1)))		//比赛未结束 且 单机模式比赛开始 且 局域网模式是双方都准备
	{
		if (step.GetCount() % 2 == 1)
		{
			--StepCount;
			step.RemoveTail();
			qz[48].x = -100;
			qz[48].y = -100;
		}
		if (!step.IsEmpty())
		{
			if (step.GetTail().n != 0)
			{
				qz[step.GetTail().n].x = step.GetTail().x;			//第四步还原
				qz[step.GetTail().n].y = step.GetTail().y;
			}
			step.RemoveTail();
			qz[qz[step.GetTail().n].s].x = -100;
			qz[qz[step.GetTail().n].s].y = -100;
			qz[step.GetTail().n].x = step.GetTail().x;
			qz[step.GetTail().n].y = step.GetTail().y;				//第三步还原
			step.RemoveTail();
			qz[48].x = -100;
			qz[48].y = -100;
			if (step.GetCount() >= 2)
			{
				qz[step.GetAt(step.FindIndex(step.GetCount() - 2)).n].x = step.GetTail().x;
				qz[step.GetAt(step.FindIndex(step.GetCount() - 2)).n].y = step.GetTail().y;
				qz[qz[step.GetAt(step.FindIndex(step.GetCount() - 2)).n].s].x = step.GetTail().x;
				qz[qz[step.GetAt(step.FindIndex(step.GetCount() - 2)).n].s].y = step.GetTail().y;	//第二步还原
				qz[48].x = step.GetAt(step.FindIndex(step.GetCount() - 2)).x;
				qz[48].y = step.GetAt(step.FindIndex(step.GetCount() - 2)).y;						//第一步还原
			}
			else
			{
				qz[48].x = -100;
				qz[48].y = -100;
			}
		}
		if (MoShi == 2)
		{
			if (right == 2)
			{
				if (!step.IsEmpty())
				{
					if (step.GetTail().n != 0)
					{
						qz[step.GetTail().n].x = step.GetTail().x;			//第四步还原
						qz[step.GetTail().n].y = step.GetTail().y;
					}
					step.RemoveTail();
					qz[qz[step.GetTail().n].s].x = -100;
					qz[qz[step.GetTail().n].s].y = -100;
					qz[step.GetTail().n].x = step.GetTail().x;
					qz[step.GetTail().n].y = step.GetTail().y;				//第三步还原
					step.RemoveTail();
					qz[48].x = -100;
					qz[48].y = -100;
					if (step.GetCount() >= 2)
					{
						qz[step.GetAt(step.FindIndex(step.GetCount() - 2)).n].x = step.GetTail().x;
						qz[step.GetAt(step.FindIndex(step.GetCount() - 2)).n].y = step.GetTail().y;
						qz[qz[step.GetAt(step.FindIndex(step.GetCount() - 2)).n].s].x = step.GetTail().x;
						qz[qz[step.GetAt(step.FindIndex(step.GetCount() - 2)).n].s].y = step.GetTail().y;	//第二步还原
						qz[48].x = step.GetAt(step.FindIndex(step.GetCount() - 2)).x;
						qz[48].y = step.GetAt(step.FindIndex(step.GetCount() - 2)).y;						//第一步还原
					}
					else
					{
						qz[48].x = -100;
						qz[48].y = -100;
					}
				}
			}
			ifbtn1 = 1;
			kehu();
		}
		G_Show();
	}
}

//认输
void CChineseChessView::OnBtnDown2()
{
	if (!IfGameOver && ((MoShi == 1 && IfGameBegin) || (MoShi == 2 && ifbtn == 1 && IfGameBegin == 1)))		//比赛未结束 且 单机模式比赛开始 且 局域网模式是双方都准备
	{
		sndPlaySound(SoundfileName[2], SND_ASYNC | SND_NODEFAULT);

		SetBkMode(hdc, TRANSPARENT);//透明 
		SelectObject(hdc, CreateFont(80, 20, 0, 0, FW_HEAVY, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_RASTER_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, FF_SCRIPT, "黑体"));
		for (int Qxx = 0, Qyy = Qy; Qxx <= Qx + 3 * QL + 10; Qxx += 5, Qyy += 5)
		{
			G_Show();
			if (step.GetCount() < 2)
			{
				SetTextColor(hdc, RGB(255, 0, 0));//设置文字的颜色
				TextOut(hdc, Qxx, Qyy, "红方认输", 8);
			}
			else if (step.GetTail().n <= 17 && step.GetAt(step.FindIndex(step.GetCount() - 2)).n <= 17)
			{
				SetTextColor(hdc, RGB(0, 0, 0));//设置文字的颜色
				TextOut(hdc, Qxx, Qyy, "黑方认输", 8);
			}
			else if (step.GetTail().n <= 17 && step.GetAt(step.FindIndex(step.GetCount() - 2)).n > 17)
			{
				SetTextColor(hdc, RGB(255, 0, 0));//设置文字的颜色
				TextOut(hdc, Qxx, Qyy, "红方认输", 8);
			}
			else if (step.GetTail().n > 17 && step.GetAt(step.FindIndex(step.GetCount() - 2)).n <= 17)
			{
				SetTextColor(hdc, RGB(0, 0, 0));//设置文字的颜色
				TextOut(hdc, Qxx, Qyy, "黑方认输", 8);
			}
			else
			{
				SetTextColor(hdc, RGB(255, 0, 0));//设置文字的颜色
				TextOut(hdc, Qxx, Qyy, "红方认输", 8);
			}
		}
		IfGameOver = true;
		IfGameBegin = false;
		step.RemoveAll();
		if (MoShi == 2)
		{
			ifbtn2 = 1;
			Sendright = 3;
			kehu();
		}
	}
}

//退出游戏
void CChineseChessView::OnBtnDown3()
{
	if (MoShi == 1)
	{
		if (IDYES == AfxMessageBox("确认退出游戏？", MB_YESNO | MB_ICONQUESTION))
		{
			PostQuitMessage(0);
		}
	}
	else if (MoShi == 2)
	{
		if (IDYES == AfxMessageBox("确认退出游戏？", MB_YESNO | MB_ICONQUESTION))
		{
			ifbtn3 = 1;
			kehu();
			PostQuitMessage(0);

		}
	}
}

//和局
void CChineseChessView::OnBtnDown4()
{
	int Qxx, Qyy;
	if (IfGameOver)
	{
	}
	else if (MoShi == 1 && IfGameBegin)
	{
		SetBkMode(hdc, TRANSPARENT);//透明 
		SelectObject(hdc, CreateFont(80, 20, 0, 0, FW_HEAVY, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_RASTER_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, FF_SCRIPT, "黑体"));

		if (step.GetCount() < 2)
		{
			if (IDYES == AfxMessageBox("红方请求和局,是否同意？", MB_YESNO | MB_ICONQUESTION))
			{
				sndPlaySound(SoundfileName[3], SND_ASYNC | SND_NODEFAULT);
				for (Qxx = 0, Qyy = Qy; Qxx <= Qx + 4 * QL - 10; Qxx += 5, Qyy += 4)
				{
					G_Show();
					SetTextColor(hdc, RGB(255, 0, 0));//设置文字的颜色
					TextOut(hdc, Qxx, Qyy, "和局", 4);
				}
				IfGameOver = true;
				IfGameBegin = false;
				step.RemoveAll();
			}
			else
			{
				AfxMessageBox("黑方拒绝和棋");
			}
		}
		else if (step.GetTail().n <= 17 && step.GetAt(step.FindIndex(step.GetCount() - 2)).n <= 17)
		{
			if (IDYES == AfxMessageBox("黑方请求和局,是否同意？", MB_YESNO | MB_ICONQUESTION))
			{
				sndPlaySound(SoundfileName[3], SND_ASYNC | SND_NODEFAULT);
				for (Qxx = 0, Qyy = Qy; Qxx <= Qx + 3 * QL + 10; Qxx += 4, Qyy += 5)
				{
					G_Show();
					SetTextColor(hdc, RGB(0, 0, 0));//设置文字的颜色
					TextOut(hdc, Qxx, Qyy, "和局", 4);
				}
				IfGameOver = true;
				IfGameBegin = false;
				step.RemoveAll();
			}
			else
			{
				AfxMessageBox("红方拒绝和棋");
			}
		}
		else if (step.GetTail().n <= 17 && step.GetAt(step.FindIndex(step.GetCount() - 2)).n > 17)
		{
			if (IDYES == AfxMessageBox("红方请求和局,是否同意？", MB_YESNO | MB_ICONQUESTION))
			{
				sndPlaySound(SoundfileName[3], SND_ASYNC | SND_NODEFAULT);
				for (Qxx = 0, Qyy = Qy; Qxx <= Qx + 3 * QL + 10; Qxx += 4, Qyy += 5)
				{
					G_Show();
					SetTextColor(hdc, RGB(255, 0, 0));//设置文字的颜色
					TextOut(hdc, Qxx, Qyy, "和局", 4);
				}
				IfGameOver = true;
				IfGameBegin = false;
				step.RemoveAll();
			}
			else
			{
				AfxMessageBox("黑方拒绝和棋");
			}
		}
		else if (step.GetTail().n > 17 && step.GetAt(step.FindIndex(step.GetCount() - 2)).n <= 17)
		{
			if (IDYES == AfxMessageBox("黑方请求和局,是否同意？", MB_YESNO | MB_ICONQUESTION))
			{
				sndPlaySound(SoundfileName[3], SND_ASYNC | SND_NODEFAULT);
				for (Qxx = 0, Qyy = Qy; Qxx <= Qx + 3 * QL + 10; Qxx += 4, Qyy += 5)
				{
					G_Show();
					SetTextColor(hdc, RGB(0, 0, 0));//设置文字的颜色
					TextOut(hdc, Qxx, Qyy, "和局", 4);
				}
				IfGameOver = true;
				IfGameBegin = false;
				step.RemoveAll();
			}
			else
			{
				AfxMessageBox("红方拒绝和棋");
			}
		}
		else
		{
			if (IDYES == AfxMessageBox("红方请求和局,是否同意？", MB_YESNO | MB_ICONQUESTION))
			{
				sndPlaySound(SoundfileName[3], SND_ASYNC | SND_NODEFAULT);
				for (Qxx = 0, Qyy = Qy; Qxx <= Qx + 3 * QL + 10; Qxx += 4, Qyy += 5)
				{
					G_Show();
					SetTextColor(hdc, RGB(255, 0, 0));//设置文字的颜色
					TextOut(hdc, Qxx, Qyy, "和局", 4);
				}
				IfGameOver = true;
				IfGameBegin = false;
				step.RemoveAll();
			}
			else
			{
				AfxMessageBox("黑方拒绝和棋");
			}
		}
	}
	else if(MoShi == 2 && IfGameBegin && ifbtn==1)
	{
		SetBkMode(hdc, TRANSPARENT);//透明 
		SelectObject(hdc, CreateFont(80, 20, 0, 0, FW_HEAVY, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_RASTER_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, FF_SCRIPT, "黑体"));

		if (ifbtn4 == 0)
		{
			AfxMessageBox("请求已发送，等待对方回应");
		}
		else
		{
			if (ifbtn4 == 1)
			{
				if (step.GetCount() < 2)
				{
					if (IDYES == AfxMessageBox("红方请求和局,是否同意？", MB_YESNO | MB_ICONQUESTION))
					{
						ifbtn4 == 2;
						kehu();
						sndPlaySound(SoundfileName[3], SND_ASYNC | SND_NODEFAULT);
						for (Qxx = 0, Qyy = Qy; Qxx <= Qx + 4 * QL - 10; Qxx += 5, Qyy += 4)
						{
							G_Show();
							SetTextColor(hdc, RGB(255, 0, 0));//设置文字的颜色
							TextOut(hdc, Qxx, Qyy, "和局", 4);
						}
						IfGameOver = true;
						IfGameBegin = false;
						step.RemoveAll();
					}
					else
					{
						ifbtn4 == 3;
						kehu();
					}
				}
				else if (step.GetTail().n <= 17 && step.GetAt(step.FindIndex(step.GetCount() - 2)).n <= 17)
				{
					if (IDYES == AfxMessageBox("黑方请求和局,是否同意？", MB_YESNO | MB_ICONQUESTION))
					{
						ifbtn4 == 2;
						kehu();
						sndPlaySound(SoundfileName[3], SND_ASYNC | SND_NODEFAULT);
						for (Qxx = 0, Qyy = Qy; Qxx <= Qx + 3 * QL + 10; Qxx += 4, Qyy += 5)
						{
							G_Show();
							SetTextColor(hdc, RGB(0, 0, 0));//设置文字的颜色
							TextOut(hdc, Qxx, Qyy, "和局", 4);
						}
						IfGameOver = true;
						IfGameBegin = false;
						step.RemoveAll();
					}
					else
					{
						ifbtn4 == 3;
						kehu();
					}
				}
				else if (step.GetTail().n <= 17 && step.GetAt(step.FindIndex(step.GetCount() - 2)).n > 17)
				{
					if (IDYES == AfxMessageBox("红方请求和局,是否同意？", MB_YESNO | MB_ICONQUESTION))
					{
						ifbtn4 == 2;
						kehu();
						sndPlaySound(SoundfileName[3], SND_ASYNC | SND_NODEFAULT);
						for (Qxx = 0, Qyy = Qy; Qxx <= Qx + 3 * QL + 10; Qxx += 4, Qyy += 5)
						{
							G_Show();
							SetTextColor(hdc, RGB(255, 0, 0));//设置文字的颜色
							TextOut(hdc, Qxx, Qyy, "和局", 4);
						}
						IfGameOver = true;
						IfGameBegin = false;
						step.RemoveAll();
					}
					else
					{
						ifbtn4 == 3;
						kehu();
					}
				}
				else if (step.GetTail().n > 17 && step.GetAt(step.FindIndex(step.GetCount() - 2)).n <= 17)
				{
					if (IDYES == AfxMessageBox("黑方请求和局,是否同意？", MB_YESNO | MB_ICONQUESTION))
					{
						ifbtn4 == 2;
						kehu();
						sndPlaySound(SoundfileName[3], SND_ASYNC | SND_NODEFAULT);
						for (Qxx = 0, Qyy = Qy; Qxx <= Qx + 3 * QL + 10; Qxx += 4, Qyy += 5)
						{
							G_Show();
							SetTextColor(hdc, RGB(0, 0, 0));//设置文字的颜色
							TextOut(hdc, Qxx, Qyy, "和局", 4);
						}
						IfGameOver = true;
						IfGameBegin = false;
						step.RemoveAll();
					}
					else
					{
						ifbtn4 == 3;
						kehu();
					}
				}
				else if (step.GetTail().n > 17 && step.GetAt(step.FindIndex(step.GetCount() - 2)).n <= 17)
				{
					if (IDYES == AfxMessageBox("黑方请求和局,是否同意？", MB_YESNO | MB_ICONQUESTION))
					{
						ifbtn4 == 2;
						kehu();
						sndPlaySound(SoundfileName[3], SND_ASYNC | SND_NODEFAULT);
						for (Qxx = 0, Qyy = Qy; Qxx <= Qx + 3 * QL + 10; Qxx += 4, Qyy += 5)
						{
							G_Show();
							SetTextColor(hdc, RGB(0, 0, 0));//设置文字的颜色
							TextOut(hdc, Qxx, Qyy, "和局", 4);
						}
						IfGameOver = true;
						IfGameBegin = false;
						step.RemoveAll();
					}
					else
					{
						ifbtn4 == 3;
						kehu();
					}
				}
				else
				{
					if (IDYES == AfxMessageBox("红方请求和局,是否同意？", MB_YESNO | MB_ICONQUESTION))
					{
						ifbtn4 == 2;
						kehu();
						sndPlaySound(SoundfileName[3], SND_ASYNC | SND_NODEFAULT);
						for (Qxx = 0, Qyy = Qy; Qxx <= Qx + 3 * QL + 10; Qxx += 4, Qyy += 5)
						{
							G_Show();
							SetTextColor(hdc, RGB(255, 0, 0));//设置文字的颜色
							TextOut(hdc, Qxx, Qyy, "和局", 4);
						}
						IfGameOver = true;
						IfGameBegin = false;
						step.RemoveAll();
					}
					else
					{
						ifbtn4 == 3;
						kehu();
					}
				}
			}
			else if (ifbtn4 == 2)
			{
				if (step.GetCount() < 2)
				{
					sndPlaySound(SoundfileName[3], SND_ASYNC | SND_NODEFAULT);
					for (Qxx = 0, Qyy = Qy; Qxx <= Qx + 4 * QL - 10; Qxx += 5, Qyy += 4)
					{
						G_Show();
						SetTextColor(hdc, RGB(255, 0, 0));//设置文字的颜色
						TextOut(hdc, Qxx, Qyy, "和局", 4);
					}
					IfGameOver = true;
					IfGameBegin = false;
					step.RemoveAll();
				}
				else if (step.GetTail().n <= 17 && step.GetAt(step.FindIndex(step.GetCount() - 2)).n <= 17)
				{
					sndPlaySound(SoundfileName[3], SND_ASYNC | SND_NODEFAULT);
					for (Qxx = 0, Qyy = Qy; Qxx <= Qx + 3 * QL + 10; Qxx += 4, Qyy += 5)
					{
						G_Show();
						SetTextColor(hdc, RGB(0, 0, 0));//设置文字的颜色
						TextOut(hdc, Qxx, Qyy, "和局", 4);
					}
					IfGameOver = true;
					IfGameBegin = false;
					step.RemoveAll();
				}
				else if (step.GetTail().n <= 17 && step.GetAt(step.FindIndex(step.GetCount() - 2)).n > 17)
				{
					sndPlaySound(SoundfileName[3], SND_ASYNC | SND_NODEFAULT);
					for (Qxx = 0, Qyy = Qy; Qxx <= Qx + 3 * QL + 10; Qxx += 4, Qyy += 5)
					{
						G_Show();
						SetTextColor(hdc, RGB(255, 0, 0));//设置文字的颜色
						TextOut(hdc, Qxx, Qyy, "和局", 4);
					}
					IfGameOver = true;
					IfGameBegin = false;
					step.RemoveAll();
				}
				else if (step.GetTail().n > 17 && step.GetAt(step.FindIndex(step.GetCount() - 2)).n <= 17)
				{
					sndPlaySound(SoundfileName[3], SND_ASYNC | SND_NODEFAULT);
					for (Qxx = 0, Qyy = Qy; Qxx <= Qx + 3 * QL + 10; Qxx += 4, Qyy += 5)
					{
						G_Show();
						SetTextColor(hdc, RGB(255, 0, 0));//设置文字的颜色
						TextOut(hdc, Qxx, Qyy, "和局", 4);
					}
					IfGameOver = true;
					IfGameBegin = false;
					step.RemoveAll();
				}
				else if (step.GetTail().n > 17 && step.GetAt(step.FindIndex(step.GetCount() - 2)).n <= 17)
				{
					sndPlaySound(SoundfileName[3], SND_ASYNC | SND_NODEFAULT);
					for (Qxx = 0, Qyy = Qy; Qxx <= Qx + 3 * QL + 10; Qxx += 4, Qyy += 5)
					{
						G_Show();
						SetTextColor(hdc, RGB(0, 0, 0));//设置文字的颜色
						TextOut(hdc, Qxx, Qyy, "和局", 4);
					}
					IfGameOver = true;
					IfGameBegin = false;
					step.RemoveAll();
				}
				else
				{
					sndPlaySound(SoundfileName[3], SND_ASYNC | SND_NODEFAULT);
					for (Qxx = 0, Qyy = Qy; Qxx <= Qx + 3 * QL + 10; Qxx += 4, Qyy += 5)
					{
						G_Show();
						SetTextColor(hdc, RGB(255, 0, 0));//设置文字的颜色
						TextOut(hdc, Qxx, Qyy, "和局", 4);
					}
					IfGameOver = true;
					IfGameBegin = false;
					step.RemoveAll();
				}
			}
			else if (ifbtn4 == 3)
			{
				if (step.GetCount() < 2)
				{
					AfxMessageBox("黑方拒绝和棋");
				}
				else if (step.GetTail().n <= 17 && step.GetAt(step.FindIndex(step.GetCount() - 2)).n <= 17)
				{
					AfxMessageBox("红方拒绝和棋");
				}
				else if (step.GetTail().n <= 17 && step.GetAt(step.FindIndex(step.GetCount() - 2)).n > 17)
				{
					AfxMessageBox("黑方拒绝和棋");
				}
				else if (step.GetTail().n > 17 && step.GetAt(step.FindIndex(step.GetCount() - 2)).n <= 17)
				{
					AfxMessageBox("红方拒绝和棋");
				}
				else if (step.GetTail().n > 17 && step.GetAt(step.FindIndex(step.GetCount() - 2)).n <= 17)
				{
					AfxMessageBox("红方拒绝和棋");
				}
				else
				{
					AfxMessageBox("黑方拒绝和棋");
				}
			}
		}
	}
}

//鼠标左键点击消息响应
void CChineseChessView::OnLButtonDown(UINT nFlags, CPoint point)//////////////////////////////
{
	if (abs(point.x - 612) <= 5 && abs(point.y - 63) <= 5)
	{
		PlayBGM();
		G_Show();
	}
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	int NewX, NewY;		//棋子坐标
	int i;
	if (step.GetCount() >= 2)
	{
		step2 = step.GetAt(step.FindIndex(step.GetCount() - 2));
	}

	if (!IfGameOver && ((MoShi == 1 && IfGameBegin) || (MoShi == 2 && ifbtn == 1 && IfGameBegin == 1)))		//比赛未结束 且 单机模式比赛开始 且 局域网模式是双方都准备
	{
		if (point.x > 50 && point.x < 50 + 9 * QL && point.y>30 && point.y < 30 + 10 * QL)	//棋盘范围
		{
			//得到棋子坐标
			NewX = (point.x - Qx) % QL;
			NewY = (point.y - Qy) % QL;

			if (NewX > 5 && NewX < 52 && NewY>5 && NewY < 52)
			{
				StepCount++;

				//精确点的坐标到十字中心
				NewX = point.x - NewX;
				NewY = point.y - NewY;

				if (MoShi == 1)
				{
					ConsoleGame(NewX, NewY);
				}
				else if (MoShi == 2)
				{
					LANGame(NewX, NewY);
				}
				GameOver();
			}
		}
	}
	CView::OnLButtonDown(nFlags, point);
}

//将或帅被吃，比赛结束
void GameOver()
{
	if (qz[2].x == -100 && qz[2].y == -100 || qz[18].x == -100 && qz[18].y == -100)		
	{
		sndPlaySound(SoundfileName[1], SND_ASYNC | SND_NODEFAULT);

		SetTextColor(hdc, RGB(255, 0, 0));//设置文字的颜色     
		SetBkMode(hdc, TRANSPARENT);//透明 
		SelectObject(hdc, CreateFont(80, 20, 0, 0, FW_HEAVY, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_RASTER_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, FF_SCRIPT, "黑体"));
		for (int Qxx = 0, Qyy = Qy; Qxx <= Qx + 3 * QL; Qxx += 5, Qyy += 5)
		{
			G_Show();
			TextOut(hdc, Qxx, Qyy, "GAME OVER", 9);
		}
		IfGameOver = true;
		IfGameBegin = false;
		ifbtn = 0;
	}
}

//单机游戏
void CChineseChessView::ConsoleGame(int NewX, int NewY)
{
	int i;
	for (i = 2; i <= 33; i++)
	{
		if (NewX == qz[i].x + Qx&&NewY == qz[i].y + Qy)	//搜索是否有棋子被选中
		{
			step1.n = i;
			step1.x = NewX - Qx;
			step1.y = NewY - Qy;
			if (StepCount % 2 == 1)			//选棋
			{
				if (!step.IsEmpty())		//如果链表不为空
				{
					if ((step2.n <= 17 && step1.n <= 17) || (step2.n > 17 && step1.n > 17))	//红黑棋子交换下子
					{
						StepCount--;
					}
					else
					{
						sndPlaySound(SoundfileName[4], SND_ASYNC | SND_NODEFAULT);
						if (!step.IsEmpty())
						{
							qz[qz[step2.n].s].x = -100;			//将上一步带框图片去掉
							qz[qz[step2.n].s].y = -100;
						}
						qz[48].x = NewX - Qx;			//将选中棋子带框
						qz[48].y = NewY - Qy;
						step.AddTail(step1);
					}
				}
				else
				{
					sndPlaySound(SoundfileName[4], SND_ASYNC | SND_NODEFAULT);
					qz[48].x = NewX - Qx;
					qz[48].y = NewY - Qy;
					step.AddTail(step1);
				}
			}
			else//吃子
			{
				if ((step.GetTail().n <= 17 && step1.n <= 17) || (step.GetTail().n > 17 && step1.n > 17))	//不能吃己方棋子 | 重新选棋
				{
					sndPlaySound(SoundfileName[4], SND_ASYNC | SND_NODEFAULT);
					qz[48].x = NewX - Qx;		//将选中棋子带框
					qz[48].y = NewY - Qy;

					step.GetTail().n = step1.n;		//将链表最后一元素替换
					step.GetTail().x = NewX - Qx;
					step.GetTail().y = NewY - Qy;
					StepCount--;
				}
				else
				{
					if (Rules())
					{
						sndPlaySound(SoundfileName[5], SND_ASYNC | SND_NODEFAULT);
						qz[step1.n].x = -100;		//将被吃棋子图片去掉
						qz[step1.n].y = -100;
						qz[step.GetTail().n].x = NewX - Qx;		//将上一次选中棋子移至被吃棋子位置
						qz[step.GetTail().n].y = NewY - Qy;
						qz[qz[step.GetTail().n].s].x = NewX - Qx;	//将上一次选中棋子带框
						qz[qz[step.GetTail().n].s].y = NewY - Qy;

						if (killking() == 1 && (18 <= step.GetTail().n&& step.GetTail().n <= 33) || killking() == 2 && (2 <= step.GetTail().n&&step.GetTail().n <= 17))
						{
							sndPlaySound(SoundfileName[7], SND_ASYNC | SND_NODEFAULT);
							qz[step1.n].x = NewX - Qx;
							qz[step1.n].y = NewY - Qy;
							qz[step.GetTail().n].x = step.GetTail().x;
							qz[step.GetTail().n].y = step.GetTail().y;
							qz[qz[step.GetTail().n].s].x = -100;
							qz[qz[step.GetTail().n].s].y = -100;
							StepCount--;
						}
						else
						{
							step.AddTail(step1);
						}
					}
					else
					{
						sndPlaySound(SoundfileName[7], SND_ASYNC | SND_NODEFAULT);
						StepCount--;
					}
				}
			}
			break;
		}
	}

	if (i == 34)		//没选中棋子
	{
		if (StepCount % 2 == 1)		//重选
		{
			StepCount--;
		}
		else//下子
		{
			sndPlaySound(SoundfileName[6], SND_ASYNC | SND_NODEFAULT);
			step1.n = 0;
			step1.x = NewX - Qx;
			step1.y = NewY - Qy;
			if (Rules())
			{
				qz[step.GetTail().n].x = NewX - Qx;
				qz[step.GetTail().n].y = NewY - Qy;
				qz[qz[step.GetTail().n].s].x = NewX - Qx;
				qz[qz[step.GetTail().n].s].y = NewY - Qy;

				if (killking() == 1 && (18 <= step.GetTail().n&& step.GetTail().n <= 33) || killking() == 2 && (2 <= step.GetTail().n&&step.GetTail().n <= 17))
				{
					sndPlaySound(SoundfileName[7], SND_ASYNC | SND_NODEFAULT);
					qz[step.GetTail().n].x = step.GetTail().x;
					qz[step.GetTail().n].y = step.GetTail().y;
					qz[qz[step.GetTail().n].s].x = -100;
					qz[qz[step.GetTail().n].s].y = -100;
					StepCount--;
				}
				else
				{
					step.AddTail(step1);
				}
			}
			else
			{
				sndPlaySound(SoundfileName[7], SND_ASYNC | SND_NODEFAULT);
				StepCount--;
			}
		}
	}
	G_Show();			//更新棋盘
}

//局域网游戏
void CChineseChessView::LANGame(int NewX, int NewY)
{
	if (right == 2)
	{
		int i;
		for (i = 2; i <= 33; i++)
		{
			if (NewX == qz[i].x + Qx&&NewY == qz[i].y + Qy)	//搜索是否有棋子被选中
			{
				step1.n = i;
				step1.x = NewX - Qx;
				step1.y = NewY - Qy;
				if (StepCount % 2 == 1)			//选棋
				{
					if (!step.IsEmpty())
					{
						if ((step2.n <= 17 && step1.n <= 17) || (step2.n > 17 && step1.n > 17))	//红黑棋子交换下子
						{
							StepCount--;
						}
						else
						{
							sndPlaySound(SoundfileName[4], SND_ASYNC | SND_NODEFAULT);
							if (!step.IsEmpty())
							{
								qz[qz[step2.n].s].x = -100;
								qz[qz[step2.n].s].y = -100;
							}
							qz[48].x = NewX - Qx;
							qz[48].y = NewY - Qy;
							step.AddTail(step1);
							
							//发送1,n,x,y
							Sendright = 1;
							kehu();

						}
					}
					else
					{
						sndPlaySound(SoundfileName[4], SND_ASYNC | SND_NODEFAULT);
						if (!step.IsEmpty())
						{
							qz[qz[step2.n].s].x = -100;
							qz[qz[step2.n].s].y = -100;
						}
						qz[48].x = NewX - Qx;
						qz[48].y = NewY - Qy;
						step.AddTail(step1);

						//发送1,n,x,y
						Sendright = 1;
						kehu();
					}
				}
				else//吃子
				{
					if ((step.GetTail().n <= 17 && step1.n <= 17) || (step.GetTail().n > 17 && step1.n > 17))	//不能吃己方棋子 | 重新选棋
					{
						sndPlaySound(SoundfileName[4], SND_ASYNC | SND_NODEFAULT);
						qz[48].x = NewX - Qx;
						qz[48].y = NewY - Qy;

						step.GetTail().n = step1.n;
						step.GetTail().x = NewX - Qx;
						step.GetTail().y = NewY - Qy;
						StepCount--;
						Sendright = 4;
						kehu();
					}
					else
					{
						if (Rules())
						{
							sndPlaySound(SoundfileName[5], SND_ASYNC | SND_NODEFAULT);
							qz[step1.n].x = -100;
							qz[step1.n].y = -100;
							qz[step.GetTail().n].x = NewX - Qx;
							qz[step.GetTail().n].y = NewY - Qy;
							qz[qz[step.GetTail().n].s].x = NewX - Qx;
							qz[qz[step.GetTail().n].s].y = NewY - Qy;

							if (killking() == 1 && (18 <= step.GetTail().n&& step.GetTail().n <= 33) || killking() == 2 && (2 <= step.GetTail().n&&step.GetTail().n <= 17))
							{
								sndPlaySound(SoundfileName[7], SND_ASYNC | SND_NODEFAULT);
								qz[step1.n].x = NewX - Qx;
								qz[step1.n].y = NewY - Qy;
								qz[step.GetTail().n].x = step.GetTail().x;
								qz[step.GetTail().n].y = step.GetTail().y;
								qz[qz[step.GetTail().n].s].x = -100;
								qz[qz[step.GetTail().n].s].y = -100;
								StepCount--;
							}
							else
							{
								step.AddTail(step1);
							}

							//发送2,n,x,y
							Sendright = 2;
							kehu();
							right = 0;
						}
						else
						{
							sndPlaySound(SoundfileName[7], SND_ASYNC | SND_NODEFAULT);
							StepCount--;
						}
					}
				}
				break;
			}
		}

		if (i == 34)		//没选中棋子
		{
			if (StepCount % 2 == 1)		//重选
			{
				StepCount--;
			}
			else//下子
			{
				sndPlaySound(SoundfileName[6], SND_ASYNC | SND_NODEFAULT);
				step1.n = 0;
				step1.x = NewX - Qx;
				step1.y = NewY - Qy;
				if (Rules())
				{
					qz[step.GetTail().n].x = NewX - Qx;
					qz[step.GetTail().n].y = NewY - Qy;
					qz[qz[step.GetTail().n].s].x = NewX - Qx;
					qz[qz[step.GetTail().n].s].y = NewY - Qy;
					if (killking() == 1 && (18 <= step.GetTail().n&& step.GetTail().n <= 33) || killking() == 2 && (2 <= step.GetTail().n&&step.GetTail().n <= 17))
					{
						sndPlaySound(SoundfileName[7], SND_ASYNC | SND_NODEFAULT);
						qz[step.GetTail().n].x = step.GetTail().x;
						qz[step.GetTail().n].y = step.GetTail().y;
						qz[qz[step.GetTail().n].s].x = -100;
						qz[qz[step.GetTail().n].s].y = -100;
						StepCount--;
					}
					else
					{
						step.AddTail(step1);
					}
					//发送2,n,x,y
					Sendright = 2;
					kehu();
					right = 0;
				}
				else
				{
					sndPlaySound(SoundfileName[7], SND_ASYNC | SND_NODEFAULT);
					StepCount--;
				}
			}
		}
		G_Show();
	}//更新棋盘
}

//下棋规则
bool CChineseChessView::Rules()
{
	int j, k = 0;

	//帅的规则
	if (qz[step.GetTail().n].s == 34)
	{
		if ((step.GetTail().x == step1.x  && abs(step.GetTail().y - step1.y) == QL) || (step.GetTail().y == step1.y && abs(step.GetTail().x - step1.x) == QL))
		{
			if (abs((step1.y - 456) / QL) <= 1 && abs((step1.x - 228) / QL) <= 1)
			{
				return true;
			}
			else
				return false;
		}
		else
			return false;
	}

	//将的规则
	else if (qz[step.GetTail().n].s == 41)
	{
		if ((step.GetTail().x == step1.x  && abs(step.GetTail().y - step1.y) == QL) || (step.GetTail().y == step1.y && abs(step.GetTail().x - step1.x) == QL))
		{
			if (abs((step1.y - 57) / QL) <= 1 && abs((step1.x - 228) / QL) <= 1)
			{
				return true;
			}
			else
				return false;
		}
		else
			return false;
	}

	//仕\士的规则
	else if (qz[step.GetTail().n].s == 35 || qz[step.GetTail().n].s == 42)
	{
		if (qz[step.GetTail().n].s == 35)
		{
			if ((abs(step.GetTail().x - step1.x) == QL&& abs(step.GetTail().y - step1.y) == QL))
			{
				if (abs((step1.y - 456) / QL) <= 1 && abs((step1.x - 228) / QL) <= 1)
				{
					return true;
				}
				else
					return false;
			}
			else
				return false;
		}
		else
		{
			if ((abs(step.GetTail().x - step1.x) == QL&& abs(step.GetTail().y - step1.y) == QL))
			{
				if (abs((step1.y - 57) / QL) <= 1 && abs((step1.x - 228) / QL) <= 1)
				{
					return true;
				}
				else
					return false;
			}
			else
				return false;

		}
	}

	//相\象的规则
	else if (qz[step.GetTail().n].s == 36 || qz[step.GetTail().n].s == 43)
	{
		if (abs(step1.x - step.GetTail().x) / QL == 2 && abs(step1.y - step.GetTail().y) / QL == 2)
		{
			for (k = 2; k <= 33; k++)
			{
				if ((qz[k].x == step.GetTail().x - QL && qz[k].y == step.GetTail().y - QL) && (step1.x == step.GetTail().x - 2 * QL && step1.y == step.GetTail().y - 2 * QL))		//左上
				{
					return false;
				}
				else if ((qz[k].x == step.GetTail().x - QL && qz[k].y == step.GetTail().y + QL) && (step1.x == step.GetTail().x - 2 * QL && step1.y == step.GetTail().y + 2 * QL))	//左下
				{
					return false;
				}
				else if ((qz[k].x == step.GetTail().x + QL && qz[k].y == step.GetTail().y - QL) && (step1.x == step.GetTail().x + 2 * QL && step1.y == step.GetTail().y - 2 * QL))	//右上
				{
					return false;
				}
				else if ((qz[k].x == step.GetTail().x + QL && qz[k].y == step.GetTail().y + QL) && (step1.x == step.GetTail().x + 2 * QL && step1.y == step.GetTail().y + 2 * QL))	//右下
				{
					return false;
				}
			}
			if (qz[step.GetTail().n].s == 36 && (step1.y - Qy) / QL < 4)
			{
				return false;
			}
			else if (qz[step.GetTail().n].s == 43 && (step1.y - Qy) / QL > 4)
			{
				return false;
			}
			else
			{
				return true;
			}
		}
		else
		{
			return false;
		}
	}

	//马\馬的规则
	else if (qz[step.GetTail().n].s == 37 || qz[step.GetTail().n].s == 44)
	{

		if ((abs(step1.x - step.GetTail().x) / QL == 1 && abs(step1.y - step.GetTail().y) / QL == 2))//日字吃子
		{
			for (k = 2; k <= 33; k++)
			{
				if ((qz[k].x == step.GetTail().x && qz[k].y == step.GetTail().y - QL) && ((step1.y - step.GetTail().y)) / QL < 0)//判定蹩上马腿
				{
					return false;
				}
				else if ((qz[k].x == step.GetTail().x && qz[k].y == step.GetTail().y + QL) && ((step1.y - step.GetTail().y)) / QL > 0)//判定蹩下马腿
				{
					return false;
				}
			}

			return true;
		}
		else if ((abs(step1.x - step.GetTail().x) / QL == 2 && abs(step1.y - step.GetTail().y) / QL == 1))	//吅字吃子
		{
			for (k = 2; k <= 33; k++)//判定上蹩马腿
			{
				if ((qz[k].y == step.GetTail().y && qz[k].x == step.GetTail().x - QL) && ((step1.x - step.GetTail().x)) / QL < 0)//判定蹩上马腿
				{
					return false;
				}
				else if ((qz[k].y == step.GetTail().y && qz[k].x == step.GetTail().x + QL) && ((step1.x - step.GetTail().x)) / QL > 0)//判定蹩上马腿
				{
					return false;
				}

			}
			return true;
		}
		else
		{
			return false;
		}
	}

	//车\車的规则
	else if (qz[step.GetTail().n].s == 38 || qz[step.GetTail().n].s == 45)
	{
		int max, min;
		//int t=0;//判断车是否将军的计数器
		if ((step.GetTail().x == step1.x || step.GetTail().y == step1.y))		//走直线
		{
			if (step.GetTail().x == step1.x)		//走行
			{
				max = max(step.GetTail().y, step1.y);
				min = min(step.GetTail().y, step1.y);

				for (k = min + QL; k < max; k += QL)
				{
					for (j = 2; j <= 33; j++)
					{
						if (qz[j].x == step1.x && qz[j].y == k)
						{
							break;
						}
					}
					if (j <= 33)
					{
						break;
					}
				}


			}
			else if (step.GetTail().y == step1.y)	//走列
			{
				max = max(step.GetTail().x, step1.x);
				min = min(step.GetTail().x, step1.x);

				for (k = min + QL; k < max; k += QL)
				{
					for (j = 2; j <= 33; j++)
					{
						if (qz[j].x == k && qz[j].y == step1.y)
						{
							break;
						}
					}
					if (j <= 33)
					{
						break;
					}
				}
			}
			if (k < max && k != 0)
			{
				return false;
			}
			else
			{

				return true;
			}
		}
		else
		{
			return false;
		}

	}

	//砲\炮的规则
	else if (qz[step.GetTail().n].s == 39 || qz[step.GetTail().n].s == 46)
	{
		int max, min, Count = 0;
		//int t = 0;//将军警示计数器
		if ((step.GetTail().x == step1.x || step.GetTail().y == step1.y))		//走直线
		{
			if (step1.n != 0)//炮的吃子
			{
				if (step.GetTail().x == step1.x)		//走行
				{
					max = max(step.GetTail().y, step1.y);
					min = min(step.GetTail().y, step1.y);

					for (k = min + QL; k < max; k += QL)
					{
						for (j = 2; j <= 33; j++)
						{
							if (qz[j].x == step1.x && qz[j].y == k)
							{
								Count++;
							}
						}
					}
				}
				else if (step.GetTail().y == step1.y)	//走列
				{
					max = max(step.GetTail().x, step1.x);
					min = min(step.GetTail().x, step1.x);

					for (k = min + QL; k < max; k += QL)
					{
						for (j = 2; j <= 33; j++)
						{
							if (qz[j].x == k && qz[j].y == step1.y)
							{
								Count++;
							}
						}
					}
				}
				if (Count == 1)
				{

					return true;

				}
				else
				{
					return false;
				}
			}
			else//炮的移动
			{
				if (step.GetTail().x == step1.x)		//走行
				{
					max = max(step.GetTail().y, step1.y);
					min = min(step.GetTail().y, step1.y);

					for (k = min + QL; k < max; k += QL)
					{
						for (j = 2; j <= 33; j++)
						{
							if (qz[j].x == step1.x && qz[j].y == k)
							{
								break;
							}
						}
						if (j <= 33)
						{
							break;
						}
					}
				}
				else if (step.GetTail().y == step1.y)	//走列
				{
					max = max(step.GetTail().x, step1.x);
					min = min(step.GetTail().x, step1.x);

					for (k = min + QL; k < max; k += QL)
					{
						for (j = 2; j <= 33; j++)
						{
							if (qz[j].x == k && qz[j].y == step1.y)
							{
								break;
							}
						}
						if (j <= 33)
						{
							break;
						}
					}
				}
				if (k < max && k != 0)
				{
					return false;
				}
				else
				{

					return true;
				}
			}
		}
		else
		{
			return false;
		}
	}

	//兵\卒的规则
	else if (qz[step.GetTail().n].s == 40 || qz[step.GetTail().n].s == 47)
	{
		if ((step.GetTail().x == step1.x  && abs(step.GetTail().y - step1.y) == QL) || (step.GetTail().y == step1.y && abs(step.GetTail().x - step1.x) == QL))
		{
			if (qz[step.GetTail().n].s == 40)
			{
				if (step1.y - step.GetTail().y == QL)
				{
					return false;
				}
				else
				{
					if ((step1.y - Qy) / QL < 4)
					{
						return true;
					}
					else
					{
						if (step.GetTail().y - step1.y == QL)
						{
							return true;
						}
						else
							return false;
					}
				}
			}
			else
			{
				if (step.GetTail().y - step1.y == QL)
				{
					return false;
				}
				else
				{
					if ((step1.y - Qy) / QL >= 4)
					{
						return true;
					}
					else
					{
						if (step1.y - step.GetTail().y == QL)
						{
							return true;
						}
						else
							return false;
					}
				}
			}
		}
		else
			return false;
	}
}

//判定将军 返回值0表示没有将军情况 返回值1表示红方将军黑方 返回值2表示黑方将军红方
int killking()
{
	int t = 0;
	int k = 0;//判断是否在不蹩马腿的情况下提示将军的计数器

	for (int i = 2; i < 34; i++)
	{
		//马判断将军
		if (qz[i].s == 37 || qz[i].s == 44)
		{
			if ((abs(qz[18].x - qz[i].x) / QL == 1 && abs(qz[18].y - qz[i].y) / QL == 2) && qz[i].s == 37)//红马判断将军
			{

				for (k = 2; k <= 33; k++)
				{
					if ((qz[k].x == qz[i].x && qz[k].y == qz[i].y - QL) && ((qz[18].y - qz[i].y)) / QL < 0)//判定蹩上马腿
					{
						t++;
					}
					else if ((qz[k].x == qz[i].x&& qz[k].y == qz[i].y + QL) && ((qz[18].y - qz[i].y)) / QL > 0)//判定蹩下马腿
					{
						t++;
					}
				}
				if (t == 0)//播放将军警报声
				{
					sndPlaySound(SoundfileName[8], SND_ASYNC | SND_NODEFAULT);
					return 1;
				}

			}
			t = 0;
			if ((abs(qz[2].x - qz[i].x) / QL == 1 && abs(qz[2].y - qz[i].y) / QL == 2) && qz[i].s == 44)//黑马判断将军
			{

				for (k = 2; k <= 33; k++)
				{
					if ((qz[k].x == qz[i].x && qz[k].y == qz[i].y - QL) && ((qz[2].y - qz[i].y)) / QL < 0)//判定蹩上马腿
					{
						t++;
					}
					else if ((qz[k].x == qz[i].x&& qz[k].y == qz[i].y + QL) && ((qz[2].y - qz[i].y)) / QL > 0)//判定蹩下马腿
					{
						t++;
					}
				}
				if (t == 0)//播放将军警报声
				{
					sndPlaySound(SoundfileName[8], SND_ASYNC | SND_NODEFAULT);
					return 2;
				}
			}
			t = 0;
			if ((abs(qz[18].x - qz[i].x) / QL == 2 && abs(qz[18].y - qz[i].y) / QL == 1) && qz[i].s == 37)//红马判定将军
			{

				for (k = 2; k <= 33; k++)//判定上蹩马腿
				{
					if ((qz[k].y == qz[i].y && qz[k].x == qz[i].x - QL) && ((qz[18].x - qz[i].x)) / QL < 0)//判定蹩上马腿
					{
						t++;
					}
					else if ((qz[k].y == qz[i].y && qz[k].x == qz[i].x + QL) && ((qz[18].x - qz[i].x)) / QL > 0)//判定蹩上马腿
					{
						t++;
					}
				}
				if (t == 0)//播放将军警报声
				{
					sndPlaySound(SoundfileName[8], SND_ASYNC | SND_NODEFAULT);
					return 1;
				}
			}
			t = 0;
			if ((abs(qz[2].x - qz[i].x) / QL == 2 && abs(qz[2].y - qz[i].y) / QL == 1) && qz[i].s == 44)//黑马判定将军
			{

				for (k = 2; k <= 33; k++)//判定上蹩马腿
				{
					if ((qz[k].y == qz[i].y && qz[k].x == qz[i].x - QL) && ((qz[2].x - qz[i].x)) / QL < 0)//判定蹩上马腿
					{
						t++;
					}
					else if ((qz[k].y == qz[i].y && qz[k].x == qz[i].x + QL) && ((qz[2].x - qz[i].x)) / QL > 0)//判定蹩上马腿
					{
						t++;
					}
				}
				if (t == 0)//播放将军警报声
				{
					sndPlaySound(SoundfileName[8], SND_ASYNC | SND_NODEFAULT);
					return 2;
				}
			}
		}

		////车\車警报
		if (qz[i].s == 38 || qz[i].s == 45)
		{
			int max = 0;
			int min = 0;
			int j = 0;
			if (qz[i].s == 38)//红车将军警报
			{
				if ((qz[i].x == qz[18].x || qz[i].y == qz[18].y))
				{
					if (qz[i].x == qz[18].x)		//走行
					{
						max = max(qz[i].y, qz[18].y);
						min = min(qz[i].y, qz[18].y);

						for (k = min + QL; k < max; k += QL)
						{
							for (j = 2; j <= 33; j++)
							{
								if (qz[j].x == qz[18].x && qz[j].y == k&&qz[j].s != 38)
								{
									break;
								}
							}
							if (j <= 33)
							{
								break;
							}
						}
					}

					else if (qz[i].y == qz[18].y)	//走列
					{
						max = max(qz[i].x, qz[18].x);
						min = min(qz[i].x, qz[18].x);

						for (k = min + QL; k < max; k += QL)
						{
							for (j = 2; j <= 33; j++)
							{
								if (qz[j].x == k && qz[j].y == qz[18].y&&qz[j].s != 38)
								{
									break;
								}
							}
							if (j <= 33)
							{
								break;
							}
						}
					}
					if (k < max && k != 0)
					{
						t++;
					}
					else
					{
						t = 0;
					}

				}
				else
				{
					t++;
				}
				if (t == 0)//播放将军警报声
				{
					sndPlaySound(SoundfileName[8], SND_ASYNC | SND_NODEFAULT);
					t = 0;
					return 1;
				}
			}
			if (qz[i].s == 45)//黑车将军警报
			{
				int max = 0;
				int min = 0;
				if ((qz[i].x == qz[2].x || qz[i].y == qz[2].y))
				{
					if (qz[i].x == qz[2].x)		//走行
					{
						max = max(qz[i].y, qz[2].y);
						min = min(qz[i].y, qz[2].y);

						for (k = min + QL; k < max; k += QL)
						{
							for (j = 2; j <= 33; j++)
							{
								if (qz[j].x == qz[2].x && qz[j].y == k&&qz[j].s != 45)
								{
									break;
								}
							}
							if (j <= 33)
							{
								break;
							}
						}
					}

					else if (qz[i].y == qz[2].y)	//走列
					{
						max = max(qz[i].x, qz[2].x);
						min = min(qz[i].x, qz[2].x);

						for (k = min + QL; k < max; k += QL)
						{
							for (j = 2; j <= 33; j++)
							{
								if (qz[j].x == k && qz[j].y == qz[2].y&&qz[j].s != 45)
								{
									break;
								}
							}
							if (j <= 33)
							{
								break;
							}
						}
					}
					if (k < max && k != 0)
					{
						t++;
					}
					else
					{
						t = 0;
					}/////////

				}
				else
				{
					t++;
				}
				if (t == 0)//播放将军警报声
				{
					sndPlaySound(SoundfileName[8], SND_ASYNC | SND_NODEFAULT);
					t = 0;
					return 2;
				}

			}
		}

		//炮的警报
		if (qz[i].s == 39 || qz[i].s == 46)
		{
			int Count1 = 0;//红炮将军间隔计数器
			int max = 0;
			int min = 0;
			int j = 0;
			if (qz[i].s == 39)//红炮的将军警示器
			{
				if ((qz[i].x == qz[18].x || qz[i].y == qz[18].y))
				{
					if (qz[i].x == qz[18].x)		//走行
					{
						max = max(qz[i].y, qz[18].y);
						min = min(qz[i].y, qz[18].y);

						for (k = min + QL; k < max; k += QL)
						{
							for (j = 2; j <= 33; j++)
							{
								if (qz[j].x == qz[18].x && qz[j].y == k&& qz[j].s != 39)
								{
									Count1++;
								}
							}
						}
					}
					else if (qz[i].y == qz[18].y)	//走列
					{
						max = max(qz[i].x, qz[18].x);
						min = min(qz[i].x, qz[18].x);

						for (k = min + QL; k < max; k += QL)
						{
							for (j = 2; j <= 33; j++)
							{
								if (qz[j].x == k && qz[j].y == qz[18].y&& qz[j].s != 39)
								{
									Count1++;
								}
							}
						}
					}
					if (Count1 == 1)
					{
						t = 0;
					}
					else
					{
						t++;
					}
					if (t == 0)//播放将军警报声
					{
						sndPlaySound(SoundfileName[8], SND_ASYNC | SND_NODEFAULT);
						t = 0;
						return 1;

					}

				}
			}//////////
			if (qz[i].s == 46)//黑炮的将军警示器
			{
				if ((qz[i].x == qz[2].x || qz[i].y == qz[2].y))
				{
					int Count2 = 0;
					if (qz[i].x == qz[2].x)		//走行
					{
						max = max(qz[i].y, qz[2].y);
						min = min(qz[i].y, qz[2].y);

						for (k = min + QL; k < max; k += QL)
						{
							for (j = 2; j <= 33; j++)
							{
								if (qz[j].x == qz[2].x && qz[j].y == k&& qz[j].s != 46)
								{
									Count2++;
								}
							}
						}
					}
					else if (qz[i].y == qz[2].y)	//走列
					{
						max = max(qz[i].x, qz[2].x);
						min = min(qz[i].x, qz[2].x);

						for (k = min + QL; k < max; k += QL)
						{
							for (j = 2; j <= 33; j++)
							{
								if (qz[j].x == k && qz[j].y == qz[2].y&& qz[j].s != 46)
								{
									Count2++;
								}
							}
						}
					}
					if (Count2 == 1)
					{
						t = 0;
					}
					else
					{
						t++;
					}
					if (t == 0)//播放将军警报声
					{
						sndPlaySound(SoundfileName[8], SND_ASYNC | SND_NODEFAULT);
						t = 0;
						return 2;
					}

				}
			}
		}

		//兵/卒报警
		if (qz[i].s == 40 || qz[i].s == 47)
		{

			if (qz[i].s == 40 && qz[i].y == qz[18].y || qz[i].x == qz[18].x)//红兵判定
			{
				if (qz[i].y == qz[18].y&&abs(qz[i].x - qz[18].x) == QL)
				{

					sndPlaySound(SoundfileName[8], SND_ASYNC | SND_NODEFAULT);
					t = 0;
					return 1;
				}
				else if (qz[i].x == qz[18].x&&qz[i].y - qz[18].y == QL)
				{
					sndPlaySound(SoundfileName[8], SND_ASYNC | SND_NODEFAULT);
					t = 0;
					return 1;
				}
			}
			else if (qz[i].s == 47 && qz[i].y == qz[2].y || qz[i].x == qz[2].x)//黑兵判定
			{
				if (qz[i].y == qz[2].y&&abs(qz[i].x - qz[2].x) == QL)
				{

					sndPlaySound(SoundfileName[8], SND_ASYNC | SND_NODEFAULT);
					t = 0;
					return 2;
				}
				else if (qz[i].x == qz[2].x&&qz[2].y - qz[i].y == QL)
				{
					sndPlaySound(SoundfileName[8], SND_ASYNC | SND_NODEFAULT);
					t = 0;
					return 2;
				}
			}
		}
	}
	return 0;
}

//播放背景音乐
void CChineseChessView::PlayBGM()
{
	if (IfTick)
	{
		IfTick = FALSE;
		mciSendString("close 声音//TheClimb.mp3", NULL, 0, NULL);
	}
	else
	{
		IfTick = TRUE;
		mciSendString("open 声音//TheClimb.mp3", NULL, 0, NULL);
		mciSendString("play 声音//TheClimb.mp3", NULL, 0, NULL);
		SetTimer(1, 236000, 0);
	}
}

//定时器
void CChineseChessView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch (nIDEvent)
	{
	case 1:
	{
		if (IfTick)
		{
			mciSendString("close 声音//TheClimb.mp3", NULL, 0, NULL);
			mciSendString("open 声音//TheClimb.mp3", NULL, 0, NULL);
			mciSendString("play 声音//TheClimb.mp3", NULL, 0, NULL);
		}
		break;
	}
	case 2:
	{
		if (!IfGameOver)
		{
			if (ifbtn1 == 1)
			{
				ifbtn1 = 0;
				OnBtnDown1();
			}
			else if (ifbtn2 == 1)
			{
				ifbtn2 = 0;
				OnBtnDown2();
			}
			else if (ifbtn3 == 1)
			{
				ifbtn3 = 0;
				AfxMessageBox("对方已退出游戏，现准备关闭窗口");
				PostQuitMessage(0);
			}
			else if (ifbtn4 != 0)
			{
				OnBtnDown4();
			}
			GameOver();
		}
		break;
	}
	default:
		break;
	}
	

	CView::OnTimer(nIDEvent);
}

//发送坐标
void kehu()
{
	WSADATA ws;
	SOCKET client;
	SOCKADDR_IN client_addr;
	int Ret;
	CString  bufferx;//缓存x
	char buf[MAX_PATH];
	char buf1[MAX_PATH];
	int t = 0;
	int t1 = 0;

	pointx.Format("%d", step1.x);
	pointy.Format("%d", step1.y);
	pointn.Format("%d", step1.n);
	point01.Format("%d", Sendright);
	pointbtn.Format("%d", IfGameBegin);
	pointbtn1.Format("%d", ifbtn1);
	pointbtn2.Format("%d", ifbtn2);
	pointbtn3.Format("%d", ifbtn3);
	pointbtn4.Format("%d", ifbtn4);

	if (WSAStartup(MAKEWORD(2, 2), &ws) != 0)
	{
		AfxMessageBox(_T("WSAStartup Failed"));
	}
	client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (client == INVALID_SOCKET)
	{
		AfxMessageBox(_T("Socket create Failed"));

		WSACleanup();
		//return;
	}
	client_addr.sin_family = AF_INET;
	client_addr.sin_port = htons((short)4444);
	char p2[50];
	LPTSTR p1 = ip.GetBuffer(0);
	for (int i = 0; i < ip.GetLength(); i++)
	{
		p2[i] = p1[i];
		t1++;
	}
	p2[t1] = '\0';
	client_addr.sin_addr.s_addr = inet_addr(p2);
	Ret = connect(client, (LPSOCKADDR)&client_addr, sizeof(client_addr));
	if (Ret == SOCKET_ERROR)
	{
		AfxMessageBox(_T("Connect Failed"));

		closesocket(client);
		WSACleanup();
		//return;
	}


	bufferx = pointx;
	//将全部信息 坐标x，坐标y，棋子n，判定数01组成字符串
	memset(buf, 0, MAX_PATH);
	bufferx += ',';
	bufferx += pointy;
	bufferx += ',';
	bufferx += pointn;
	bufferx += ',';
	bufferx += point01;
	bufferx += ',';
	bufferx += pointbtn;
	bufferx += ',';
	bufferx += pointbtn1;
	bufferx += ',';
	bufferx += pointbtn2;
	bufferx += ',';
	bufferx += pointbtn3;
	bufferx += ',';
	bufferx += pointbtn4;

	int i;
	LPTSTR p = bufferx.GetBuffer(0);
	for (i = 0; i < bufferx.GetLength(); i++)
	{
		buf[i] = p[i];

	}
	buf[i] = '\0';

	Ret = send(client, buf, strlen(buf), 0);
	
	if (Ret == SOCKET_ERROR)
	{
		AfxMessageBox(_T("send Faile"));
		closesocket(client);
		WSACleanup();
		return;
	}

	 //send(sockfd套接字描述符, msg内容的指针, len数据的长度, 0);

	if (Ret == SOCKET_ERROR)
	{
		AfxMessageBox(_T("send Faile"));
		closesocket(client);
		WSACleanup();
		return;
	}

	closesocket(client);
	WSACleanup();
	return;

}


