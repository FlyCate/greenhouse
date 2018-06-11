#pragma once
#include "chart/ChartCtrl.h"
#include "chart/ChartLineSerie.h"
#include "CustomCursorListener.h"
// wavectrl 对话框
#define  D_BUF_SIZE (100)
class wavectrl : public CDialogEx
{
	DECLARE_DYNAMIC(wavectrl)

public:
	wavectrl(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~wavectrl();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };
	//CChartCtrl m_ChartCtrl1;  

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持


	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnMove(int x, int y);
	afx_msg void OnPaint();

	CChartCtrl m_ChartCtrl;  
	CChartLineSerie *m_pLineSerie;
	void InitChartCtrl();
	void CreateWavePic();
	bool m_dynamic; //动态数据
	bool m_pan;
	bool m_zoom;
	bool m_Legend;
	bool m_Leftgrid;
	bool m_bottomgrid;
	CString m_mainname;
	CString m_xname;
	CString m_yname;
	double m_leftmin;//左侧周的最小值
	double m_leftmax;//左侧周的最大值

	double m_d_X_buf[D_BUF_SIZE];
	double m_d_Y_buf[D_BUF_SIZE];
	int m_d_count;
	double *m_s_X_buf;
	double *m_s_Y_buf;
	CChartDateTimeAxis* m_pDateAxis;
	CCustomCursorListener  *m_pCursorListener ;  
	CChartCrossHairCursor *m_CrossHairCursor;

	

	 void SetPanCtrl(bool flag=true);
	 void SetLegendCtrl(bool flag=true);
	 void SetZoomCtrl(bool flag);

	 //void Setmianname( CString str);
	 //void SetXname( CString str);
	 //void SetYname( CString str);
	 //void Setleftmin( float val);
	// void Setleftmax( float val);
	 void SetleftMaxAndMin( double min,double max);
	 void SetLeftGridCtrl(bool flag);
	 void SetBottomGridCtrl(bool flag);
	 void CreateBaseChartCtrl();
	 void ClearAllSeries();
	 void Refresh();
	 void LeftMoveArray(double* ptr,size_t length,double data) ; 
	 void DrawLineDyncChart(double xval,double yval)  ;
	 void DrawLineStaticChart(double *xval,double *yval ,int len)  ;
	 void SetXYtittle(CString xname,CString yname,CString mainname);
	 afx_msg LRESULT OnUpdateData(WPARAM wp,LPARAM lp);  
	 void SetCrosskCtrl(bool  flag);
	
};
