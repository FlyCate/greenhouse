#pragma once

#include "chart/ChartCtrl.h"
#include "chart/ChartLineSerie.h"
#include "CustomCursorListener.h"
// wavectrl 对话框
#define  D_BUF_SIZE (100)

// WaveForm 对话框

class WaveForm : public CDialogEx
{
	DECLARE_DYNAMIC(WaveForm)

public:
	WaveForm(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~WaveForm();

// 对话框数据
	enum { IDD = IDD_DLG_WAVE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	void LeftMoveArray(double* ptr,size_t length,double data) ; 
	void CreateBaseChartCtrl();
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
	// 波形控制

	virtual BOOL OnInitDialog();
	afx_msg void OnMove(int x, int y);
	afx_msg void OnPaint();


	void SetPanCtrl(bool flag=true);/*鼠标移动控制*/
	void SetLegendCtrl(bool flag=true);//无用
	void SetZoomCtrl(bool flag);//缩放控制
	void SetCrosskCtrl(bool  flag);//显示十字架标尺
	void SetBottomTickLabelFormat(bool flag);

	void Refresh();//强制刷新

	void SetXYtittle(CString xname,CString yname,CString mainname);//设置x坐标轴，y坐标轴，和主标题 名称
	void DrawLineDyncChart(double xval,double yval)  ;//画动态图
	void DrawLineStaticChart(double *xval,double *yval ,int len) ;//画静态态图
	void ClearAllSeries();//清空所用线条
};
