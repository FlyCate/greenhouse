#pragma once

#include "chart/ChartCtrl.h"
#include "chart/ChartLineSerie.h"
#include "CustomCursorListener.h"
// wavectrl �Ի���
#define  D_BUF_SIZE (100)

// WaveForm �Ի���

class WaveForm : public CDialogEx
{
	DECLARE_DYNAMIC(WaveForm)

public:
	WaveForm(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~WaveForm();

// �Ի�������
	enum { IDD = IDD_DLG_WAVE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	void LeftMoveArray(double* ptr,size_t length,double data) ; 
	void CreateBaseChartCtrl();
	bool m_dynamic; //��̬����
	bool m_pan;
	bool m_zoom;
	bool m_Legend;
	bool m_Leftgrid;
	bool m_bottomgrid;
	CString m_mainname;
	CString m_xname;
	CString m_yname;
	double m_leftmin;//����ܵ���Сֵ
	double m_leftmax;//����ܵ����ֵ

	double m_d_X_buf[D_BUF_SIZE];
	double m_d_Y_buf[D_BUF_SIZE];
	int m_d_count;
	double *m_s_X_buf;
	double *m_s_Y_buf;	

	CChartCtrl m_ChartCtrl;  
	CChartLineSerie *m_pLineSerie;
	CChartDateTimeAxis* m_pDateAxis;
	CCustomCursorListener  *m_pCursorListener ; 
	CChartCrossHairCursor *m_CrossHairCursor;

	void SetleftMaxAndMin( double min,double max);
	void SetLeftGridCtrl(bool flag);
	void SetBottomGridCtrl(bool flag);
	//void Setmianname( CString str);
	//void SetXname( CString str);
	//void SetYname( CString str);
	//void Setleftmin( float val);
	// void Setleftmax( float val);
	DECLARE_MESSAGE_MAP()
	afx_msg LRESULT OnUpdateData(WPARAM wp,LPARAM lp);  
public:
	// ���ο���

	virtual BOOL OnInitDialog();
	afx_msg void OnMove(int x, int y);
	afx_msg void OnPaint();


	void SetPanCtrl(bool flag=true);/*����ƶ�����*/
	void SetLegendCtrl(bool flag=true);//����
	void SetZoomCtrl(bool flag);//���ſ���
	void SetCrosskCtrl(bool  flag);//��ʾʮ�ּܱ��
	void SetBottomTickLabelFormat(bool flag);

	void Refresh();//ǿ��ˢ��

	void SetXYtittle(CString xname,CString yname,CString mainname);//����x�����ᣬy�����ᣬ�������� ����
	void DrawLineDyncChart(double xval,double yval)  ;//����̬ͼ
	void DrawLineStaticChart(double *xval,double *yval ,int len) ;//����̬̬ͼ
	void ClearAllSeries();//�����������
};
