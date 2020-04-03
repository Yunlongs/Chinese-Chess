// Menu.cpp : 实现文件
//

#include "stdafx.h"
#include "Chinese Chess.h"
#include "Menu.h"
#include "afxdialogex.h"

extern int MoShi;
// Menu 对话框

IMPLEMENT_DYNAMIC(Menu, CDialogEx)

Menu::Menu(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG2, pParent)
{

}

Menu::~Menu()
{
}

void Menu::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Menu, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &Menu::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &Menu::OnBnClickedButton2)
	ON_BN_CLICKED(IDCANCEL, &Menu::OnBnClickedCancel)
END_MESSAGE_MAP()


// Menu 消息处理程序


void Menu::OnBnClickedButton1()
{
	MoShi = 1;
	AfxMessageBox("进入单机游戏");
	OnCancel();
	// TODO: 在此添加控件通知处理程序代码
}


void Menu::OnBnClickedButton2()
{
	MoShi = 2;
	AfxMessageBox("进入局域网游戏");
	OnCancel();
	// TODO: 在此添加控件通知处理程序代码
}


void Menu::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	PostQuitMessage(0);
	CDialogEx::OnCancel();;
}
