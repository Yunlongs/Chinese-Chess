#pragma once


// Connection �Ի���

class Connection : public CDialogEx
{
	DECLARE_DYNAMIC(Connection)

public:
	Connection(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Connection();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString TEXT;
	CString GetMineIP;
	afx_msg void OnBnClickedCancel();
};
