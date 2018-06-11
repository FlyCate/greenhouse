
// GreenHouseDlg.h : 头文件
//

#pragma once

#include "MySerial.h"
#include "SQLCtl.h"
#include "afxwin.h"
#include "afxdtctl.h"
#include "HisForm.h"
#include "WaveForm.h"
#include "Winddlg.h"
// CGreenHouseDlg 对话框
class CGreenHouseDlg : public CDialogEx
{
// 构造
public:
	CGreenHouseDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_GREENHOUSE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

private:
	MySerial * m_serial;
	CHisForm * m_hisForm;
	CSQLCtl * m_mySQL;
	WaveForm  * m_wavedlg;
	int m_radioVal;
	CString m_startTime;
	CString m_endTime;
	BOOL    m_getTime;
	Winddlg *m_winddlg;
public:
	afx_msg void OnBnClickedButtonSerial();
	afx_msg void OnBnClickedButtonFan1();
	afx_msg void OnBnClickedButtonFan2();
	afx_msg void OnBnClickedButtonElectricMachinery1();
	afx_msg void OnBnClickedButtonElectricMachinery2();
	afx_msg void OnBnClickedButtonWaterPump1();
	afx_msg void OnBnClickedButtonWaterPump2();
	afx_msg void OnBnClickedButtonWaterPump3();
	afx_msg void OnBnClickedRadioRealtime();
	CComboBox m_type;
	afx_msg void OnBnClickedButtonSearch();
	CDateTimeCtrl m_startDate;
	CDateTimeCtrl m_endDate;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMove(int x, int y);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnBnClickedCheckTime();
	void RemoveChildwnd();
	afx_msg void OnBnClickedButtonStartCap();
	afx_msg void OnBnClickedButtonElectricMachinery3();

	int GetShowType() { return m_radioVal; }  //0 时实曲线图 1 历史曲线图 2 历史表格
	void InitWaveForm(int type);		//初始化曲线图
	void SendButtonSerialData(int type);		//发送按钮串口数据
	void SendSensorSerialData(int i);
	void ComboBoxInit(int type);
	void AutoCtrl(int type, float value);	//自动控制 0光照 1土壤湿度 2大棚温度 3大棚湿度
	afx_msg LRESULT OnUserPostMsg(WPARAM wParam, LPARAM lParam);

public:
	//状态机
	BOOL m_Light;	//照明控制
	BOOL m_Fan1;	//排风风机1
	BOOL m_Fan2;	//排风风机2
	BOOL m_Fan3;	//轴流风机1
	BOOL m_Fan4;	//轴流风机2
	BOOL m_ElectricMachinery1;	//天窗
	BOOL m_ElectricMachinery2;	//遮阳罩
	BOOL m_ElectricMachinery3;	//保温帘
	BOOL m_WaterPump1;	//灌溉
	BOOL m_WaterPump2;	//水帘
	BOOL m_WaterPump3;	//加热
	BOOL m_CapStatus;	//采集
	BOOL m_AutoCtrlStatus; //自动控制
	float  m_AutoCtrlLight;
	float  m_AutoCtrlSoilHum;
	float  m_AutoCtrlTemp;
	float  m_AutoCtrlHum;
	unsigned int m_ComboStatus;	//下拉框的状态
public:
	afx_msg void OnCbnSelchangeComboType();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButtonLight();
	afx_msg void OnBnClickedButtonFan3();
	afx_msg void OnBnClickedButtonFan4();
	afx_msg void OnBnClickedButtonAutoCtl();
};
