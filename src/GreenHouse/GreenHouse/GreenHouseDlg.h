
// GreenHouseDlg.h : ͷ�ļ�
//

#pragma once

#include "MySerial.h"
#include "SQLCtl.h"
#include "afxwin.h"
#include "afxdtctl.h"
#include "HisForm.h"
#include "WaveForm.h"
#include "Winddlg.h"
// CGreenHouseDlg �Ի���
class CGreenHouseDlg : public CDialogEx
{
// ����
public:
	CGreenHouseDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_GREENHOUSE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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

	int GetShowType() { return m_radioVal; }  //0 ʱʵ����ͼ 1 ��ʷ����ͼ 2 ��ʷ���
	void InitWaveForm(int type);		//��ʼ������ͼ
	void SendButtonSerialData(int type);		//���Ͱ�ť��������
	void SendSensorSerialData(int i);
	void ComboBoxInit(int type);
	void AutoCtrl(int type, float value);	//�Զ����� 0���� 1����ʪ�� 2�����¶� 3����ʪ��
	afx_msg LRESULT OnUserPostMsg(WPARAM wParam, LPARAM lParam);

public:
	//״̬��
	BOOL m_Light;	//��������
	BOOL m_Fan1;	//�ŷ���1
	BOOL m_Fan2;	//�ŷ���2
	BOOL m_Fan3;	//�������1
	BOOL m_Fan4;	//�������2
	BOOL m_ElectricMachinery1;	//�촰
	BOOL m_ElectricMachinery2;	//������
	BOOL m_ElectricMachinery3;	//������
	BOOL m_WaterPump1;	//���
	BOOL m_WaterPump2;	//ˮ��
	BOOL m_WaterPump3;	//����
	BOOL m_CapStatus;	//�ɼ�
	BOOL m_AutoCtrlStatus; //�Զ�����
	float  m_AutoCtrlLight;
	float  m_AutoCtrlSoilHum;
	float  m_AutoCtrlTemp;
	float  m_AutoCtrlHum;
	unsigned int m_ComboStatus;	//�������״̬
public:
	afx_msg void OnCbnSelchangeComboType();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButtonLight();
	afx_msg void OnBnClickedButtonFan3();
	afx_msg void OnBnClickedButtonFan4();
	afx_msg void OnBnClickedButtonAutoCtl();
};
