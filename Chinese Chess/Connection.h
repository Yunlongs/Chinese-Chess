#pragma once


// Connection 对话框

class Connection : public CDialogEx
{
	DECLARE_DYNAMIC(Connection)

public:
	Connection(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Connection();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString TEXT;
	CString GetMineIP;
	afx_msg void OnBnClickedCancel();
};
