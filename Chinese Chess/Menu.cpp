// Menu.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Chinese Chess.h"
#include "Menu.h"
#include "afxdialogex.h"

extern int MoShi;
// Menu �Ի���

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


// Menu ��Ϣ�������


void Menu::OnBnClickedButton1()
{
	MoShi = 1;
	AfxMessageBox("���뵥����Ϸ");
	OnCancel();
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void Menu::OnBnClickedButton2()
{
	MoShi = 2;
	AfxMessageBox("�����������Ϸ");
	OnCancel();
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void Menu::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	PostQuitMessage(0);
	CDialogEx::OnCancel();;
}
