#pragma once
#include "afxwin.h"
#include "SerialPort.h"
#define  FRAME_HEADER_UP 0xfd
#define  FRAME_END    0xFB

#define  FRAME_HEADER_DOWN 0xfc

#define INODE_TEM_HUM_TYPE  (0x09)  //环境温湿度传感器节点
#define INODE_CO2_TYPE (0x05)      //二氧化碳传感器节点
#define INODE_LIGHT_TYPE (0x02)    //光照度传感器节点
#define INODE_SIOL_TEM_HUM_TYPE (0xB1)   //土壤温湿度传感器节点
#define INODE_FAN_TYPE (0xA6)     //排风轴流风机控制节点
#define INODE_LIGHT_SWITCH_TYPE (0xA7)    //排风轴流风机1控制节点
#define INODE_WATER_HOT_PUMP_TYPE (0xA8) //水泵、热泵、水帘控制节点
#define INODE_SKY_LIGHT_TYPE (0xA1)    //	天窗	0xA1
#define INODE_VISOR_TYPE (0xA2)      //遮阳罩	0xA2
#define INODE_HEAT_PRESS_TYPE (0xA3)   //保温帘	0xA3
#define INODE_WIND_TYPE  (0xB4)    //风速风向传感器节点	0xB4

#define USER_COLLECTION  'C'
#define  USER_CONTROL  'K'



#pragma pack(1)

typedef struct {

	byte header;
	byte num;
	byte length;
	byte cmd;
	byte payload[20];//数据	校验	帧尾
	byte theend;
}PKT,*PPKT;

#pragma pack()

// MySerial 对话框
class CGreenHouseDlg;
class MySerial : public CDialogEx
{
	DECLARE_DYNAMIC(MySerial)

public:
	MySerial(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~MySerial();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonStart();
	afx_msg void OnBnClickedButtonStart2();
	CComboBox m_cb_sel;
	CComboBox m_cb_bund;
	CButton m_btn_open;
	CButton m_btn_ok;

	bool m_open;//串口是否打开
	int m_bund;//波特率设置
	CString m_com_name;
	byte    m_com_index;
	
	int      m_tm_id;
	bool     m_send_flag;
	CString  m_tmoutinf;
	CSerialPort m_com;
	CGreenHouseDlg *parent;
	afx_msg void OnCbnSelchangeComboSerial();
	afx_msg void OnCbnSelendcancelComboBaudRate();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual BOOL OnInitDialog();
	LONG OnComm(WPARAM ch,LPARAM port);
	void handerdatapkt(PKT * pkt);
	bool serialsenddata(byte * p,int len);
	bool serialsenddata(byte * p,int len,bool ischk= false ,CString inf="通讯超时",DWORD ms = 3000);
	VOID MakeCMDPKT(PKT *pkt,byte cmd, bool iscontrl,byte  *payload,byte paylen);
	bool send_cmd_whole_start_run(void);
};
