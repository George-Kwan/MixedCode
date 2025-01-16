
// GATestDlg.h: 头文件
//

#pragma once


// CGATestDlg 对话框
class CGATestDlg : public CDialogEx
{
// 构造
public:
	CGATestDlg(CWnd* pParent = nullptr);	// 标准构造函数
	~CGATestDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GATEST_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()


	ULONG_PTR diplusToken = 0;
	CStatic m_ImageBox;
	afx_msg void OnShowBnClickedButton();
	CEdit m_Text;
	CEdit m_Size;
	CSpinButtonCtrl m_Spin;
	CEdit m_Output;
};
