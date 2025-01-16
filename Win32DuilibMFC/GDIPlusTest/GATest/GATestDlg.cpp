
// GATestDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "GATest.h"
#include "GATestDlg.h"
#include "afxdialogex.h"
#include <string>

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// CGATestDlg 对话框



CGATestDlg::CGATestDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GATEST_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CGATestDlg::~CGATestDlg()
{
	Gdiplus::GdiplusShutdown(diplusToken);
}

void CGATestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_IMAGE_BOX, m_ImageBox);
	DDX_Control(pDX, IDC_EDIT1, m_Text);
	DDX_Control(pDX, IDC_EDIT2, m_Size);
	DDX_Control(pDX, IDC_SPIN1, m_Spin);
	DDX_Control(pDX, IDC_EDIT3, m_Output);
}

BEGIN_MESSAGE_MAP(CGATestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CGATestDlg::OnShowBnClickedButton)
END_MESSAGE_MAP()


// CGATestDlg 消息处理程序

BOOL CGATestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	m_Text.SetWindowTextW(L"张三狗");

	m_ImageBox.SetWindowPos(nullptr, 0, 0, 100, 100, SWP_NOMOVE);

	m_Spin.SetRange32(15, 30);
	m_Spin.SetBase(10);
	m_Spin.SetBuddy(&m_Size);
	m_Spin.SetPos(15);
	
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	Gdiplus::GdiplusStartup(&diplusToken, &gdiplusStartupInput, NULL);

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CGATestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CGATestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CGATestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CGATestDlg::OnShowBnClickedButton()
{
	// TODO: 在此添加控件通知处理程序代码
	
	wchar_t nameArray[256]{ 0 };
	m_Text.GetWindowTextW(nameArray, 256);
	wstring name = nameArray;

	if (name.empty()) {
		name = LR"(默认)";
		m_Text.SetWindowTextW(name.c_str());
	}

	if (name.length() > 2) {
		name = name.substr(name.length() - 2);
	}

	memset(nameArray, 256, 0x00);
	m_Size.GetWindowTextW(nameArray, 256);

	wstring sizestr = nameArray;
	if (sizestr.empty()) {
		sizestr = L"25";
		m_Size.SetWindowTextW(sizestr.c_str());
	}

	float size = std::stof(sizestr.c_str());

	if (size < 15 || size > 30) {
		MessageBox(LR"(请输入数值在 15-30之间)", L"", MB_OK);
		return;
	}

	float x = 100.0f, y = 100.0f;
	Gdiplus::Bitmap bitmap(100, 100);
	Gdiplus::Graphics graphics(&bitmap);
	Gdiplus::SolidBrush brush(0xFF347AFC);
	graphics.FillRectangle(&brush, 0.0f, 0.0f, x, y);
	//Gdiplus::Pen pen(0xFF347AFC);
	//graphics.DrawRectangle(&pen, 0.0f, 0.0f, x, y);

	Gdiplus::FontFamily fontFamily(/*L"Microsoft YaHei"*/ /*L"新宋体"*/  L"Arial");

	float emSize = [&]()->float {
		float f = size;
		while (f > 15)
		{
			Gdiplus::Font myFont(&fontFamily, f, Gdiplus::FontStyleBold, Gdiplus::UnitPoint);
			Gdiplus::RectF boundingBox{ 0.00,0.00,0.00,0.00 };
			graphics.MeasureString(name.c_str(), -1, &myFont, { 0.0f, 0.0f }, &boundingBox);
			if (x > boundingBox.Width)
				break;
			f--;
		}
		return f;
	}();

	size = emSize;

	Gdiplus::Font myFont(&fontFamily, size/*20*//*23*/, Gdiplus::FontStyleBold, Gdiplus::UnitPoint);
	Gdiplus::SolidBrush solidBrush(Gdiplus::Color(255, 255, 255, 255));
	Gdiplus::RectF rect(0.0f, 0.0f, x, y);
	//Gdiplus::StringFormat format(Gdiplus::StringFormatFlagsNoWrap);  //取消自动换行 
	//Gdiplus::StringFormat format(Gdiplus::StringFormatFlagsLineLimit);  //在布局矩形中只布置整行
	//Gdiplus::StringFormat format(Gdiplus::StringFormatFlagsNoFitBlackBox);    // // 允许字符尾部悬于矩形之外	
	//Gdiplus::StringFormat format = format.GenericTypographic();
	//Gdiplus::StringFormat format = format.GenericDefault();
	//format.SetAlignment(Gdiplus::StringAlignmentCenter);    //左右居中
	//format.SetLineAlignment(Gdiplus::StringAlignmentCenter);  //上下居中
	// stringFormat.SetTrimming(StringTrimmingEllipsisWord);  ////按单词去尾，并用...代替
	//stringFormat.SetTrimming(StringTrimmingEllipsisCharacter);  ////按字符去尾，并用...代替
	//stringFormat.SetTrimming(StringTrimmingEllipsisPath);  //显示首尾，并用...代替


	Gdiplus::StringFormat format(Gdiplus::StringFormatFlagsNoWrap);
	format.SetAlignment(Gdiplus::StringAlignmentCenter);    //左右居中
	format.SetLineAlignment(Gdiplus::StringAlignmentCenter);  //上下居中
	graphics.DrawString(name.c_str(), name.length(), &myFont, rect, &format, &solidBrush);

	
	Gdiplus::RectF boundingBox{ 0.0f,0.0f,0.0f,0.0f };
	graphics.MeasureString(name.c_str(), (int)name.length(), &myFont, { 0.0f, 0.0f }, &boundingBox);

	wchar_t fontName[256]{ 0 };
	fontFamily.GetFamilyName(fontName);
	wstring info = L"图像W x H 为： 100 x 100 \r\n \r\n 字符区域W H为： \r\n W=" + to_wstring((int)boundingBox.Width) + L"\r\n" + L" H=" + to_wstring((int)boundingBox.Height) + L"\r\n\r\n字体：" + wstring(fontName) + L"\r\n\r\n字体：" + to_wstring((int)size);
	
	m_Output.SetWindowTextW(info.c_str());

	//Gdiplus::StringFormat format = Gdiplus::StringFormat::GenericTypographic();
	//format.SetAlignment(Gdiplus::StringAlignmentCenter);  
	//format.SetLineAlignment(Gdiplus::StringAlignmentCenter); 
	//int i = format.GetFormatFlags();
	//format.SetFormatFlags(Gdiplus::StringFormatFlagsNoWrap | format.GetFormatFlags());
	//i = format.GetFormatFlags();
	/*rect.Width = boundingBox.Width;
	rect.Height = boundingBox.Height;
	rect.X = (x - rect.Width) / 2;
	rect.Y = (y - rect.Height) / 2;

	format.GenericTypographic();*/

	
	//graphics.DrawString(name.c_str(), name.length(), &myFont, rect, &format, &solidBrush);


	HBITMAP hBitmap = nullptr;
	bitmap.GetHBITMAP(Gdiplus::Color(0, 0, 0, 0), &hBitmap);

	m_ImageBox.SetBitmap(hBitmap);
}
