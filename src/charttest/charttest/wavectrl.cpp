// wavectrl.cpp : 实现文件
//

#include "stdafx.h"
#include "charttest.h"
#include "wavectrl.h"
#include "afxdialogex.h"
//#include  "chart/ChartDateTimeAxis.h"
#include "chart/ChartAxisLabel.h"
#include "chart/ChartCrossHairCursor.h"
// wavectrl 对话框

IMPLEMENT_DYNAMIC(wavectrl, CDialogEx)

wavectrl::wavectrl(CWnd* pParent /*=NULL*/)
	: CDialogEx(wavectrl::IDD, pParent)
	,m_pan(false)
	,m_zoom(false)
	,m_Legend(false)
	,m_Leftgrid(true)
	,m_bottomgrid(true)
	,m_dynamic(true)
	,m_pDateAxis(NULL)
	,m_mainname("温度显示")
	,m_xname("时间")
	,m_yname("采集值")
	,m_leftmin(0)//左侧周的最小值
	,m_leftmax(100)//左侧周的最大值
	,m_d_count(0)
	,m_s_X_buf(NULL)
	,m_s_Y_buf(NULL)
	,m_CrossHairCursor(NULL)
{	

}

wavectrl::~wavectrl()
{
}

void wavectrl::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
  // DDX_Control(pDX, IDC_CUSTOM1, m_ChartCtrl1);  

}


BEGIN_MESSAGE_MAP(wavectrl, CDialogEx)
	ON_WM_MOVE()
	ON_WM_PAINT()
	ON_MESSAGE(MESSAGE_UPDATEPOS,OnUpdateData)  
END_MESSAGE_MAP()


// wavectrl 消息处理程序


BOOL wavectrl::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CRect rt;
	GetClientRect(&rt);
	m_ChartCtrl.Create(this,rt,IDC_CUSTOM2);  
	m_ChartCtrl.ShowWindow(SW_SHOWNORMAL);  
	m_ChartCtrl.MoveWindow(&rt);
	InitChartCtrl();

	//m_ChartCtrl.SetWindowRgn(rt);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
void wavectrl::InitChartCtrl()
{
	CreateBaseChartCtrl();

}
//设置x轴，Y轴显示标题
void wavectrl::SetXYtittle(CString xname,CString yname,CString mainname)
{
	if (xname =="" || yname==""|| mainname=="")
	{
		return;
	}
	m_mainname = mainname;
	m_yname = yname;
	m_xname = xname;
	//设置主标题
	m_ChartCtrl.GetTitle()->RemoveAll(); 
	m_ChartCtrl.GetTitle()->AddString(TChartString(mainname)); 
	//设置坐标轴的标题
	m_ChartCtrl.GetLeftAxis()->GetLabel()->SetText(TChartString(xname));  
	m_ChartCtrl.GetBottomAxis()->GetLabel()->SetText(TChartString(yname));
}
void wavectrl::CreateWavePic()
{
}

void wavectrl::OnMove(int x, int y)
{
	CDialogEx::OnMove(x, y);

	// TODO: 在此处添加消息处理程序代码
	CRect rt;
	GetClientRect(&rt);
	if(IsWindow(m_ChartCtrl.GetSafeHwnd()))
	{
		m_ChartCtrl.MoveWindow(&rt);
		m_ChartCtrl.EnableRefresh(true);
	}
}


void wavectrl::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()

	CRect rt;
	GetClientRect(&rt);
	//CBrush bush(RGB(255,255,0));
	//dc.FillRect(&rt,&bush);
	if(IsWindow(m_ChartCtrl.GetSafeHwnd()))
	{
		m_ChartCtrl.MoveWindow(&rt);
	    m_ChartCtrl.EnableRefresh(true);
	}

}
 void wavectrl::SetPanCtrl(bool flag)
 {
	 m_pan = flag;
	 m_ChartCtrl.SetPanEnabled(flag);
	 m_ChartCtrl.RefreshCtrl();
 }
 void wavectrl::SetLegendCtrl(bool flag)
 {
	 m_Legend =flag;
	 m_ChartCtrl.GetLegend()->SetVisible(flag);
	 m_ChartCtrl.RefreshCtrl();
 }
  void wavectrl::SetZoomCtrl(bool flag)
  {
	 m_zoom =flag;
	 m_ChartCtrl.SetZoomEnabled(flag);	
	 m_ChartCtrl.RefreshCtrl();
  }
  void wavectrl::SetLeftGridCtrl(bool flag)
  {
	  m_Leftgrid =flag;
	  CChartAxis* pAxis = m_ChartCtrl.GetLeftAxis();
	  if (pAxis)
	  { 
		  pAxis->GetGrid()->SetVisible(flag);
	
	  }
  }
  void wavectrl::SetBottomGridCtrl(bool flag)
  {
	  m_bottomgrid =flag;
	  CChartAxis* pAxis = m_ChartCtrl.GetBottomAxis();
	  if (pAxis)
	  { 
		  pAxis->GetGrid()->SetVisible(flag);

	  }
  }
  
  void wavectrl::Refresh( )
  {
	  m_ChartCtrl.RefreshCtrl();
  }
  //void wavectrl::Setmianname( CString str)
  //{
	 //m_mainname = str;
  //}
  //void wavectrl::SetXname( CString str)
  //{
	 // m_xname = str;
  //}
  //void wavectrl::SetYname( CString str)
  //{
	 // m_yname = str;
  //}
  //void wavectrl::Setleftmin( float val)
  //{
	 // m_leftmin= val;
  //}

  //void wavectrl::Setleftmax( float val)
  //{
	 // m_leftmax= val;
  //}

  void wavectrl::SetleftMaxAndMin( double min,double max)
  { 
	  CChartAxis *pAxis;
	  if (min>=max)return;
	  m_leftmax = max;
	  m_leftmin = min;
	  pAxis = m_ChartCtrl.GetLeftAxis();
	  pAxis->SetMinMax(min,max);
	  
  }

   void wavectrl::ClearAllSeries()
   {
		 m_ChartCtrl.RemoveAllSeries();
		 m_d_count =0;
   }
  void wavectrl::CreateBaseChartCtrl()
  {
	 
	  SetPanCtrl(m_pan);
	  SetLegendCtrl(m_zoom);
	  SetZoomCtrl(m_Legend);  
	  //指x轴显示格式 创建时间坐标
	  m_pDateAxis = m_ChartCtrl.CreateDateTimeAxis(CChartCtrl::BottomAxis);  
	  m_pDateAxis->SetAutomatic(true); 
	  m_pDateAxis->GetGrid()->SetColor(RGB(0,255,0));//设置竖直方向格子颜色
	  m_pDateAxis->GetLabel()->SetColor(RGB(255,255,255));//设置文字标题颜色
	  m_pDateAxis->SetTextColor(RGB(255,255,255));//设置刻度标尺的标示颜色
	
	  m_pDateAxis->SetTickLabelFormat(false,_T("%H:%M:%S")); //("%m-%d %H:%M:%S")

	  CChartAxis *pAxis = m_ChartCtrl.CreateStandardAxis(CChartCtrl::LeftAxis);  
	  pAxis->SetAutomatic(true); 
	  pAxis->GetGrid()->SetColor(RGB(0,255,0));
	  pAxis->GetLabel()->SetColor(RGB(255,255,255));
	  pAxis->SetTextColor(RGB(255,255,255));
	  SetLeftGridCtrl(true);
	  SetBottomGridCtrl(true);
	   
	  /*设置主标题，x标题，y轴标题*/
	  SetXYtittle(m_yname,m_xname,m_mainname);
	   /*设置Y轴刻度范围*/
	  SetleftMaxAndMin(m_leftmin,m_leftmax);
	  m_ChartCtrl.ShowMouseCursor(true);
	  m_ChartCtrl.SetBackColor(RGB(0,0,0));//主控件背景色
	  m_ChartCtrl.SetBorderColor(RGB(255,255,255));//x轴，y轴边框颜色
	 // m_ChartCtrl.SetZoomRectColor(RGB(255,255,0));
	  m_ChartCtrl.SetBackGradient (RGB(0,0,0),RGB(128,128,128), gtHorizontal);
	 m_ChartCtrl.GetTitle()->SetColor(RGB(255,255,255));//设置主标题颜色
	 m_pCursorListener = new CCustomCursorListener; 
	 SetCrosskCtrl( false) ;
  }

  /*添加数据向左移动数据buf*/
  void wavectrl::LeftMoveArray(double* ptr,size_t length,double data)  
  {  
	  for (size_t i=1;i<length;++i)  
	  {  
		  ptr[i-1] = ptr[i];  
	  }  
	  ptr[length-1] = data;  
  }  
  /*动态画图*/
  void wavectrl::DrawLineDyncChart(double xval,double yval)  
  {
	    m_d_count++;
		if (m_d_count <= D_BUF_SIZE)
	    {
			m_d_X_buf[m_d_count-1] = xval;
			m_d_Y_buf[m_d_count-1] = yval;
		}else
		{
			LeftMoveArray(m_d_X_buf,D_BUF_SIZE,xval); 
			LeftMoveArray(m_d_Y_buf,D_BUF_SIZE,yval); 
		}
		 m_ChartCtrl.EnableRefresh(false); 
	  	m_ChartCtrl.RemoveAllSeries();//先清空  

	  	m_pLineSerie = m_ChartCtrl.CreateLineSerie();  
	  	m_pLineSerie->SetSeriesOrdering(poNoOrdering);//设置为无序  
		if (m_d_count <= D_BUF_SIZE)
		{
			m_pLineSerie->AddPoints(m_d_X_buf, m_d_Y_buf,m_d_count);  
		}else
	  		m_pLineSerie->AddPoints(m_d_X_buf, m_d_Y_buf,D_BUF_SIZE);  
	  	m_ChartCtrl.EnableRefresh(true); 
  }
  /*绘制静态图形*/
   void wavectrl::DrawLineStaticChart(double *xval,double *yval ,int len)  
   {
	   int i;
	   if (len<=0)
		   return;
	  
	   m_s_X_buf= new double[len];
	   m_s_Y_buf= new double[len];
	   for (i=0;i<len;i++)
	   {
		   m_s_X_buf[i] = xval[i];
		   m_s_Y_buf[i] = yval[i];
		
	   }
	   m_ChartCtrl.EnableRefresh(false); 
	   m_ChartCtrl.RemoveAllSeries();//先清空  
	   m_pLineSerie = m_ChartCtrl.CreateLineSerie(); 
	    CString  xstr,ystr ;
	
	   m_pLineSerie->AddPoints(xval,yval,len);
	   if (m_s_X_buf)
	   {
		   delete[] m_s_X_buf;
	   }
	   if (m_s_Y_buf)
	   {
		   delete[] m_s_Y_buf;
	   }
	 	m_ChartCtrl.EnableRefresh(true); 
   }
   LRESULT wavectrl::OnUpdateData(WPARAM wp,LPARAM lp)  
   {  
	   CString s= (CString)(char*)wp;
	   CStatic* pStatic;  
	   pStatic = (CStatic*)this->GetParent()->GetDlgItem(IDC_STATIC1);
	   pStatic->SetWindowText(s);  
	   
	   return 1;  
   }  

	void wavectrl::SetCrosskCtrl(bool  flag) 
	{
		if (flag == false)
		{
			if (m_CrossHairCursor)
			{
			
				m_ChartCtrl.RemoveCursor(m_CrossHairCursor->GetCursorId() );
					m_CrossHairCursor =NULL;
			}
			return ;
		}
			
		m_CrossHairCursor = m_ChartCtrl.CreateCrossHairCursor (false,false);	
		m_CrossHairCursor->SetColor (RGB(128,128,128));//设置鼠标移动十字线条颜色
		HWND hWnd = this->GetSafeHwnd();  

		m_pCursorListener->GetHwnd(hWnd);      
		m_CrossHairCursor->RegisterListener(m_pCursorListener); 
	}