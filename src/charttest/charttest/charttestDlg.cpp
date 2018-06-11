
// charttestDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "charttest.h"
#include "charttestDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CcharttestDlg 对话框




CcharttestDlg::CcharttestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CcharttestDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CcharttestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CcharttestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_MOVE()
	ON_BN_CLICKED(IDC_CHECK1, &CcharttestDlg::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_CHECK2, &CcharttestDlg::OnBnClickedCheck2)
	ON_BN_CLICKED(IDC_CHECK3, &CcharttestDlg::OnBnClickedCheck3)
	ON_BN_CLICKED(IDC_BUTTON1, &CcharttestDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CcharttestDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CcharttestDlg::OnBnClickedButton3)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_CHECK4, &CcharttestDlg::OnBnClickedCheck4)
END_MESSAGE_MAP()


// CcharttestDlg 消息处理程序

BOOL CcharttestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	m_wavedlg =new wavectrl(this);
	m_wavedlg->Create(IDD_DIALOG1,this);
	m_wavedlg->ShowWindow(TRUE);
	
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CcharttestDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CcharttestDlg::OnPaint()
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
HCURSOR CcharttestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CcharttestDlg::OnMove(int x, int y)
{
	CDialogEx::OnMove(x, y);

	// TODO: 在此处添加消息处理程序代码
	CRect rt;
	GetClientRect(&rt);
		rt.right -= 100;
		rt.bottom -= 50;
	m_wavedlg->MoveWindow(&rt);
}

//pan控制
void CcharttestDlg::OnBnClickedCheck1()
{
	// TODO: 在此添加控件通知处理程序代码
	if (((CButton*)GetDlgItem(IDC_CHECK1))->GetCheck() == 1)
	    m_wavedlg->SetPanCtrl(true);
	else
		m_wavedlg->SetPanCtrl(false);
}

//zoom 控制
void CcharttestDlg::OnBnClickedCheck2()
{
	if (((CButton*)GetDlgItem(IDC_CHECK2))->GetCheck() == 1)
		m_wavedlg->SetZoomCtrl(true);
	else
		m_wavedlg->SetZoomCtrl(false);
}

//lengde 控制
void CcharttestDlg::OnBnClickedCheck3()
{
	if (((CButton*)GetDlgItem(IDC_CHECK3))->GetCheck() == 1)
		m_wavedlg->SetLegendCtrl(true);
	else
		m_wavedlg->SetLegendCtrl(false);
}

//清空所有
void CcharttestDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	m_wavedlg->ClearAllSeries();
}

//静态划线
void CcharttestDlg::OnBnClickedButton2()
{
	double x[1000],y[1000];
	COleDateTime t1(COleDateTime::GetCurrentTime());  
	COleDateTimeSpan tsp(0,0,1,0);  
	for (int i=0; i<1000; i++)  
	{  
		x[i] = t1.m_dt;  
		y[i] = sin(float(i));  
		t1 += tsp;  
	}  
	m_wavedlg->SetXYtittle("CO2浓度","当前时间","室内co采集");
	m_wavedlg->SetleftMaxAndMin( 0,30);
	m_wavedlg->DrawLineStaticChart(x,y , 100);
}

//动态划线
void CcharttestDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	static bool running =false;
	running = !running;
	if (running)
	{
	
		m_wavedlg->SetXYtittle("CO2浓度","当前时间","室内co采集");
		m_wavedlg->SetleftMaxAndMin( 0,30);
		SetTimer(11,1000,NULL);
	}
	else
	{
		KillTimer(11);
	}

}


void CcharttestDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (nIDEvent  == 11)
	{
		drawuserdynctest() ;
	}

	CDialogEx::OnTimer(nIDEvent);
}
void CcharttestDlg::drawuserdynctest()
{
	COleDateTime t1(COleDateTime::GetCurrentTime());  
	static int num =0;

	m_wavedlg->DrawLineDyncChart(t1.m_dt ,num++) ;
}


void CcharttestDlg::OnBnClickedCheck4()
{
	// TODO: 在此添加控件通知处理程序代码
	if (((CButton*)GetDlgItem(IDC_CHECK4))->GetCheck() == 1)
		m_wavedlg->SetCrosskCtrl(true);
	else
		m_wavedlg->SetCrosskCtrl(false);
}
