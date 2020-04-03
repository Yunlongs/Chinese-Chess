
// Chinese Chess.cpp : ����Ӧ�ó��������Ϊ��
//

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "Chinese Chess.h"
#include "MainFrm.h"

#include "Chinese ChessDoc.h"
#include "Chinese ChessView.h"
#include "Menu.h"
#include "Connection.h"
#include "SkinMagicLib.h"
#pragma comment(lib,"SkinMagicTrial.lib") 
#include <mmsystem.h>
#pragma comment(lib, "WINMM.LIB")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


extern QZ qz[50];
extern CString SoundfileName[9];
extern void G_Show();
extern int killking();

extern int MoShi ;
extern CString ip;
extern int ifbtn1, ifbtn2, ifbtn3, ifbtn4, ifbtn;

extern int StepCount;
extern CList <STEP> step;
extern STEP step1/*��ǰ*/;
STEP step3/*ǰ����*/;
extern int right;

CString GetIP();
// CChineseChessApp

BEGIN_MESSAGE_MAP(CChineseChessApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CChineseChessApp::OnAppAbout)
	// �����ļ��ı�׼�ĵ�����
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
END_MESSAGE_MAP()


// ��̨��������
UINT DuoXianCheng(LPVOID param)
{
	WSADATA ws;
	SOCKET server;
	SOCKET client;
	SOCKADDR_IN ser_addr;
	int Ret = 0;

	int pointxx = 0;//�������x����
	int pointyy = 0;//�������y����
	int pointnn = 0;//�����������n
	int point0011 = 0;//��������ж���
	int pointbbttnn = 0;//���������ʼ��ť��Ϣ
	int pointbbttnn1 = 0;//����������尴ť��Ϣ
	int pointbbttnn2 = 0;//����������䰴ť��Ϣ
	int pointbbttnn3 = 0;//��������˳���ť��Ϣ
	int pointbbttnn4 = 0; //��������;ְ�ť��Ϣ
	char bufferxrev[MAX_PATH];//����x����
	char bufferyrev[MAX_PATH];//����y����
	char buffernrev[MAX_PATH];//��������n��Ϣ
	char buffer01rev[MAX_PATH];//�����ж���01

	char bufferbtnrev[MAX_PATH];//���濪ʼ��ť��Ϣ
	char bufferbtn1rev[MAX_PATH];//������尴ť��Ϣ
	char bufferbtn2rev[MAX_PATH];//�������䰴ť��Ϣ
	char bufferbtn3rev[MAX_PATH];//�����˳���ť��Ϣ
	char bufferbtn4rev[MAX_PATH];//����;ְ�ť��Ϣ

	char buffer[MAX_PATH];//�ܻ���

	if (WSAStartup(MAKEWORD(2, 2), &ws) != 0)
	{
		AfxMessageBox(_T("WSAStartup Failed"));
		return 0;
	}
	server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (server == INVALID_SOCKET)
	{
		AfxMessageBox(_T("�׽��ִ���ʧ��"));
		WSACleanup();
		return 0;
	}
	unsigned long u1 = 1;

	ser_addr.sin_family = AF_INET;
	ser_addr.sin_port = htons(4444);
	ser_addr.sin_addr.s_addr = INADDR_ANY;
	memset(ser_addr.sin_zero, 0, sizeof(ser_addr.sin_zero));
	Ret = bind(server, (struct sockaddr*)&ser_addr, sizeof(struct sockaddr));

	if (Ret == SOCKET_ERROR)
	{
		AfxMessageBox(_T("��ʧ��"));
		closesocket(server);
		WSACleanup();
		return 0;
	}

	Ret = listen(server, 100);

	if (Ret == SOCKET_ERROR)
	{
		AfxMessageBox(_T("����ʧ��"));
		closesocket(server);
		WSACleanup();
		return 0;
	}
	sockaddr_in client_addr;

	while (true) 
	{
		memset(buffer, 0, MAX_PATH);
		int addrlen = sizeof(client_addr);
		client = accept(server, (struct sockaddr*)&client_addr, &addrlen);
		if (client == INVALID_SOCKET)
		{
			AfxMessageBox(_T("accept Failed"));

			continue;
		}
		Ret = recv(client, buffer, MAX_PATH, 0);//����
		if (Ret == SOCKET_ERROR)
		{
			AfxMessageBox(_T("recv Failed"));

			continue;
		}
		else 
		{
			//�����ݽ��в��
			int i = 0, k1 = 0;	//������ݼ�����
			//���x
			for (i = 0; i < strlen(buffer); i++)
			{
				if (buffer[i] == ',')
				{
					for (int t = 0; t < i; t++)
					{
						bufferxrev[t] = buffer[t];
					}
					bufferxrev[i] = '\0';
					k1 =++i;
					
					break;
				}
			}
			//���y
			for (; i < strlen(buffer); i++)
			{
				if (buffer[i] == ',')
				{
					for (int t = k1; t < i; t++)
					{
						bufferyrev[t-(strlen(bufferxrev)+1)] = buffer[t];
					}
					bufferyrev[i-k1] = '\0';
					k1 = ++i;
					break;
				}
			}
			//���n
			for (; i < strlen(buffer); i++)
			{
				if (buffer[i] == ',')
				{
					for (int t = k1; t < i; t++)
					{
						buffernrev[t - (strlen(bufferxrev)+strlen(bufferyrev) + 2)] = buffer[t];
					}
					buffernrev[i-k1] = '\0';
					break;
				}
			}
			
			//����ж���
			buffer01rev[0] = buffer[++i];
			++i;
			//��ֿ�ʼ��ť
			bufferbtnrev[0] = buffer[++i];
			++i;

			//��ֻ��尴ť
			bufferbtn1rev[0] = buffer[++i];
			++i;

			//������䰴ť
			bufferbtn2rev[0] = buffer[++i];
			++i;

			//����˳���ť
			bufferbtn3rev[0] = buffer[++i];
			++i;

			//��ֺ;ְ�ť
			bufferbtn4rev[0] = buffer[++i];
			++i;

			pointxx = 0;
			pointyy = 0;
			pointnn = 0;
			pointbbttnn1 = 0;

			//ת��Ϊint������
			for (i = 0; bufferxrev[i] != '\0'; i++)
			{
				pointxx = pointxx * 10 + (bufferxrev[i] - '0');
			}
			for (i = 0; bufferyrev[i] != '\0'; i++)
			{
				pointyy = pointyy * 10 + (bufferyrev[i] - '0');
			}
			for (i = 0; buffernrev[i] != '\0'; i++)
			{
				pointnn = pointnn * 10 + (buffernrev[i] - '0');
			}
			point0011 = buffer01rev[0] - '0';
			pointbbttnn = bufferbtnrev[0] - '0';
			pointbbttnn1 = bufferbtn1rev[0] - '0';
			pointbbttnn2 = bufferbtn2rev[0] - '0';
			pointbbttnn3 = bufferbtn3rev[0] - '0';
			pointbbttnn4 = bufferbtn4rev[0] - '0';

			int btnright = 0/*����֮ǰ���ж���*/, ready = 0;/*�Ƿ��Ѿ�׼��*/

			btnright = right;

			if (ifbtn == 1)
			{
				ready = 1;
			}
			else
			{
				ready = 0;
			}

			step1.n = pointnn;
			step1.x = pointxx;
			step1.y = pointyy;
			right = point0011;
			ifbtn = pointbbttnn;
			ifbtn1 = pointbbttnn1;
			ifbtn2 = pointbbttnn2;
			ifbtn3 = pointbbttnn3;
			ifbtn4 = pointbbttnn4;

			if (step.GetCount() >= 3)
			{
				step3 = step.GetAt(step.FindIndex(step.GetCount() - 3));
			}

			//�Է�����
			if (right != 0)
			{
				if (right == 1)				//�Է�ѡ��
				{
					step.AddTail(step1);
					StepCount++;
				}
				else if (right == 4)				//�Է�����ѡ��
				{
					step.GetTail().n = step1.n;
					step.GetTail().x = step1.x;
					step.GetTail().y = step1.y;
				}
				else if (right == 2)			//�Է�����
				{
					qz[48].x = step.GetTail().x;	//���ϲ�ѡ�����Ӵ���
					qz[48].y = step.GetTail().y;

					if (step1.n != 0)
					{
						sndPlaySound(SoundfileName[5], SND_ASYNC | SND_NODEFAULT);
						qz[step1.n].x = -100;
						qz[step1.n].y = -100;
					}
					else
					{
						sndPlaySound(SoundfileName[6], SND_ASYNC | SND_NODEFAULT);
					}
					
					qz[qz[step.GetTail().n].s].x = step1.x;
					qz[qz[step.GetTail().n].s].y = step1.y;

					if (step.GetCount() >= 3)	//���Է����ӵĿ����
					{
						qz[qz[step3.n].s].x = -100;
						qz[qz[step3.n].s].y = -100;
					}
					qz[step.GetTail().n].x = step1.x;
					qz[step.GetTail().n].y = step1.y;

					step.AddTail(step1);
					StepCount++;
					killking();
					G_Show();
				}
				else if(right == 3)
				{
					if (ifbtn == 1 && ready == 0)
					{
						AfxMessageBox("�Է���׼��!");
					}
					right = btnright;
				}
			}
		}
	}
	return 0;
}

// CChineseChessApp ����
CChineseChessApp::CChineseChessApp()
{
	m_bHiColorIcons = TRUE;

	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// ���Ӧ�ó��������ù�����������ʱ֧��(/clr)�����ģ���: 
	//     1) �����д˸������ã�������������������֧�ֲ�������������
	//     2) ��������Ŀ�У������밴������˳���� System.Windows.Forms ������á�
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: ������Ӧ�ó��� ID �ַ����滻ΪΨһ�� ID �ַ�����������ַ�����ʽ
	//Ϊ CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("Chinese Chess.AppID.NoVersion"));

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}

// Ψһ��һ�� CChineseChessApp ����

CChineseChessApp theApp;


// CChineseChessApp ��ʼ��


int CChineseChessApp::ExitInstance()
{
	//TODO: �����������ӵĸ�����Դ
	ExitSkinMagicLib();
	AfxOleTerm(FALSE);
	return CWinAppEx::ExitInstance();
}

// CChineseChessApp ��Ϣ�������


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// �������жԻ����Ӧ�ó�������
void CChineseChessApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CChineseChessApp �Զ������/���淽��

void CChineseChessApp::PreLoadState()
{
	BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
}

void CChineseChessApp::LoadCustomState()
{
}

void CChineseChessApp::SaveCustomState()
{
}

// CChineseChessApp ��Ϣ�������


//��ʾѡ��ģʽ
BOOL CChineseChessApp::InitInstance()
{
	VERIFY(InitSkinMagicLib(AfxGetInstanceHandle(), "Skin", NULL, NULL));
	if (LoadSkinFromResource(AfxGetInstanceHandle(), (LPCTSTR)IDR_SKINMAGIC1, "SKINMAGIC"))
	{    
		  //���öԻ���Ĭ��Ƥ��
		SetDialogSkin("Dialog");
	}
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()��  ���򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();


	// ��ʼ�� OLE ��
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction(FALSE);

	// ʹ�� RichEdit �ؼ���Ҫ AfxInitRichEdit2()	
	// AfxInitRichEdit2();

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));
	LoadStdProfileSettings(4);  // ���ر�׼ INI �ļ�ѡ��(���� MRU)


	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);



		// ע��Ӧ�ó�����ĵ�ģ�塣  �ĵ�ģ��
		// �������ĵ�����ܴ��ں���ͼ֮�������
		CSingleDocTemplate* pDocTemplate;
		pDocTemplate = new CSingleDocTemplate(
			IDR_MAINFRAME,
			RUNTIME_CLASS(CChineseChessDoc),
			RUNTIME_CLASS(CMainFrame),       // �� SDI ��ܴ���
			RUNTIME_CLASS(CChineseChessView));
		if (!pDocTemplate)
			return FALSE;
		AddDocTemplate(pDocTemplate);


		// ������׼ shell ���DDE�����ļ�������������
		CCommandLineInfo cmdInfo;
		ParseCommandLine(cmdInfo);



		// ��������������ָ�������  ���
		// �� /RegServer��/Register��/Unregserver �� /Unregister ����Ӧ�ó����򷵻� FALSE��
		if (!ProcessShellCommand(cmdInfo))
			return FALSE;

		// Ψһ��һ�������ѳ�ʼ���������ʾ����������и���


		SetWindowPos(AfxGetMainWnd()->m_hWnd, 0, 0, 0, 750, 720, SWP_NOMOVE);//�ı䴰�ڴ�С

		m_pMainWnd->ShowWindow(SW_SHOW);
		m_pMainWnd->UpdateWindow();
		Menu menu;
		menu.DoModal();
		if (MoShi == 1)
		{

		}
		else if (MoShi == 2)
		{
			InputIP();
		}

	return TRUE;
}

//����IP
void CChineseChessApp::InputIP()
{
	Connection  C_Ip;
	C_Ip.TEXT = GetIP();
	C_Ip.DoModal();
	ip = C_Ip.TEXT;
	AfxBeginThread(DuoXianCheng,NULL);
}

//�õ��Լ�IP��ַ
CString GetIP()
{
	WORD	wVersionRequested;
	WSADATA	wsaData;
	int		retVal;
	wVersionRequested = MAKEWORD(2, 2);
	retVal = WSAStartup(wVersionRequested, (LPWSADATA)&wsaData);
	if (0 != retVal)
	{
		//	MessageBox(NULL, "Can not find a usable Windows Sockets dll!", "ERROR", MB_OK);
		//cout << "error" << endl;
		//return 1;
	}
	char hostname[MAX_PATH];
	gethostname(hostname, MAX_PATH);			//��ȡ��������
	struct hostent FAR*	lpHost = gethostbyname(hostname);

	LPSTR IPadress = lpHost->h_addr_list[0];
	struct in_addr inAddr;
	memmove(&inAddr, IPadress, 4);
//	cout << "IpAdress:" << adress << endl;
	CString a;
	a = CString(inet_ntoa(inAddr));
	return a;
}