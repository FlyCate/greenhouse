
// charttestDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "charttest.h"
#include "charttestDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CcharttestDlg �Ի���




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


// CcharttestDlg ��Ϣ�������

BOOL CcharttestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	m_wavedlg =new wavectrl(this);
	m_wavedlg->Create(IDD_DIALOG1,this);
	m_wavedlg->ShowWindow(TRUE);
	
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CcharttestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CcharttestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CcharttestDlg::OnMove(int x, int y)
{
	CDialogEx::OnMove(x, y);

	// TODO: �ڴ˴������Ϣ����������
	CRect rt;
	GetClientRect(&rt);
		rt.right -= 100;
		rt.bottom -= 50;
	m_wavedlg->MoveWindow(&rt);
}

//pan����
void CcharttestDlg::OnBnClickedCheck1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (((CButton*)GetDlgItem(IDC_CHECK1))->GetCheck() == 1)
	    m_wavedlg->SetPanCtrl(true);
	else
		m_wavedlg->SetPanCtrl(false);
}

//zoom ����
void CcharttestDlg::OnBnClickedCheck2()
{
	if (((CButton*)GetDlgItem(IDC_CHECK2))->GetCheck() == 1)
		m_wavedlg->SetZoomCtrl(true);
	else
		m_wavedlg->SetZoomCtrl(false);
}

//lengde ����
void CcharttestDlg::OnBnClickedCheck3()
{
	if (((CButton*)GetDlgItem(IDC_CHECK3))->GetCheck() == 1)
		m_wavedlg->SetLegendCtrl(true);
	else
		m_wavedlg->SetLegendCtrl(false);
}

//�������
void CcharttestDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_wavedlg->ClearAllSeries();
}

//��̬����
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
	m_wavedlg->SetXYtittle("CO2Ũ��","��ǰʱ��","����co�ɼ�");
	m_wavedlg->SetleftMaxAndMin( 0,30);
	m_wavedlg->DrawLineStaticChart(x,y , 100);
}

//��̬����
void CcharttestDlg::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	static bool running =false;
	running = !running;
	if (running)
	{
	
		m_wavedlg->SetXYtittle("CO2Ũ��","��ǰʱ��","����co�ɼ�");
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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (((CButton*)GetDlgItem(IDC_CHECK4))->GetCheck() == 1)
		m_wavedlg->SetCrosskCtrl(true);
	else
		m_wavedlg->SetCrosskCtrl(false);
}
