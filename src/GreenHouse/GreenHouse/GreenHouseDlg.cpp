
// GreenHouseDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "GreenHouse.h"
#include "GreenHouseDlg.h"
#include "afxdialogex.h"
#include <process.h>
#include "AutoParamSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define TIMER_ID_GET_DATA 1
#define TIMER_ID_START_DATA 2

// CGreenHouseDlg 对话框




CGreenHouseDlg::CGreenHouseDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CGreenHouseDlg::IDD, pParent)
	, m_radioVal(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGreenHouseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO_REALTIME, m_radioVal);
	DDX_Control(pDX, IDC_COMBO_TYPE, m_type);
	DDX_Control(pDX, IDC_DATETIM_START_DATE, m_startDate);
	DDX_Control(pDX, IDC_DATETIM_END_DATE, m_endDate);
}

BEGIN_MESSAGE_MAP(CGreenHouseDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_SERIAL, &CGreenHouseDlg::OnBnClickedButtonSerial)
	ON_BN_CLICKED(IDC_BUTTON_FAN1, &CGreenHouseDlg::OnBnClickedButtonFan1)
	ON_BN_CLICKED(IDC_BUTTON_FAN2, &CGreenHouseDlg::OnBnClickedButtonFan2)
	ON_BN_CLICKED(IDC_BUTTON_ELECTRIC_MACHINERY1, &CGreenHouseDlg::OnBnClickedButtonElectricMachinery1)
	ON_BN_CLICKED(IDC_BUTTON_ELECTRIC_MACHINERY2, &CGreenHouseDlg::OnBnClickedButtonElectricMachinery2)
	ON_BN_CLICKED(IDC_BUTTON_WATER_PUMP1, &CGreenHouseDlg::OnBnClickedButtonWaterPump1)
	ON_BN_CLICKED(IDC_BUTTON_WATER_PUMP2, &CGreenHouseDlg::OnBnClickedButtonWaterPump2)
	ON_BN_CLICKED(IDC_BUTTON_WATER_PUMP3, &CGreenHouseDlg::OnBnClickedButtonWaterPump3)
	ON_BN_CLICKED(IDC_RADIO_HISDATA_PIC, &CGreenHouseDlg::OnBnClickedRadioRealtime)
	ON_BN_CLICKED(IDC_RADIO_HISDATA_FORM, &CGreenHouseDlg::OnBnClickedRadioRealtime)
	ON_BN_CLICKED(IDC_RADIO_REALTIME, &CGreenHouseDlg::OnBnClickedRadioRealtime)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, &CGreenHouseDlg::OnBnClickedButtonSearch)
	ON_WM_SIZE()
	ON_WM_MOVE()
	ON_WM_SYSCOMMAND()
	ON_BN_CLICKED(IDC_CHECK_TIME, &CGreenHouseDlg::OnBnClickedCheckTime)
	ON_BN_CLICKED(IDC_BUTTON_START_CAP, &CGreenHouseDlg::OnBnClickedButtonStartCap)
	ON_BN_CLICKED(IDC_BUTTON_ELECTRIC_MACHINERY3, &CGreenHouseDlg::OnBnClickedButtonElectricMachinery3)
	ON_CBN_SELCHANGE(IDC_COMBO_TYPE, &CGreenHouseDlg::OnCbnSelchangeComboType)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_LIGHT, &CGreenHouseDlg::OnBnClickedButtonLight)
	ON_BN_CLICKED(IDC_BUTTON_FAN3, &CGreenHouseDlg::OnBnClickedButtonFan3)
	ON_BN_CLICKED(IDC_BUTTON_FAN4, &CGreenHouseDlg::OnBnClickedButtonFan4)
	ON_MESSAGE(WM_USER_POSTMSG, OnUserPostMsg)
	ON_BN_CLICKED(IDC_BUTTON_AUTO_CTL, &CGreenHouseDlg::OnBnClickedButtonAutoCtl)
END_MESSAGE_MAP()


// CGreenHouseDlg 消息处理程序

BOOL CGreenHouseDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	/*创建串口设置对话框*/
	m_Light = FALSE;//照明控制
	m_Fan1 = FALSE;	//排风轴流风机1
	m_Fan2 = FALSE;	//排风轴流风机2
	m_ElectricMachinery1 = FALSE;	//天窗
	m_ElectricMachinery2 = FALSE;	//遮阳罩
	m_ElectricMachinery3 = FALSE;	//保温帘
	m_WaterPump1 = FALSE;	//灌溉
	m_WaterPump2 = FALSE;	//水帘
	m_WaterPump3 = FALSE;	//加热
	m_CapStatus = FALSE;	//采集

	//设置保温帘为打开状态
	m_ElectricMachinery3 = TRUE;
	GetDlgItem(IDC_BUTTON_ELECTRIC_MACHINERY3)->SetWindowText("关");

	m_serial = new MySerial(this);
	m_serial->Create(IDD_DIALOG1, this);
	m_serial->ShowWindow(false);
	// TODO: 在此添加额外的初始化代码

	m_hisForm = new CHisForm(this);
	m_hisForm->Create(IDD_DIALOG_HIS_FORM, this);
	m_hisForm->ShowWindow(FALSE);

	m_wavedlg = new WaveForm(this);
	m_wavedlg->Create(IDD_DLG_WAVE, this);
	m_wavedlg->ShowWindow(TRUE);
	
	m_winddlg = new Winddlg(this);
	m_winddlg->Create(IDD_DLG_WIND, this);
	m_winddlg->ShowWindow(FALSE);

	m_mySQL = new CSQLCtl();
	int ret = m_mySQL->ConnectSQL();
	if (ret != 0)
		MessageBox("数据库未连接!");

	ComboBoxInit(0);

	m_startDate.SetFormat("yyyy-M-d HH:mm:ss");
	m_endDate.SetFormat("yyyy-M-d HH:mm:ss");
	OnBnClickedRadioRealtime();

	m_AutoCtrlStatus = FALSE;

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CGreenHouseDlg::ComboBoxInit(int type)
{
	m_type.ResetContent();
	m_type.InsertString(0, "光照度传感器");
	m_type.InsertString(1, "环境温度传感器");
	m_type.InsertString(2, "环境湿度传感器");
	m_type.InsertString(3, "二氧化碳传感器");
	m_type.InsertString(4, "土壤温度传感器");
	m_type.InsertString(5, "土壤湿度传感器");
	m_type.InsertString(6, "风速传感器");
	//if (type == 0) m_type.InsertString(7, "风向传感器");
	m_type.SetCurSel(0);
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CGreenHouseDlg::OnPaint()
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
		//RECT rect;
		//GetDlgItem(IDC_STATIC_SHOW)->GetWindowRect(&rect);
		//rect.top += 100;
		//rect.left += 1;
		//rect.right -= 1;
		//rect.bottom -= 1;
		//m_hisForm->MoveWindow(rect.left, rect.top, (rect.right - rect.left), (rect.bottom - rect.top));

		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CGreenHouseDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//串口设置
void CGreenHouseDlg::OnBnClickedButtonSerial()
{
	// TODO: 在此添加控件通知处理程序代码
	CRect parrt,mainrt,newrct;
	GetWindowRect(parrt);
	m_serial->GetWindowRect(mainrt);
	newrct.left = parrt.Width()/2 - mainrt.Width()/2;
	newrct.right += newrct.left + mainrt.Width();
	newrct.top =  parrt.Height()/2 - mainrt.Height()/2;
	newrct.bottom =  newrct.top +  mainrt.Height();
	ClientToScreen(newrct);
	m_serial->MoveWindow(newrct);
	m_serial->ShowWindow(true);

}

//照明控制
void CGreenHouseDlg::OnBnClickedButtonLight()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_Light == TRUE)
	{
		//关闭
		m_Light = FALSE;
		GetDlgItem(IDC_BUTTON_LIGHT)->SetWindowText("开");
	}
	else
	{
		//打开
		m_Light = TRUE;
		GetDlgItem(IDC_BUTTON_LIGHT)->SetWindowText("关");
	}
	SendButtonSerialData(10);
}

//排风风机1
void CGreenHouseDlg::OnBnClickedButtonFan1()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_Fan1 == TRUE)
	{
		//关闭
		m_Fan1 = FALSE;
		GetDlgItem(IDC_BUTTON_FAN1)->SetWindowText("开");
	}
	else
	{
		//打开
		m_Fan1 = TRUE;
		GetDlgItem(IDC_BUTTON_FAN1)->SetWindowText("关");
	}
	SendButtonSerialData(0);
}

//排风风机2
void CGreenHouseDlg::OnBnClickedButtonFan2()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_Fan2 == TRUE)
	{
		//关闭
		m_Fan2 = FALSE;
		GetDlgItem(IDC_BUTTON_FAN2)->SetWindowText("开");
	}
	else
	{
		//打开
		m_Fan2 = TRUE;
		GetDlgItem(IDC_BUTTON_FAN2)->SetWindowText("关");
	}
	SendButtonSerialData(1);
}

//轴流风机1
void CGreenHouseDlg::OnBnClickedButtonFan3()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_Fan3 == TRUE)
	{
		//关闭
		m_Fan3 = FALSE;
		GetDlgItem(IDC_BUTTON_FAN3)->SetWindowText("开");
	}
	else
	{
		//打开
		m_Fan3 = TRUE;
		GetDlgItem(IDC_BUTTON_FAN3)->SetWindowText("关");
	}
	SendButtonSerialData(2);
}

//轴流风机2
void CGreenHouseDlg::OnBnClickedButtonFan4()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_Fan4 == TRUE)
	{
		//关闭
		m_Fan4 = FALSE;
		GetDlgItem(IDC_BUTTON_FAN4)->SetWindowText("开");
	}
	else
	{
		//打开
		m_Fan4 = TRUE;
		GetDlgItem(IDC_BUTTON_FAN4)->SetWindowText("关");
	}
	SendButtonSerialData(3);
}


//天窗
void CGreenHouseDlg::OnBnClickedButtonElectricMachinery1()
{
	// TODO: 在此添加控件通知处理程序代码
	//判断保温帘是否关闭 关闭了则不能控制天窗
	if (m_ElectricMachinery3 == FALSE)
	{
		MessageBox("保温帘关闭了 不能控制天窗！");
		return;
	}

	if (m_ElectricMachinery1 == TRUE)
	{
		//关闭
		m_ElectricMachinery1 = FALSE;
		GetDlgItem(IDC_BUTTON_ELECTRIC_MACHINERY1)->SetWindowText("开");
	}
	else
	{
		//打开
		m_ElectricMachinery1 = TRUE;
		GetDlgItem(IDC_BUTTON_ELECTRIC_MACHINERY1)->SetWindowText("关");
	}
	SendButtonSerialData(4);
}

//遮阳罩
void CGreenHouseDlg::OnBnClickedButtonElectricMachinery2()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_ElectricMachinery2 == TRUE)
	{
		//关闭
		m_ElectricMachinery2 = FALSE;
		GetDlgItem(IDC_BUTTON_ELECTRIC_MACHINERY2)->SetWindowText("开");
	}
	else
	{
		//打开
		m_ElectricMachinery2 = TRUE;
		GetDlgItem(IDC_BUTTON_ELECTRIC_MACHINERY2)->SetWindowText("关");
	}
	SendButtonSerialData(5);
}

//保温帘
void CGreenHouseDlg::OnBnClickedButtonElectricMachinery3()
{
	// TODO: 在此添加控件通知处理程序代码
	//判断天窗是否打开  打开了则不能控制保温帘
	if (m_ElectricMachinery1 == TRUE)
	{
		MessageBox("天窗打开了  不能控制保温帘！");
		return;
	}

	if (m_ElectricMachinery3 == TRUE)
	{
		//关闭
		m_ElectricMachinery3 = FALSE;
		GetDlgItem(IDC_BUTTON_ELECTRIC_MACHINERY3)->SetWindowText("开");
	}
	else
	{
		//打开
		m_ElectricMachinery3 = TRUE;
		GetDlgItem(IDC_BUTTON_ELECTRIC_MACHINERY3)->SetWindowText("关");
	}
	SendButtonSerialData(6);
}

//灌溉
void CGreenHouseDlg::OnBnClickedButtonWaterPump1()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_WaterPump1 == TRUE)
	{
		//关闭
		m_WaterPump1 = FALSE;
		GetDlgItem(IDC_BUTTON_WATER_PUMP1)->SetWindowText("开");
	}
	else
	{
		//打开
		m_WaterPump1 = TRUE;
		GetDlgItem(IDC_BUTTON_WATER_PUMP1)->SetWindowText("关");
	}
	SendButtonSerialData(7);
}

//水帘
void CGreenHouseDlg::OnBnClickedButtonWaterPump2()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_WaterPump2 == TRUE)
	{
		//关闭
		m_WaterPump2 = FALSE;
		GetDlgItem(IDC_BUTTON_WATER_PUMP2)->SetWindowText("开");
	}
	else
	{
		//打开
		m_WaterPump2 = TRUE;
		GetDlgItem(IDC_BUTTON_WATER_PUMP2)->SetWindowText("关");
	}
	SendButtonSerialData(8);
}

//加热
void CGreenHouseDlg::OnBnClickedButtonWaterPump3()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_WaterPump3 == TRUE)
	{
		//关闭
		m_WaterPump3 = FALSE;
		GetDlgItem(IDC_BUTTON_WATER_PUMP3)->SetWindowText("开");
	}
	else
	{
		//打开
		m_WaterPump3 = TRUE;
		GetDlgItem(IDC_BUTTON_WATER_PUMP3)->SetWindowText("关");
	}
	SendButtonSerialData(9);
}

//发送按键消息串口数据
void CGreenHouseDlg::SendButtonSerialData(int type)
{
	PKT pkt;
	byte * payload = NULL;
	UINT paylen = 0;
	byte cmd = 0;

	memset(&pkt, 0, sizeof(PKT));
	switch (type)
	{
	case 0:
		{
			paylen = 4;
			payload = new byte[4];
			memset(payload, 0xaa, 4);

			//排风风机1
			if (m_Fan1 == TRUE)
			{
				payload[0] = 'N';
			}
			else
			{
				payload[0] = 'F';
			}

			cmd = INODE_FAN_TYPE;
		}
		break;
	case 1:
		{
			paylen = 4;
			payload = new byte[4];
			memset(payload, 0xaa, 4);

			//排风风机1
			if (m_Fan2 == TRUE)
			{
				payload[1] = 'N';
			}
			else
			{
				payload[1] = 'F';
			}

			cmd = INODE_FAN_TYPE;
		}
		break;
	case 2:
		{
			paylen = 4;
			payload = new byte[4];
			memset(payload, 0xaa, 4);

			//排风风机1
			if (m_Fan3 == TRUE)
			{
				payload[2] = 'N';
			}
			else
			{
				payload[2] = 'F';
			}

			cmd = INODE_FAN_TYPE;
		}
		break;
	case 3:
		{
			paylen = 4;
			payload = new byte[4];
			memset(payload, 0xaa, 4);

			//排风风机1
			if (m_Fan4 == TRUE)
			{
				payload[3] = 'N';
			}
			else
			{
				payload[3] = 'F';
			}

			cmd = INODE_FAN_TYPE;
		}
		break;
	case 4://天窗
		{
			paylen = 1;
			payload = new byte[1];
			if (m_ElectricMachinery1 == TRUE)
			{
				payload[0] = 'O';
			}
			else
			{
				payload[0] = 'C';
			}
			cmd = INODE_SKY_LIGHT_TYPE;
		}
		break;
	case 5://遮阳罩
		{
			paylen = 1;
			payload = new byte[1];
			if (m_ElectricMachinery2 == TRUE)
			{
				payload[0] = 'O';
			}
			else
			{
				payload[0] = 'C';
			}
			cmd = INODE_VISOR_TYPE;
		}
		break;
	case 6://保温帘
		{
			paylen = 1;
			payload = new byte[1];
			if (m_ElectricMachinery3 == TRUE)
			{
				payload[0] = 'O';
			}
			else
			{
				payload[0] = 'C';
			}
			cmd = INODE_HEAT_PRESS_TYPE;
		}
		break;
	case 7://灌溉
		{
			paylen = 4;
			payload = new byte[4];
			memset(payload, 0xaa, 4);

			if (m_WaterPump1 == TRUE)
			{
				payload[2] = 'N';
			}
			else
			{
				payload[2] = 'F';
			}

			cmd = INODE_WATER_HOT_PUMP_TYPE;
		}
		break;
	case 8://水帘
		{
			paylen = 4;
			payload = new byte[4];
			memset(payload, 0xaa, 4);

			if (m_WaterPump2 == TRUE)
			{
				payload[3] = 'N';
			}
			else
			{
				payload[3] = 'F';
			}

			cmd = INODE_WATER_HOT_PUMP_TYPE;
		}
		break;
	case 9://加热
		{
			paylen = 4;
			payload = new byte[4];
			memset(payload, 0xaa, 4);

			if (m_WaterPump3 == TRUE)
			{
				payload[0] = 'N';
				payload[1] = 'N';
			}
			else
			{
				payload[0] = 'F';
				payload[1] = 'F';
			}

			cmd = INODE_WATER_HOT_PUMP_TYPE;
		}
		break;
	case 10:
		{
			paylen = 1;
			payload = new byte[1];

			if (m_Light == TRUE)
			{
				payload[0] = 'N';
			}
			else
			{
				payload[0] = 'F';
			}
			cmd = INODE_LIGHT_SWITCH_TYPE;
		}
		break;
	default:
		break;
	}
	m_serial->MakeCMDPKT(&pkt, cmd, true, payload, paylen);
	m_serial->serialsenddata((byte *)&pkt, pkt.length+2, false);
	delete payload;
	payload = NULL;
}

//单选按钮响应
void CGreenHouseDlg::OnBnClickedRadioRealtime()
{	
	RECT rect;

	GetDlgItem(IDC_STATIC_SHOW)->GetWindowRect(&rect);
	rect.top += 100;
	rect.left += 1;
	rect.right -= 1;
	rect.bottom -= 1;
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	ComboBoxInit(m_radioVal);
	switch(m_radioVal)
	{
	case 0://时实曲线
		OutputDebugString("----------0---------\n");
		GetDlgItem(IDC_CHECK_TIME)->EnableWindow(FALSE);
		GetDlgItem(IDC_DATETIM_START_DATE)->EnableWindow(FALSE);
		GetDlgItem(IDC_DATETIM_END_DATE)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_SEARCH)->EnableWindow(FALSE);

		m_wavedlg->ShowWindow(true);
		OnCbnSelchangeComboType();
		RemoveChildwnd();
		//隐藏表格 dlg
		m_hisForm->ShowWindow(FALSE);
		m_winddlg->ShowWindow(FALSE);
		break;
	case 1://历史曲线
		OutputDebugString("----------1---------\n");
		GetDlgItem(IDC_CHECK_TIME)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_SEARCH)->EnableWindow(TRUE);
		OnBnClickedCheckTime();
		m_wavedlg->ShowWindow(true);
		RemoveChildwnd();
		//隐藏表格 dlg
		m_hisForm->ShowWindow(FALSE);
		m_winddlg->ShowWindow(FALSE);
		break;
	case 2://历史表格
		OutputDebugString("----------2---------\n");
		GetDlgItem(IDC_CHECK_TIME)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_SEARCH)->EnableWindow(TRUE);
		OnBnClickedCheckTime();

		//显示表格 dlg

		//m_hisForm->MoveWindow(rect.left, rect.top, (rect.right - rect.left), (rect.bottom - rect.top));
		RemoveChildwnd();
		m_hisForm->ShowWindow(TRUE);
		m_wavedlg->ShowWindow(FALSE);
		m_winddlg->ShowWindow(FALSE);
		break;
	default:
		break;
	}
}

//历史数据搜索按钮
void CGreenHouseDlg::OnBnClickedButtonSearch()
{
	// TODO: 在此添加控件通知处理程序代码

	if (m_getTime == TRUE)
	{
		CTime tm;
		m_startDate.GetTime(tm);
		m_startTime.Format("%d-%d-%d %d:%d:%d", tm.GetYear(), tm.GetMonth(), tm.GetDay(), tm.GetHour(), tm.GetMinute(), tm.GetSecond());

		m_endDate.GetTime(tm);
		m_endTime.Format("%d-%d-%d %d:%d:%d", tm.GetYear(), tm.GetMonth(), tm.GetDay(), tm.GetHour(), tm.GetMinute(), tm.GetSecond());
	}
	else
	{
		m_startTime = "";
		m_endTime = "";
	}

	//获取参数
	SelectInfo info;
	info.startTime = m_startTime;
	info.endTime = m_endTime;
	int type = m_type.GetCurSel();
	int ret = m_mySQL->SelectData(&info, (DATA_TYPE)(type+1));
	if (ret != 0)
	{
		return;
	}
	//调用显示图的界面
	switch(GetShowType())
	{
	case 1://历史曲线
		{
			InitWaveForm(GetShowType());
			double * xres = new double[info.infoList.size()];
			double * yres = new double[info.infoList.size()];
			int i = 0;
			//COleDateTime t1(COleDateTime::GetCurrentTime());  
			//COleDateTimeSpan tsp(0,0,1,0);
			for (vector<BaseInfo>::iterator iter = info.infoList.begin(); iter != info.infoList.end(); iter++)
			{
				COleDateTime t1;
				int year = atoi(iter->time.Mid(0,4));
				int month = atoi(iter->time.Mid(5,2));
				int day = atoi(iter->time.Mid(8,2));
				int hour = atoi(iter->time.Mid(11,2));
				int minite = atoi(iter->time.Mid(14,2));
				int second = atoi(iter->time.Mid(17,2));
				t1.SetDateTime(year, month, day, hour, minite, second);
				CString str = "";
				str.Format("%d-%d-%d %d:%d:%d\n", t1.GetYear(), t1.GetMonth(), t1.GetDay(), t1.GetHour(), t1.GetMinute(), t1.GetSecond());
				OutputDebugString(str);
				xres[i] = t1.m_dt;
				yres[i] = (double) atof(iter->info);
				//t1 += tsp;
				i++;
				str = "";
				str.Format("--%d--\n", i);
				OutputDebugString(str);
			}
			m_wavedlg->DrawLineStaticChart(xres, yres, info.infoList.size());
			delete xres;
			delete yres;
		}
		break;
	case 2://历史表格
		m_hisForm->SetFormValue(&info);
		break;
	default:
		break;
	}
}


void CGreenHouseDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码

}


void CGreenHouseDlg::OnMove(int x, int y)
{
	CDialogEx::OnMove(x, y);

	// TODO: 在此处添加消息处理程序代码
	//RECT rect;
	//GetDlgItem(IDC_STATIC_SHOW)->GetWindowRect(&rect);
	//rect.top += 100;
	//rect.left += 1;
	//rect.right -= 1;
	//rect.bottom -= 1;
	//m_hisForm->MoveWindow(rect.left, rect.top, (rect.right - rect.left), (rect.bottom - rect.top));
	if(this->GetDlgItem(IDC_STATIC_SHOW))
	{
		RemoveChildwnd();
	}
}


void CGreenHouseDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (nID == 0xF003 || nID == 0xF002 || nID == 0xF001 || nID == 0xF007 || nID == 0xF006 || nID == 0xF009 || nID == 0xF008 || nID == 0xF004 || nID == 0xF005)
	{
		return;
	}

	CDialogEx::OnSysCommand(nID, lParam);
}

//选择时间
void CGreenHouseDlg::OnBnClickedCheckTime()
{
	// TODO: 在此添加控件通知处理程序代码
	if (BST_CHECKED == IsDlgButtonChecked(IDC_CHECK_TIME))
	{
		//选中
		GetDlgItem(IDC_DATETIM_START_DATE)->EnableWindow(TRUE);
		GetDlgItem(IDC_DATETIM_END_DATE)->EnableWindow(TRUE);
		m_getTime = TRUE;
	}
	else
	{
		//未选中
		GetDlgItem(IDC_DATETIM_START_DATE)->EnableWindow(FALSE);
		GetDlgItem(IDC_DATETIM_END_DATE)->EnableWindow(FALSE);
		m_getTime = FALSE;
	}
}
void CGreenHouseDlg::RemoveChildwnd()
{
	RECT rect;
	GetDlgItem(IDC_STATIC_SHOW)->GetWindowRect(&rect);
	ScreenToClient(&rect);
	rect.top += 100;
	rect.left += 1;
	rect.right -= 1;
	rect.bottom -= 1;
	m_wavedlg->MoveWindow(rect.left, rect.top, (rect.right - rect.left), (rect.bottom - rect.top));
	m_hisForm->MoveWindow(rect.left, rect.top, (rect.right - rect.left), (rect.bottom - rect.top));
}

void CGreenHouseDlg::OnBnClickedButtonStartCap()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_CapStatus == TRUE)
	{
		//关闭
		m_CapStatus = FALSE;
		GetDlgItem(IDC_BUTTON_START_CAP)->SetWindowText("开始采集");
		//SetTimer(TIMER_ID_GET_DATA, 5000, NULL);
		KillTimer(TIMER_ID_GET_DATA);
		KillTimer(TIMER_ID_START_DATA);
	}
	else
	{
		//开始
		m_CapStatus = TRUE;
		GetDlgItem(IDC_BUTTON_START_CAP)->SetWindowText("停止采集");
		//KillTimer(TIMER_ID_GET_DATA);
		SetTimer(TIMER_ID_START_DATA, 5000, NULL);
	}
}


//下拉框变化的事件 只对时实曲线图有效
void CGreenHouseDlg::OnCbnSelchangeComboType()
{
	// TODO: 在此添加控件通知处理程序代码
	if (GetShowType() == 0)
	{
		//变化显示图
		InitWaveForm(GetShowType());
	}
}

void CGreenHouseDlg::InitWaveForm(int type)
{
	m_ComboStatus = m_type.GetCurSel();
	

	m_wavedlg->ClearAllSeries();
	if(m_ComboStatus !=6)
	{
		m_winddlg->ShowWindow(FALSE);
		//m_wavedlg->ShowWindow(true);
	
	}else
	{
		m_winddlg->ShowWindow(true);
		//m_wavedlg->ShowWindow(FALSE);
	}
	switch (m_ComboStatus)
	{
	case 0:
		m_wavedlg->SetXYtittle("光照", "时间", "光照度传感器");
		break;
	case 1:
		m_wavedlg->SetXYtittle("温度", "时间", "环境温度传感器");
		break;
	case 2:
		m_wavedlg->SetXYtittle("湿度", "时间", "环境湿度传感器");
		break;
	case 3:
		m_wavedlg->SetXYtittle("二氧化碳", "时间", "二氧化碳传感器");
		break;
	case 4:
		m_wavedlg->SetXYtittle("土壤温度", "时间", "土壤温度传感器");
		break;
	case 5:
		m_wavedlg->SetXYtittle("土壤湿度", "时间", "土壤湿度传感器");
		break;
	case 6:
		m_wavedlg->SetXYtittle("风速", "时间", "风速传感器");
		break;
	case 7:
		//m_wavedlg->SetXYtittle("风向", "时间", "风向传感器");
	
		break;
	default:
		break;
	}

	if (type == 0)
	{
		m_wavedlg->SetPanCtrl(false);
		m_wavedlg->SetZoomCtrl(false);
		m_wavedlg->SetCrosskCtrl(false);
		m_wavedlg->SetBottomTickLabelFormat(false);
	}else
	{
		m_wavedlg->SetPanCtrl(true);
		m_wavedlg->SetZoomCtrl(true);
		m_wavedlg->SetCrosskCtrl(true);
		m_wavedlg->SetBottomTickLabelFormat(true);
	}
}

void SendGetDataThread(void * arg)
{
	CGreenHouseDlg * pDlg = (CGreenHouseDlg *)arg;

	for(int i = 0; i < 5; i++)
	{
		pDlg->SendSensorSerialData(i);
		Sleep(500);
	}
}

void CGreenHouseDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	static int i = 0;
	switch (nIDEvent)
	{
	case TIMER_ID_START_DATA:
		{
			//i = 0;
			//KillTimer(TIMER_ID_START_DATA);
			//SetTimer(TIMER_ID_GET_DATA, 500, NULL);
			_beginthread(SendGetDataThread, 0, this);
		}
		break;
	case TIMER_ID_GET_DATA:
		{
			//发送采集数据消息
			SendSensorSerialData(i++);
			if (i == 5)
			{
				i = 0;
				KillTimer(TIMER_ID_GET_DATA);
				SetTimer(TIMER_ID_START_DATA, 5000, NULL);
			}
		}
		break;
	default:
		break;
	}

	CDialogEx::OnTimer(nIDEvent);
}

//发送  采集传感器信息消息
void CGreenHouseDlg::SendSensorSerialData(int i)
{
	PKT pkt;
	UINT paylen = 0;
	byte cmd = 0;

	memset(&pkt, 0, sizeof(PKT));
	switch (i)
	{
		case 0: cmd = INODE_TEM_HUM_TYPE; break;
		case 1: cmd = INODE_CO2_TYPE; break;
		case 2: cmd = INODE_LIGHT_TYPE; break;
		case 3: cmd = INODE_SIOL_TEM_HUM_TYPE; break;
		case 4: cmd = INODE_WIND_TYPE; break;
		default: break;
	}
	m_serial->MakeCMDPKT(&pkt, cmd, false, NULL, 0);
	m_serial->serialsenddata((byte *)&pkt, pkt.length+2, false);
}

void InitInfoBasePing(BaseInfo * base, byte num1, byte num2)
{
	base->info = "";
	base->info.Format("%d.%d", num1, num2);
}

void InitInfoBaseAdd(BaseInfo * base, byte num1, byte num2)
{
	base->info = "";
	base->info.Format("%d", num1*256 + num2);
}

//处理串口接收数据
LRESULT CGreenHouseDlg::OnUserPostMsg(WPARAM wParam, LPARAM lParam)
{
	PKT * pkt = (PKT *)wParam;

	int OldTemp = 20;
	SYSTEMTIME tm;
	BaseInfo base;
	BOOL bWriteForm = FALSE;
	GetLocalTime(&tm);
	base.time.Format("%d-%d-%d %d:%d:%d", tm.wYear, tm.wMonth, tm.wDay, tm.wHour, tm.wMinute, tm.wSecond);

	switch (pkt->num)
	{
	case INODE_TEM_HUM_TYPE://环境温湿度传感器节点
		{
			//写数据库
			InitInfoBasePing(&base, pkt->payload[0], pkt->payload[1]);
			int temp = atoi(base.info.GetBuffer());
			base.info.Format("%d", temp - 20);
			OldTemp = temp - 20;
			m_mySQL->InsertData(&base, DATA_TYPE_TEMP);

			//自动控制
			if (m_AutoCtrlStatus == TRUE)
			{
				AutoCtrl(2, atof(base.info));
			}

			InitInfoBasePing(&base, pkt->payload[2], pkt->payload[3]);
			m_mySQL->InsertData(&base, DATA_TYPE_HUMIDITY);

			//自动控制
			if (m_AutoCtrlStatus == TRUE)
			{
				AutoCtrl(3, atof(base.info));
			}

			if ((m_ComboStatus == 1) || (m_ComboStatus == 2)) bWriteForm = TRUE;
			if (m_ComboStatus == 1)
			{
				InitInfoBasePing(&base, pkt->payload[0], pkt->payload[1]);
				int temp = atoi(base.info.GetBuffer());
				base.info.Format("%d", temp - 20);
			}
		}
		break;
	case INODE_CO2_TYPE://二氧化碳传感器节点
		{
			//写数据库
			InitInfoBaseAdd(&base, pkt->payload[0], pkt->payload[1]);
			m_mySQL->InsertData(&base, DATA_TYPE_CO2);

			if (m_ComboStatus == 3) bWriteForm = TRUE;
		}
		break;
	case INODE_LIGHT_TYPE://光照度传感器节点
		{
			//写数据库
			InitInfoBaseAdd(&base, pkt->payload[0], pkt->payload[1]);
			m_mySQL->InsertData(&base, DATA_TYPE_LIGHT);
			if (m_ComboStatus == 0) bWriteForm = TRUE;

			//自动控制
			if (m_AutoCtrlStatus == TRUE)
			{
				AutoCtrl(0, atof(base.info));
			}
		}
		break;
	case INODE_SIOL_TEM_HUM_TYPE://土壤温湿度传感器节点
		{
			//写数据库
			InitInfoBasePing(&base, pkt->payload[0], pkt->payload[1]);
			//int temp = atoi(base.info.GetBuffer());
			base.info.Format("%d", OldTemp - 5);
			m_mySQL->InsertData(&base, DATA_TYPE_SOIL_TEMP);

			InitInfoBasePing(&base, pkt->payload[2], pkt->payload[3]);
			m_mySQL->InsertData(&base, DATA_TYPE_SOIL_HUMIDITY);

			//自动控制
			if (m_AutoCtrlStatus == TRUE)
			{
				AutoCtrl(1, atof(base.info));
			}

			if ((m_ComboStatus == 4) || (m_ComboStatus == 5)) bWriteForm = TRUE;
			if (m_ComboStatus == 4) 
			{
				base.info.Format("%d", OldTemp - 5);
			}
		}
		break;
	case INODE_FAN_TYPE://排风轴流风机控制节点
		{
			if (pkt->payload[0] == 'N')
			{
				//排风风机1开
				GetDlgItem(IDC_BUTTON_FAN1)->SetWindowTextA("关");
				m_Fan1 = TRUE;
			}
			else if (pkt->payload[0] == 'F')
			{
				//排风风机1关
				GetDlgItem(IDC_BUTTON_FAN1)->SetWindowTextA("开");
				m_Fan1 = FALSE;
			}

			if (pkt->payload[1] == 'N')
			{
				//排风风机2开
				GetDlgItem(IDC_BUTTON_FAN2)->SetWindowTextA("关");
				m_Fan2 = TRUE;
			}
			else if (pkt->payload[1] == 'F')
			{
				//排风风机2关
				GetDlgItem(IDC_BUTTON_FAN2)->SetWindowTextA("开");
				m_Fan2 = FALSE;
			}

			if (pkt->payload[2] == 'N')
			{
				//轴流风机1开
				GetDlgItem(IDC_BUTTON_FAN3)->SetWindowTextA("关");
				m_Fan3 = TRUE;
			}
			else if (pkt->payload[2] == 'F')
			{
				//轴流风机1关
				GetDlgItem(IDC_BUTTON_FAN3)->SetWindowTextA("开");
				m_Fan3 = FALSE;
			}

			if (pkt->payload[3] == 'N')
			{
				//轴流风机2开
				GetDlgItem(IDC_BUTTON_FAN4)->SetWindowTextA("关");
				m_Fan4 = TRUE;
			}
			else if (pkt->payload[3] == 'F')
			{
				//轴流风机2关
				GetDlgItem(IDC_BUTTON_FAN4)->SetWindowTextA("开");
				m_Fan4 = FALSE;
			}
		}
		break;
	case INODE_LIGHT_SWITCH_TYPE://照明控制节点
		{
			if (pkt->payload[0] == 'N')
			{
				//轴流风机2开
				GetDlgItem(IDC_BUTTON_LIGHT)->SetWindowTextA("关");
				m_Light = TRUE;
			}
			else if (pkt->payload[0] == 'F')
			{
				//轴流风机2关
				GetDlgItem(IDC_BUTTON_LIGHT)->SetWindowTextA("开");
				m_Light = FALSE;
			}
		}
		break;
	case INODE_WATER_HOT_PUMP_TYPE://水泵、热泵、水帘控制节点
		{
			if (pkt->payload[0] == 'N')
			{
				//加热控制开
				GetDlgItem(IDC_BUTTON_WATER_PUMP3)->SetWindowTextA("关");
				m_WaterPump3 = TRUE;
			}
			else if (pkt->payload[0] == 'F')
			{
				//加热控制关
				GetDlgItem(IDC_BUTTON_WATER_PUMP3)->SetWindowTextA("开");
				m_WaterPump3 = FALSE;
			}

			if (pkt->payload[2] == 'N')
			{
				//水泵控制开
				GetDlgItem(IDC_BUTTON_WATER_PUMP1)->SetWindowTextA("关");
				m_WaterPump1 = TRUE;
			}
			else if (pkt->payload[2] == 'F')
			{
				//水泵控制关
				GetDlgItem(IDC_BUTTON_WATER_PUMP1)->SetWindowTextA("开");
				m_WaterPump1 = FALSE;
			}

			if (pkt->payload[3] == 'N')
			{
				//水帘控制开
				GetDlgItem(IDC_BUTTON_WATER_PUMP2)->SetWindowTextA("关");
				m_WaterPump2 = TRUE;
			}
			else if (pkt->payload[3] == 'F')
			{
				//水帘控制关
				GetDlgItem(IDC_BUTTON_WATER_PUMP2)->SetWindowTextA("开");
				m_WaterPump2 = FALSE;
			}
		}
		break;
	case INODE_SKY_LIGHT_TYPE://	天窗	0xA1
		{
			if (pkt->payload[0] == 'O')
			{
				//天窗 开
				GetDlgItem(IDC_BUTTON_ELECTRIC_MACHINERY1)->SetWindowTextA("关");
				m_ElectricMachinery1 = TRUE;
			}
			else if (pkt->payload[0] == 'C')
			{
				//天窗 关
				GetDlgItem(IDC_BUTTON_ELECTRIC_MACHINERY1)->SetWindowTextA("开");
				m_ElectricMachinery1 = FALSE;
			}
		}
		break;
	case INODE_VISOR_TYPE://遮阳罩	0xA2
		{
			if (pkt->payload[0] == 'O')
			{
				//遮阳罩 开
				GetDlgItem(IDC_BUTTON_ELECTRIC_MACHINERY2)->SetWindowTextA("关");
				m_ElectricMachinery2 = TRUE;
			}
			else if (pkt->payload[0] == 'C')
			{
				//遮阳罩 关
				GetDlgItem(IDC_BUTTON_ELECTRIC_MACHINERY2)->SetWindowTextA("开");
				m_ElectricMachinery2 = FALSE;
			}
		}
		break;
	case INODE_HEAT_PRESS_TYPE://保温帘	0xA3
		{
			if (pkt->payload[0] == 'O')
			{
				//保温帘 开
				GetDlgItem(IDC_BUTTON_ELECTRIC_MACHINERY3)->SetWindowTextA("关");
				m_ElectricMachinery3 = TRUE;
			}
			else if (pkt->payload[0] == 'C')
			{
				//保温帘 关
				GetDlgItem(IDC_BUTTON_ELECTRIC_MACHINERY3)->SetWindowTextA("开");
				m_ElectricMachinery3 = FALSE;
			}
		}
		break;
	case INODE_WIND_TYPE://风速风向传感器节点	0xB4
		{
			//写数据库
			InitInfoBasePing(&base, pkt->payload[0], pkt->payload[1]);
			m_mySQL->InsertData(&base, DATA_TYPE_WIND_SPEED);

			InitInfoBaseAdd(&base, pkt->payload[2], pkt->payload[3]);
			m_winddlg->DrawWindPic(atoi(base.info.GetBuffer()));
			m_mySQL->InsertData(&base, DATA_TYPE_WIND_DIRECTION);

			if ((m_ComboStatus == 6) || (m_ComboStatus == 7)) bWriteForm = TRUE;
			if (m_ComboStatus == 6)
				InitInfoBasePing(&base, pkt->payload[0], pkt->payload[1]);
		}
		break;

	default:break;
	}

	if (GetShowType() == 0) //时实图像模式
	{
		if (bWriteForm == TRUE)
		{
			//写时实图像
			COleDateTime t1(COleDateTime::GetCurrentTime());
			double x = atof(base.info);
			double y = t1.m_dt;
			m_wavedlg->DrawLineDyncChart(y, x);
		}
	}

	delete pkt;

	return 0;
}

//自动控制
void CGreenHouseDlg::OnBnClickedButtonAutoCtl()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_AutoCtrlStatus == FALSE)
	{
		//开始自动控制
		//打开设置对话框
		AutoParamSet * pParamDlg = new AutoParamSet(this);
		if (pParamDlg->DoModal() == IDOK)
		{
			//确定开始自动控制
			m_AutoCtrlStatus = TRUE;
			GetDlgItem(IDC_BUTTON_LIGHT)->EnableWindow(FALSE);
			GetDlgItem(IDC_BUTTON_ELECTRIC_MACHINERY1)->EnableWindow(FALSE);
			GetDlgItem(IDC_BUTTON_ELECTRIC_MACHINERY2)->EnableWindow(FALSE);
			GetDlgItem(IDC_BUTTON_ELECTRIC_MACHINERY3)->EnableWindow(FALSE);
			GetDlgItem(IDC_BUTTON_FAN1)->EnableWindow(FALSE);
			GetDlgItem(IDC_BUTTON_FAN2)->EnableWindow(FALSE);
			GetDlgItem(IDC_BUTTON_FAN3)->EnableWindow(FALSE);
			GetDlgItem(IDC_BUTTON_FAN4)->EnableWindow(FALSE);
			GetDlgItem(IDC_BUTTON_WATER_PUMP1)->EnableWindow(FALSE);
			GetDlgItem(IDC_BUTTON_WATER_PUMP2)->EnableWindow(FALSE);
			GetDlgItem(IDC_BUTTON_WATER_PUMP3)->EnableWindow(FALSE);
		}
	}
	else
	{
		//停止自动控制
		m_AutoCtrlStatus = FALSE;
		GetDlgItem(IDC_BUTTON_LIGHT)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_ELECTRIC_MACHINERY1)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_ELECTRIC_MACHINERY2)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_ELECTRIC_MACHINERY3)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_FAN1)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_FAN2)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_FAN3)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_FAN4)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_WATER_PUMP1)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_WATER_PUMP2)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_WATER_PUMP3)->EnableWindow(TRUE);
	}
}

void CGreenHouseDlg::AutoCtrl(int type, float value)	//自动控制 0光照 1土壤湿度 2大棚温度 3大棚湿度
{
	switch (type)
	{
	case 0:
		{
			if (value > (m_AutoCtrlLight + 100))
			{
				//关闭遮阳罩 和 照明灯
				if (m_ElectricMachinery2 == TRUE) OnBnClickedButtonElectricMachinery2();
				Sleep(300);
				if (m_Light == TRUE) OnBnClickedButtonLight();
			}
			else if (value < (m_AutoCtrlLight - 100))
			{
				//打开遮阳罩 和 照明灯
				if (m_ElectricMachinery2 == FALSE) OnBnClickedButtonElectricMachinery2();
				Sleep(300);
				if (m_Light == FALSE) OnBnClickedButtonLight();
			}
		}
		break;
	case 1:
		{
			if (value > (m_AutoCtrlSoilHum + 20))
			{
				//关闭水泵
				if (m_WaterPump1 == TRUE) OnBnClickedButtonWaterPump1();
			}
			else if (value < (m_AutoCtrlSoilHum - 10))
			{
				//打开水泵
				if (m_WaterPump1 == FALSE) OnBnClickedButtonWaterPump1();
			}
		}
		break;
	case 2:
		{
			if (value > (m_AutoCtrlHum + 10))
			{
				//关闭 风扇 水帘 打开天窗
				if (m_Fan1 == TRUE) OnBnClickedButtonFan1();
				Sleep(300);
				if (m_Fan2 == TRUE) OnBnClickedButtonFan2();
				Sleep(300);
				if (m_Fan3 == TRUE) OnBnClickedButtonFan3();
				Sleep(300);
				if (m_Fan4 == TRUE) OnBnClickedButtonFan4();
				Sleep(300);
				if (m_WaterPump2 == TRUE) OnBnClickedButtonWaterPump2();
				//if (m_ElectricMachinery1 == FALSE) OnBnClickedButtonElectricMachinery1();
			}
			else if (value < (m_AutoCtrlHum - 10))
			{
				//打开 风扇 水帘 关闭天窗
				if (m_Fan1 == FALSE) OnBnClickedButtonFan1();
				Sleep(300);
				if (m_Fan2 == FALSE) OnBnClickedButtonFan2();
				Sleep(300);
				if (m_Fan3 == FALSE) OnBnClickedButtonFan3();
				Sleep(300);
				if (m_Fan4 == FALSE) OnBnClickedButtonFan4();
				Sleep(300);
				if (m_WaterPump2 == FALSE) OnBnClickedButtonWaterPump2();
				//Wif (m_ElectricMachinery1 == TRUE) OnBnClickedButtonElectricMachinery1();
			}
		}
		break;
	case 3:
		{
			if (value > (m_AutoCtrlTemp + 5))
			{
				//打开 天窗 关闭 加热泵
				if (m_ElectricMachinery1 == FALSE) OnBnClickedButtonElectricMachinery1();
				Sleep(300);
				if (m_WaterPump3 == TRUE) OnBnClickedButtonWaterPump3();
			}
			else if (value < (m_AutoCtrlTemp - 5))
			{
				//关闭 天窗 打开 加热泵
				if (m_ElectricMachinery1 == TRUE) OnBnClickedButtonElectricMachinery1();
				Sleep(300);
				if (m_WaterPump3 == FALSE) OnBnClickedButtonWaterPump3();
			}
		}
		break;
	default: break;
	}
}