
// Chinese Chess.cpp : 定义应用程序的类行为。
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
extern STEP step1/*当前*/;
STEP step3/*前三步*/;
extern int right;

CString GetIP();
// CChineseChessApp

BEGIN_MESSAGE_MAP(CChineseChessApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CChineseChessApp::OnAppAbout)
	// 基于文件的标准文档命令
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
END_MESSAGE_MAP()


// 后台监听函数
UINT DuoXianCheng(LPVOID param)
{
	WSADATA ws;
	SOCKET server;
	SOCKET client;
	SOCKADDR_IN ser_addr;
	int Ret = 0;

	int pointxx = 0;//最终输出x坐标
	int pointyy = 0;//最终输出y坐标
	int pointnn = 0;//最终输出棋子n
	int point0011 = 0;//最终输出判定数
	int pointbbttnn = 0;//最终输出开始按钮信息
	int pointbbttnn1 = 0;//最终输出悔棋按钮信息
	int pointbbttnn2 = 0;//最终输出认输按钮信息
	int pointbbttnn3 = 0;//最终输出退出按钮信息
	int pointbbttnn4 = 0; //最终输出和局按钮信息
	char bufferxrev[MAX_PATH];//缓存x坐标
	char bufferyrev[MAX_PATH];//缓存y坐标
	char buffernrev[MAX_PATH];//缓存棋子n信息
	char buffer01rev[MAX_PATH];//缓存判定数01

	char bufferbtnrev[MAX_PATH];//缓存开始按钮信息
	char bufferbtn1rev[MAX_PATH];//缓存悔棋按钮信息
	char bufferbtn2rev[MAX_PATH];//缓存认输按钮信息
	char bufferbtn3rev[MAX_PATH];//缓存退出按钮信息
	char bufferbtn4rev[MAX_PATH];//缓存和局按钮信息

	char buffer[MAX_PATH];//总缓存

	if (WSAStartup(MAKEWORD(2, 2), &ws) != 0)
	{
		AfxMessageBox(_T("WSAStartup Failed"));
		return 0;
	}
	server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (server == INVALID_SOCKET)
	{
		AfxMessageBox(_T("套接字创建失败"));
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
		AfxMessageBox(_T("绑定失败"));
		closesocket(server);
		WSACleanup();
		return 0;
	}

	Ret = listen(server, 100);

	if (Ret == SOCKET_ERROR)
	{
		AfxMessageBox(_T("监听失败"));
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
		Ret = recv(client, buffer, MAX_PATH, 0);//接收
		if (Ret == SOCKET_ERROR)
		{
			AfxMessageBox(_T("recv Failed"));

			continue;
		}
		else 
		{
			//对数据进行拆分
			int i = 0, k1 = 0;	//拆分数据计数器
			//拆分x
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
			//拆分y
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
			//拆分n
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
			
			//拆分判定数
			buffer01rev[0] = buffer[++i];
			++i;
			//拆分开始按钮
			bufferbtnrev[0] = buffer[++i];
			++i;

			//拆分悔棋按钮
			bufferbtn1rev[0] = buffer[++i];
			++i;

			//拆分认输按钮
			bufferbtn2rev[0] = buffer[++i];
			++i;

			//拆分退出按钮
			bufferbtn3rev[0] = buffer[++i];
			++i;

			//拆分和局按钮
			bufferbtn4rev[0] = buffer[++i];
			++i;

			pointxx = 0;
			pointyy = 0;
			pointnn = 0;
			pointbbttnn1 = 0;

			//转换为int型数据
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

			int btnright = 0/*保存之前的判定数*/, ready = 0;/*是否已经准备*/

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

			//对方下子
			if (right != 0)
			{
				if (right == 1)				//对方选棋
				{
					step.AddTail(step1);
					StepCount++;
				}
				else if (right == 4)				//对方重新选棋
				{
					step.GetTail().n = step1.n;
					step.GetTail().x = step1.x;
					step.GetTail().y = step1.y;
				}
				else if (right == 2)			//对方下棋
				{
					qz[48].x = step.GetTail().x;	//将上步选中棋子带框
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

					if (step.GetCount() >= 3)	//将对方棋子的框清除
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
						AfxMessageBox("对方已准备!");
					}
					right = btnright;
				}
			}
		}
	}
	return 0;
}

// CChineseChessApp 构造
CChineseChessApp::CChineseChessApp()
{
	m_bHiColorIcons = TRUE;

	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// 如果应用程序是利用公共语言运行时支持(/clr)构建的，则: 
	//     1) 必须有此附加设置，“重新启动管理器”支持才能正常工作。
	//     2) 在您的项目中，您必须按照生成顺序向 System.Windows.Forms 添加引用。
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: 将以下应用程序 ID 字符串替换为唯一的 ID 字符串；建议的字符串格式
	//为 CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("Chinese Chess.AppID.NoVersion"));

	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}

// 唯一的一个 CChineseChessApp 对象

CChineseChessApp theApp;


// CChineseChessApp 初始化


int CChineseChessApp::ExitInstance()
{
	//TODO: 处理可能已添加的附加资源
	ExitSkinMagicLib();
	AfxOleTerm(FALSE);
	return CWinAppEx::ExitInstance();
}

// CChineseChessApp 消息处理程序


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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

// 用于运行对话框的应用程序命令
void CChineseChessApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CChineseChessApp 自定义加载/保存方法

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

// CChineseChessApp 消息处理程序


//显示选择模式
BOOL CChineseChessApp::InitInstance()
{
	VERIFY(InitSkinMagicLib(AfxGetInstanceHandle(), "Skin", NULL, NULL));
	if (LoadSkinFromResource(AfxGetInstanceHandle(), (LPCTSTR)IDR_SKINMAGIC1, "SKINMAGIC"))
	{    
		  //设置对话框默认皮肤
		SetDialogSkin("Dialog");
	}
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。  否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();


	// 初始化 OLE 库
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction(FALSE);

	// 使用 RichEdit 控件需要 AfxInitRichEdit2()	
	// AfxInitRichEdit2();

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));
	LoadStdProfileSettings(4);  // 加载标准 INI 文件选项(包括 MRU)


	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);



		// 注册应用程序的文档模板。  文档模板
		// 将用作文档、框架窗口和视图之间的连接
		CSingleDocTemplate* pDocTemplate;
		pDocTemplate = new CSingleDocTemplate(
			IDR_MAINFRAME,
			RUNTIME_CLASS(CChineseChessDoc),
			RUNTIME_CLASS(CMainFrame),       // 主 SDI 框架窗口
			RUNTIME_CLASS(CChineseChessView));
		if (!pDocTemplate)
			return FALSE;
		AddDocTemplate(pDocTemplate);


		// 分析标准 shell 命令、DDE、打开文件操作的命令行
		CCommandLineInfo cmdInfo;
		ParseCommandLine(cmdInfo);



		// 调度在命令行中指定的命令。  如果
		// 用 /RegServer、/Register、/Unregserver 或 /Unregister 启动应用程序，则返回 FALSE。
		if (!ProcessShellCommand(cmdInfo))
			return FALSE;

		// 唯一的一个窗口已初始化，因此显示它并对其进行更新


		SetWindowPos(AfxGetMainWnd()->m_hWnd, 0, 0, 0, 750, 720, SWP_NOMOVE);//改变窗口大小

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

//输入IP
void CChineseChessApp::InputIP()
{
	Connection  C_Ip;
	C_Ip.TEXT = GetIP();
	C_Ip.DoModal();
	ip = C_Ip.TEXT;
	AfxBeginThread(DuoXianCheng,NULL);
}

//得到自己IP地址
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
	gethostname(hostname, MAX_PATH);			//获取主机名称
	struct hostent FAR*	lpHost = gethostbyname(hostname);

	LPSTR IPadress = lpHost->h_addr_list[0];
	struct in_addr inAddr;
	memmove(&inAddr, IPadress, 4);
//	cout << "IpAdress:" << adress << endl;
	CString a;
	a = CString(inet_ntoa(inAddr));
	return a;
}