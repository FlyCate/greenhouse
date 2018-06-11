// MySerial.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "GreenHouse.h"
#include "MySerial.h"
#include "afxdialogex.h"
#include "GreenHouseDlg.h"
#define  COMBUFLEN 30
byte Bufcom[COMBUFLEN]={0};
// MySerial �Ի���


IMPLEMENT_DYNAMIC(MySerial, CDialogEx)

MySerial::MySerial(CWnd* pParent /*=NULL*/)
	: CDialogEx(MySerial::IDD, pParent)
	,m_open(false)
	,m_bund(115200)
	,m_com_name("")
	,m_com_index(0)
	,m_tm_id(256)
	,m_send_flag(false)
	,m_tmoutinf("")
{
	parent =  (CGreenHouseDlg *)pParent;
}

MySerial::~MySerial()
{
}

void MySerial::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_SERIAL, m_cb_sel);
	DDX_Control(pDX, IDC_COMBO_BAUD_RATE, m_cb_bund);
	DDX_Control(pDX, IDC_BUTTON_START, m_btn_open);
	DDX_Control(pDX, IDC_BUTTON_START2, m_btn_ok);
}


BEGIN_MESSAGE_MAP(MySerial, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_START, &MySerial::OnBnClickedButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_START2, &MySerial::OnBnClickedButtonStart2)
	ON_CBN_SELCHANGE(IDC_COMBO_SERIAL, &MySerial::OnCbnSelchangeComboSerial)
	ON_CBN_SELENDCANCEL(IDC_COMBO_BAUD_RATE, &MySerial::OnCbnSelendcancelComboBaudRate)
	ON_MESSAGE(WM_COMM_RXCHAR,  &MySerial::OnComm)  //��Ϣӳ��
	ON_WM_TIMER()
END_MESSAGE_MAP()


// MySerial ��Ϣ�������

//�������ڰ���
void MySerial::OnBnClickedButtonStart()
{
	m_open = !m_open;
	if(m_open)
	{
		
		//if(m_com.InitPort(this,m_com_index,m_bund))
		if(m_com.InitPort(this,m_com_index,m_bund, 'N',  8, 1,EV_RXCHAR,  1024))
		{
			m_com.StartMonitoring();
			m_btn_open.SetCheck(true);
			m_cb_sel.EnableWindow(FALSE);
			m_cb_bund.EnableWindow(FALSE);
			m_btn_open.SetWindowText("�رմ���");
		}else
		{
			m_cb_sel.EnableWindow(TRUE);
			m_cb_bund.EnableWindow(TRUE);

			MessageBox("����","û�з��ִ˴��ڻ��߱�ռ��");
			m_open=FALSE;
			m_btn_open.SetWindowText("��������");
		}
	}else
	{
		m_cb_sel.EnableWindow(TRUE);
		m_cb_bund.EnableWindow(TRUE);
		m_btn_open.SetWindowText("��������");
		m_com.StopMonitoring();
		m_com.ClosePort();
	}
}

//ȷ������
void MySerial::OnBnClickedButtonStart2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	this->ShowWindow(FALSE);

}

//����ѡ��comb�ı�
void MySerial::OnCbnSelchangeComboSerial()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString str;
	m_cb_sel.GetLBText(m_cb_sel.GetCurSel(),str);
	if (str.GetLength()>3)
	{
		str = str.Mid(3);
		m_com_index = atoi(str.GetString())	;
	}
}

//������combѡ��ı�
void MySerial::OnCbnSelendcancelComboBaudRate()
{
	CString str;
	m_cb_bund.GetLBText(m_cb_bund.GetCurSel(),str);
	if (str.GetLength()>0)
	{
		m_bund = atoi(str.GetString())	;
	}
}
/*��ʱʼ��*/
void MySerial::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (nIDEvent == m_tm_id)
	{
		if (m_send_flag == true)
		{    
			KillTimer(nIDEvent);
			if(!m_tmoutinf.IsEmpty())
				MessageBox(m_tmoutinf);
			m_tmoutinf = "";
			m_send_flag = false;
		}
		else
		{
			m_tmoutinf = "";
			KillTimer(nIDEvent);
		}
	}
	CDialogEx::OnTimer(nIDEvent);
}


BOOL MySerial::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_com.Hkey2ComboBox(m_cb_sel);
	CString str;
	if (m_cb_sel.GetCount()>0)
	{

		m_cb_sel.SetCurSel(0);

		m_cb_sel.GetLBText(m_cb_sel.GetCurSel(),str);
		if (str.GetLength()>3)
		{
			str = str.Mid(3);
			m_com_index = atoi(str.GetString())	;
		}
	}

	m_cb_bund.SetCurSel(1);

	m_cb_bund.GetLBText(m_cb_bund.GetCurSel(),str);
	if (str.GetLength()>0)
	{
		m_bund = atoi(str.GetString())	;
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
//���ڽ��պ���
LONG MySerial::OnComm(WPARAM ch,LPARAM port)
{
	static int num =0;
	byte data = (byte)ch;

	Bufcom[num++] = data;

	if (num >= COMBUFLEN)
	{
		num  = 0;
	}else
	{
		if (num == 1)
		{//У����ͷ
			if (Bufcom[0]  != FRAME_HEADER_UP)
			{
				num =0;
			}
		}else if (num > 3)
		{   //������α��
			if ((Bufcom[2]+2)  == num)
			{
				if (Bufcom[num-1] != FRAME_END)
				{
					num =0;
				}else
				{
					//������������
					PKT pkt;
					memcpy(&pkt,Bufcom,num);
					handerdatapkt(&pkt);
					num =0;
				}
			}
		}
	}
	return true;
}
void MySerial::handerdatapkt(PKT * pkt)
{
	CString str ="";
	m_send_flag = false;  //��շ��ͱ��

	PKT * msg = new PKT;
	memcpy(msg, pkt, sizeof(PKT));
	::PostMessage(parent->GetSafeHwnd(), WM_USER_POSTMSG, (WPARAM)msg, NULL);

	switch (pkt->num)
	{
	case INODE_TEM_HUM_TYPE://������ʪ�ȴ������ڵ�
		break;
	case INODE_CO2_TYPE://������̼�������ڵ�
		break;
	case INODE_LIGHT_TYPE://���նȴ������ڵ�
		break;
	case INODE_SIOL_TEM_HUM_TYPE://������ʪ�ȴ������ڵ�
		break;
	case INODE_FAN_TYPE://�ŷ�����������ƽڵ�
		break;
	case INODE_LIGHT_SWITCH_TYPE://�������ƽڵ�

		break;
	case INODE_WATER_HOT_PUMP_TYPE://ˮ�á��ȱá�ˮ�����ƽڵ�

		break;
	case INODE_SKY_LIGHT_TYPE://	�촰	0xA1

	case INODE_VISOR_TYPE://������	0xA2

		break;
	case INODE_HEAT_PRESS_TYPE://������	0xA3

		break;
	case INODE_WIND_TYPE://���ٷ��򴫸����ڵ�	0xB4

		break;

	default:break;
	}
}
//���ڷ���
bool  MySerial::serialsenddata(byte * p,int len)
{
	if (p == NULL || len <=  0)
	{
		return false;
	}
	if (!m_open)
	{ 
		MessageBox("���ȴ򿪴���");
		return false;
	}
	m_com.WriteToPort(p,  len);
	return true;
}

//���ڷ���,����ʱ����
bool  MySerial::serialsenddata(byte * p,int len,bool ischk,CString inf,DWORD ms)
{
	if (p == NULL || len <=  0 )
	{
		return false;
	}
	if (!m_open)
	{ 
	    MessageBox("���ȴ򿪴���");
		return false;
	}
	m_com.WriteToPort(p,  len);
	if (ischk)
	{
		m_tmoutinf = inf;
		m_send_flag = true;
		SetTimer(m_tm_id,ms,NULL);
	}
	return true;
}
VOID MySerial::MakeCMDPKT(PKT *pkt,byte cmd,bool iscontrl ,byte  *payload,byte paylen)
{
	if (pkt == NULL)
		return;
	if (paylen > 10)
		return;

	pkt->header = FRAME_HEADER_DOWN;
	pkt->num    = cmd;
	//pkt->length = 4 + paylen;
	pkt->length = 4 + 10;
	if (iscontrl)
		pkt->cmd = USER_CONTROL;
	else
		pkt->cmd = USER_COLLECTION;

	if (paylen > 0) memcpy(pkt->payload,payload,paylen);
	memset(&pkt->payload[paylen],0xaa,10-paylen);
	byte crc = 0;

	char *p = (char*)pkt;
	for (int i=0;i< pkt->length+2-2;i++)
	{
		crc += p[i];
	}
	pkt->payload[10] = crc;
	pkt->payload[10+1] = FRAME_END;
}
//����ר������
bool MySerial::send_cmd_whole_start_run(void)
{
	return true;

}
