
// GreenHouseDlg.cpp : ʵ���ļ�
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

// CGreenHouseDlg �Ի���




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


// CGreenHouseDlg ��Ϣ�������

BOOL CGreenHouseDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��
	/*�����������öԻ���*/
	m_Light = FALSE;//��������
	m_Fan1 = FALSE;	//�ŷ��������1
	m_Fan2 = FALSE;	//�ŷ��������2
	m_ElectricMachinery1 = FALSE;	//�촰
	m_ElectricMachinery2 = FALSE;	//������
	m_ElectricMachinery3 = FALSE;	//������
	m_WaterPump1 = FALSE;	//���
	m_WaterPump2 = FALSE;	//ˮ��
	m_WaterPump3 = FALSE;	//����
	m_CapStatus = FALSE;	//�ɼ�

	//���ñ�����Ϊ��״̬
	m_ElectricMachinery3 = TRUE;
	GetDlgItem(IDC_BUTTON_ELECTRIC_MACHINERY3)->SetWindowText("��");

	m_serial = new MySerial(this);
	m_serial->Create(IDD_DIALOG1, this);
	m_serial->ShowWindow(false);
	// TODO: �ڴ���Ӷ���ĳ�ʼ������

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
		MessageBox("���ݿ�δ����!");

	ComboBoxInit(0);

	m_startDate.SetFormat("yyyy-M-d HH:mm:ss");
	m_endDate.SetFormat("yyyy-M-d HH:mm:ss");
	OnBnClickedRadioRealtime();

	m_AutoCtrlStatus = FALSE;

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CGreenHouseDlg::ComboBoxInit(int type)
{
	m_type.ResetContent();
	m_type.InsertString(0, "���նȴ�����");
	m_type.InsertString(1, "�����¶ȴ�����");
	m_type.InsertString(2, "����ʪ�ȴ�����");
	m_type.InsertString(3, "������̼������");
	m_type.InsertString(4, "�����¶ȴ�����");
	m_type.InsertString(5, "����ʪ�ȴ�����");
	m_type.InsertString(6, "���ٴ�����");
	//if (type == 0) m_type.InsertString(7, "���򴫸���");
	m_type.SetCurSel(0);
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CGreenHouseDlg::OnPaint()
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

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CGreenHouseDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//��������
void CGreenHouseDlg::OnBnClickedButtonSerial()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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

//��������
void CGreenHouseDlg::OnBnClickedButtonLight()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_Light == TRUE)
	{
		//�ر�
		m_Light = FALSE;
		GetDlgItem(IDC_BUTTON_LIGHT)->SetWindowText("��");
	}
	else
	{
		//��
		m_Light = TRUE;
		GetDlgItem(IDC_BUTTON_LIGHT)->SetWindowText("��");
	}
	SendButtonSerialData(10);
}

//�ŷ���1
void CGreenHouseDlg::OnBnClickedButtonFan1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_Fan1 == TRUE)
	{
		//�ر�
		m_Fan1 = FALSE;
		GetDlgItem(IDC_BUTTON_FAN1)->SetWindowText("��");
	}
	else
	{
		//��
		m_Fan1 = TRUE;
		GetDlgItem(IDC_BUTTON_FAN1)->SetWindowText("��");
	}
	SendButtonSerialData(0);
}

//�ŷ���2
void CGreenHouseDlg::OnBnClickedButtonFan2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_Fan2 == TRUE)
	{
		//�ر�
		m_Fan2 = FALSE;
		GetDlgItem(IDC_BUTTON_FAN2)->SetWindowText("��");
	}
	else
	{
		//��
		m_Fan2 = TRUE;
		GetDlgItem(IDC_BUTTON_FAN2)->SetWindowText("��");
	}
	SendButtonSerialData(1);
}

//�������1
void CGreenHouseDlg::OnBnClickedButtonFan3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_Fan3 == TRUE)
	{
		//�ر�
		m_Fan3 = FALSE;
		GetDlgItem(IDC_BUTTON_FAN3)->SetWindowText("��");
	}
	else
	{
		//��
		m_Fan3 = TRUE;
		GetDlgItem(IDC_BUTTON_FAN3)->SetWindowText("��");
	}
	SendButtonSerialData(2);
}

//�������2
void CGreenHouseDlg::OnBnClickedButtonFan4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_Fan4 == TRUE)
	{
		//�ر�
		m_Fan4 = FALSE;
		GetDlgItem(IDC_BUTTON_FAN4)->SetWindowText("��");
	}
	else
	{
		//��
		m_Fan4 = TRUE;
		GetDlgItem(IDC_BUTTON_FAN4)->SetWindowText("��");
	}
	SendButtonSerialData(3);
}


//�촰
void CGreenHouseDlg::OnBnClickedButtonElectricMachinery1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//�жϱ������Ƿ�ر� �ر������ܿ����촰
	if (m_ElectricMachinery3 == FALSE)
	{
		MessageBox("�������ر��� ���ܿ����촰��");
		return;
	}

	if (m_ElectricMachinery1 == TRUE)
	{
		//�ر�
		m_ElectricMachinery1 = FALSE;
		GetDlgItem(IDC_BUTTON_ELECTRIC_MACHINERY1)->SetWindowText("��");
	}
	else
	{
		//��
		m_ElectricMachinery1 = TRUE;
		GetDlgItem(IDC_BUTTON_ELECTRIC_MACHINERY1)->SetWindowText("��");
	}
	SendButtonSerialData(4);
}

//������
void CGreenHouseDlg::OnBnClickedButtonElectricMachinery2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_ElectricMachinery2 == TRUE)
	{
		//�ر�
		m_ElectricMachinery2 = FALSE;
		GetDlgItem(IDC_BUTTON_ELECTRIC_MACHINERY2)->SetWindowText("��");
	}
	else
	{
		//��
		m_ElectricMachinery2 = TRUE;
		GetDlgItem(IDC_BUTTON_ELECTRIC_MACHINERY2)->SetWindowText("��");
	}
	SendButtonSerialData(5);
}

//������
void CGreenHouseDlg::OnBnClickedButtonElectricMachinery3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//�ж��촰�Ƿ��  �������ܿ��Ʊ�����
	if (m_ElectricMachinery1 == TRUE)
	{
		MessageBox("�촰����  ���ܿ��Ʊ�������");
		return;
	}

	if (m_ElectricMachinery3 == TRUE)
	{
		//�ر�
		m_ElectricMachinery3 = FALSE;
		GetDlgItem(IDC_BUTTON_ELECTRIC_MACHINERY3)->SetWindowText("��");
	}
	else
	{
		//��
		m_ElectricMachinery3 = TRUE;
		GetDlgItem(IDC_BUTTON_ELECTRIC_MACHINERY3)->SetWindowText("��");
	}
	SendButtonSerialData(6);
}

//���
void CGreenHouseDlg::OnBnClickedButtonWaterPump1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_WaterPump1 == TRUE)
	{
		//�ر�
		m_WaterPump1 = FALSE;
		GetDlgItem(IDC_BUTTON_WATER_PUMP1)->SetWindowText("��");
	}
	else
	{
		//��
		m_WaterPump1 = TRUE;
		GetDlgItem(IDC_BUTTON_WATER_PUMP1)->SetWindowText("��");
	}
	SendButtonSerialData(7);
}

//ˮ��
void CGreenHouseDlg::OnBnClickedButtonWaterPump2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_WaterPump2 == TRUE)
	{
		//�ر�
		m_WaterPump2 = FALSE;
		GetDlgItem(IDC_BUTTON_WATER_PUMP2)->SetWindowText("��");
	}
	else
	{
		//��
		m_WaterPump2 = TRUE;
		GetDlgItem(IDC_BUTTON_WATER_PUMP2)->SetWindowText("��");
	}
	SendButtonSerialData(8);
}

//����
void CGreenHouseDlg::OnBnClickedButtonWaterPump3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_WaterPump3 == TRUE)
	{
		//�ر�
		m_WaterPump3 = FALSE;
		GetDlgItem(IDC_BUTTON_WATER_PUMP3)->SetWindowText("��");
	}
	else
	{
		//��
		m_WaterPump3 = TRUE;
		GetDlgItem(IDC_BUTTON_WATER_PUMP3)->SetWindowText("��");
	}
	SendButtonSerialData(9);
}

//���Ͱ�����Ϣ��������
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

			//�ŷ���1
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

			//�ŷ���1
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

			//�ŷ���1
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

			//�ŷ���1
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
	case 4://�촰
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
	case 5://������
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
	case 6://������
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
	case 7://���
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
	case 8://ˮ��
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
	case 9://����
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

//��ѡ��ť��Ӧ
void CGreenHouseDlg::OnBnClickedRadioRealtime()
{	
	RECT rect;

	GetDlgItem(IDC_STATIC_SHOW)->GetWindowRect(&rect);
	rect.top += 100;
	rect.left += 1;
	rect.right -= 1;
	rect.bottom -= 1;
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	ComboBoxInit(m_radioVal);
	switch(m_radioVal)
	{
	case 0://ʱʵ����
		OutputDebugString("----------0---------\n");
		GetDlgItem(IDC_CHECK_TIME)->EnableWindow(FALSE);
		GetDlgItem(IDC_DATETIM_START_DATE)->EnableWindow(FALSE);
		GetDlgItem(IDC_DATETIM_END_DATE)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_SEARCH)->EnableWindow(FALSE);

		m_wavedlg->ShowWindow(true);
		OnCbnSelchangeComboType();
		RemoveChildwnd();
		//���ر�� dlg
		m_hisForm->ShowWindow(FALSE);
		m_winddlg->ShowWindow(FALSE);
		break;
	case 1://��ʷ����
		OutputDebugString("----------1---------\n");
		GetDlgItem(IDC_CHECK_TIME)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_SEARCH)->EnableWindow(TRUE);
		OnBnClickedCheckTime();
		m_wavedlg->ShowWindow(true);
		RemoveChildwnd();
		//���ر�� dlg
		m_hisForm->ShowWindow(FALSE);
		m_winddlg->ShowWindow(FALSE);
		break;
	case 2://��ʷ���
		OutputDebugString("----------2---------\n");
		GetDlgItem(IDC_CHECK_TIME)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_SEARCH)->EnableWindow(TRUE);
		OnBnClickedCheckTime();

		//��ʾ��� dlg

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

//��ʷ����������ť
void CGreenHouseDlg::OnBnClickedButtonSearch()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

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

	//��ȡ����
	SelectInfo info;
	info.startTime = m_startTime;
	info.endTime = m_endTime;
	int type = m_type.GetCurSel();
	int ret = m_mySQL->SelectData(&info, (DATA_TYPE)(type+1));
	if (ret != 0)
	{
		return;
	}
	//������ʾͼ�Ľ���
	switch(GetShowType())
	{
	case 1://��ʷ����
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
	case 2://��ʷ���
		m_hisForm->SetFormValue(&info);
		break;
	default:
		break;
	}
}


void CGreenHouseDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������

}


void CGreenHouseDlg::OnMove(int x, int y)
{
	CDialogEx::OnMove(x, y);

	// TODO: �ڴ˴������Ϣ����������
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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (nID == 0xF003 || nID == 0xF002 || nID == 0xF001 || nID == 0xF007 || nID == 0xF006 || nID == 0xF009 || nID == 0xF008 || nID == 0xF004 || nID == 0xF005)
	{
		return;
	}

	CDialogEx::OnSysCommand(nID, lParam);
}

//ѡ��ʱ��
void CGreenHouseDlg::OnBnClickedCheckTime()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (BST_CHECKED == IsDlgButtonChecked(IDC_CHECK_TIME))
	{
		//ѡ��
		GetDlgItem(IDC_DATETIM_START_DATE)->EnableWindow(TRUE);
		GetDlgItem(IDC_DATETIM_END_DATE)->EnableWindow(TRUE);
		m_getTime = TRUE;
	}
	else
	{
		//δѡ��
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_CapStatus == TRUE)
	{
		//�ر�
		m_CapStatus = FALSE;
		GetDlgItem(IDC_BUTTON_START_CAP)->SetWindowText("��ʼ�ɼ�");
		//SetTimer(TIMER_ID_GET_DATA, 5000, NULL);
		KillTimer(TIMER_ID_GET_DATA);
		KillTimer(TIMER_ID_START_DATA);
	}
	else
	{
		//��ʼ
		m_CapStatus = TRUE;
		GetDlgItem(IDC_BUTTON_START_CAP)->SetWindowText("ֹͣ�ɼ�");
		//KillTimer(TIMER_ID_GET_DATA);
		SetTimer(TIMER_ID_START_DATA, 5000, NULL);
	}
}


//������仯���¼� ֻ��ʱʵ����ͼ��Ч
void CGreenHouseDlg::OnCbnSelchangeComboType()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (GetShowType() == 0)
	{
		//�仯��ʾͼ
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
		m_wavedlg->SetXYtittle("����", "ʱ��", "���նȴ�����");
		break;
	case 1:
		m_wavedlg->SetXYtittle("�¶�", "ʱ��", "�����¶ȴ�����");
		break;
	case 2:
		m_wavedlg->SetXYtittle("ʪ��", "ʱ��", "����ʪ�ȴ�����");
		break;
	case 3:
		m_wavedlg->SetXYtittle("������̼", "ʱ��", "������̼������");
		break;
	case 4:
		m_wavedlg->SetXYtittle("�����¶�", "ʱ��", "�����¶ȴ�����");
		break;
	case 5:
		m_wavedlg->SetXYtittle("����ʪ��", "ʱ��", "����ʪ�ȴ�����");
		break;
	case 6:
		m_wavedlg->SetXYtittle("����", "ʱ��", "���ٴ�����");
		break;
	case 7:
		//m_wavedlg->SetXYtittle("����", "ʱ��", "���򴫸���");
	
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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
			//���Ͳɼ�������Ϣ
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

//����  �ɼ���������Ϣ��Ϣ
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

//�����ڽ�������
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
	case INODE_TEM_HUM_TYPE://������ʪ�ȴ������ڵ�
		{
			//д���ݿ�
			InitInfoBasePing(&base, pkt->payload[0], pkt->payload[1]);
			int temp = atoi(base.info.GetBuffer());
			base.info.Format("%d", temp - 20);
			OldTemp = temp - 20;
			m_mySQL->InsertData(&base, DATA_TYPE_TEMP);

			//�Զ�����
			if (m_AutoCtrlStatus == TRUE)
			{
				AutoCtrl(2, atof(base.info));
			}

			InitInfoBasePing(&base, pkt->payload[2], pkt->payload[3]);
			m_mySQL->InsertData(&base, DATA_TYPE_HUMIDITY);

			//�Զ�����
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
	case INODE_CO2_TYPE://������̼�������ڵ�
		{
			//д���ݿ�
			InitInfoBaseAdd(&base, pkt->payload[0], pkt->payload[1]);
			m_mySQL->InsertData(&base, DATA_TYPE_CO2);

			if (m_ComboStatus == 3) bWriteForm = TRUE;
		}
		break;
	case INODE_LIGHT_TYPE://���նȴ������ڵ�
		{
			//д���ݿ�
			InitInfoBaseAdd(&base, pkt->payload[0], pkt->payload[1]);
			m_mySQL->InsertData(&base, DATA_TYPE_LIGHT);
			if (m_ComboStatus == 0) bWriteForm = TRUE;

			//�Զ�����
			if (m_AutoCtrlStatus == TRUE)
			{
				AutoCtrl(0, atof(base.info));
			}
		}
		break;
	case INODE_SIOL_TEM_HUM_TYPE://������ʪ�ȴ������ڵ�
		{
			//д���ݿ�
			InitInfoBasePing(&base, pkt->payload[0], pkt->payload[1]);
			//int temp = atoi(base.info.GetBuffer());
			base.info.Format("%d", OldTemp - 5);
			m_mySQL->InsertData(&base, DATA_TYPE_SOIL_TEMP);

			InitInfoBasePing(&base, pkt->payload[2], pkt->payload[3]);
			m_mySQL->InsertData(&base, DATA_TYPE_SOIL_HUMIDITY);

			//�Զ�����
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
	case INODE_FAN_TYPE://�ŷ�����������ƽڵ�
		{
			if (pkt->payload[0] == 'N')
			{
				//�ŷ���1��
				GetDlgItem(IDC_BUTTON_FAN1)->SetWindowTextA("��");
				m_Fan1 = TRUE;
			}
			else if (pkt->payload[0] == 'F')
			{
				//�ŷ���1��
				GetDlgItem(IDC_BUTTON_FAN1)->SetWindowTextA("��");
				m_Fan1 = FALSE;
			}

			if (pkt->payload[1] == 'N')
			{
				//�ŷ���2��
				GetDlgItem(IDC_BUTTON_FAN2)->SetWindowTextA("��");
				m_Fan2 = TRUE;
			}
			else if (pkt->payload[1] == 'F')
			{
				//�ŷ���2��
				GetDlgItem(IDC_BUTTON_FAN2)->SetWindowTextA("��");
				m_Fan2 = FALSE;
			}

			if (pkt->payload[2] == 'N')
			{
				//�������1��
				GetDlgItem(IDC_BUTTON_FAN3)->SetWindowTextA("��");
				m_Fan3 = TRUE;
			}
			else if (pkt->payload[2] == 'F')
			{
				//�������1��
				GetDlgItem(IDC_BUTTON_FAN3)->SetWindowTextA("��");
				m_Fan3 = FALSE;
			}

			if (pkt->payload[3] == 'N')
			{
				//�������2��
				GetDlgItem(IDC_BUTTON_FAN4)->SetWindowTextA("��");
				m_Fan4 = TRUE;
			}
			else if (pkt->payload[3] == 'F')
			{
				//�������2��
				GetDlgItem(IDC_BUTTON_FAN4)->SetWindowTextA("��");
				m_Fan4 = FALSE;
			}
		}
		break;
	case INODE_LIGHT_SWITCH_TYPE://�������ƽڵ�
		{
			if (pkt->payload[0] == 'N')
			{
				//�������2��
				GetDlgItem(IDC_BUTTON_LIGHT)->SetWindowTextA("��");
				m_Light = TRUE;
			}
			else if (pkt->payload[0] == 'F')
			{
				//�������2��
				GetDlgItem(IDC_BUTTON_LIGHT)->SetWindowTextA("��");
				m_Light = FALSE;
			}
		}
		break;
	case INODE_WATER_HOT_PUMP_TYPE://ˮ�á��ȱá�ˮ�����ƽڵ�
		{
			if (pkt->payload[0] == 'N')
			{
				//���ȿ��ƿ�
				GetDlgItem(IDC_BUTTON_WATER_PUMP3)->SetWindowTextA("��");
				m_WaterPump3 = TRUE;
			}
			else if (pkt->payload[0] == 'F')
			{
				//���ȿ��ƹ�
				GetDlgItem(IDC_BUTTON_WATER_PUMP3)->SetWindowTextA("��");
				m_WaterPump3 = FALSE;
			}

			if (pkt->payload[2] == 'N')
			{
				//ˮ�ÿ��ƿ�
				GetDlgItem(IDC_BUTTON_WATER_PUMP1)->SetWindowTextA("��");
				m_WaterPump1 = TRUE;
			}
			else if (pkt->payload[2] == 'F')
			{
				//ˮ�ÿ��ƹ�
				GetDlgItem(IDC_BUTTON_WATER_PUMP1)->SetWindowTextA("��");
				m_WaterPump1 = FALSE;
			}

			if (pkt->payload[3] == 'N')
			{
				//ˮ�����ƿ�
				GetDlgItem(IDC_BUTTON_WATER_PUMP2)->SetWindowTextA("��");
				m_WaterPump2 = TRUE;
			}
			else if (pkt->payload[3] == 'F')
			{
				//ˮ�����ƹ�
				GetDlgItem(IDC_BUTTON_WATER_PUMP2)->SetWindowTextA("��");
				m_WaterPump2 = FALSE;
			}
		}
		break;
	case INODE_SKY_LIGHT_TYPE://	�촰	0xA1
		{
			if (pkt->payload[0] == 'O')
			{
				//�촰 ��
				GetDlgItem(IDC_BUTTON_ELECTRIC_MACHINERY1)->SetWindowTextA("��");
				m_ElectricMachinery1 = TRUE;
			}
			else if (pkt->payload[0] == 'C')
			{
				//�촰 ��
				GetDlgItem(IDC_BUTTON_ELECTRIC_MACHINERY1)->SetWindowTextA("��");
				m_ElectricMachinery1 = FALSE;
			}
		}
		break;
	case INODE_VISOR_TYPE://������	0xA2
		{
			if (pkt->payload[0] == 'O')
			{
				//������ ��
				GetDlgItem(IDC_BUTTON_ELECTRIC_MACHINERY2)->SetWindowTextA("��");
				m_ElectricMachinery2 = TRUE;
			}
			else if (pkt->payload[0] == 'C')
			{
				//������ ��
				GetDlgItem(IDC_BUTTON_ELECTRIC_MACHINERY2)->SetWindowTextA("��");
				m_ElectricMachinery2 = FALSE;
			}
		}
		break;
	case INODE_HEAT_PRESS_TYPE://������	0xA3
		{
			if (pkt->payload[0] == 'O')
			{
				//������ ��
				GetDlgItem(IDC_BUTTON_ELECTRIC_MACHINERY3)->SetWindowTextA("��");
				m_ElectricMachinery3 = TRUE;
			}
			else if (pkt->payload[0] == 'C')
			{
				//������ ��
				GetDlgItem(IDC_BUTTON_ELECTRIC_MACHINERY3)->SetWindowTextA("��");
				m_ElectricMachinery3 = FALSE;
			}
		}
		break;
	case INODE_WIND_TYPE://���ٷ��򴫸����ڵ�	0xB4
		{
			//д���ݿ�
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

	if (GetShowType() == 0) //ʱʵͼ��ģʽ
	{
		if (bWriteForm == TRUE)
		{
			//дʱʵͼ��
			COleDateTime t1(COleDateTime::GetCurrentTime());
			double x = atof(base.info);
			double y = t1.m_dt;
			m_wavedlg->DrawLineDyncChart(y, x);
		}
	}

	delete pkt;

	return 0;
}

//�Զ�����
void CGreenHouseDlg::OnBnClickedButtonAutoCtl()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_AutoCtrlStatus == FALSE)
	{
		//��ʼ�Զ�����
		//�����öԻ���
		AutoParamSet * pParamDlg = new AutoParamSet(this);
		if (pParamDlg->DoModal() == IDOK)
		{
			//ȷ����ʼ�Զ�����
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
		//ֹͣ�Զ�����
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

void CGreenHouseDlg::AutoCtrl(int type, float value)	//�Զ����� 0���� 1����ʪ�� 2�����¶� 3����ʪ��
{
	switch (type)
	{
	case 0:
		{
			if (value > (m_AutoCtrlLight + 100))
			{
				//�ر������� �� ������
				if (m_ElectricMachinery2 == TRUE) OnBnClickedButtonElectricMachinery2();
				Sleep(300);
				if (m_Light == TRUE) OnBnClickedButtonLight();
			}
			else if (value < (m_AutoCtrlLight - 100))
			{
				//�������� �� ������
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
				//�ر�ˮ��
				if (m_WaterPump1 == TRUE) OnBnClickedButtonWaterPump1();
			}
			else if (value < (m_AutoCtrlSoilHum - 10))
			{
				//��ˮ��
				if (m_WaterPump1 == FALSE) OnBnClickedButtonWaterPump1();
			}
		}
		break;
	case 2:
		{
			if (value > (m_AutoCtrlHum + 10))
			{
				//�ر� ���� ˮ�� ���촰
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
				//�� ���� ˮ�� �ر��촰
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
				//�� �촰 �ر� ���ȱ�
				if (m_ElectricMachinery1 == FALSE) OnBnClickedButtonElectricMachinery1();
				Sleep(300);
				if (m_WaterPump3 == TRUE) OnBnClickedButtonWaterPump3();
			}
			else if (value < (m_AutoCtrlTemp - 5))
			{
				//�ر� �촰 �� ���ȱ�
				if (m_ElectricMachinery1 == TRUE) OnBnClickedButtonElectricMachinery1();
				Sleep(300);
				if (m_WaterPump3 == FALSE) OnBnClickedButtonWaterPump3();
			}
		}
		break;
	default: break;
	}
}