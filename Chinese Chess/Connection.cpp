// Connection.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Chinese Chess.h"
#include "Connection.h"
#include "afxdialogex.h"

extern int MoShi;
// Connection �Ի���

IMPLEMENT_DYNAMIC(Connection, CDialogEx)

Connection::Connection(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

Connection::~Connection()
{
}

void Connection::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, TEXT);
}


BEGIN_MESSAGE_MAP(Connection, CDialogEx)
	ON_BN_CLICKED(IDCANCEL, &Connection::OnBnClickedCancel)
END_MESSAGE_MAP()


// Connection ��Ϣ�������


void Connection::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	PostQuitMessage(0);
	MoShi=0;
	CDialogEx::OnCancel();
}
