#pragma once
#include "chart\chartcursor.h"
#include "chart\ChartCtrl.h"
#define  MESSAGE_UPDATEPOS WM_USER + 1
class CCustomCursorListener :public CChartCursorListener
{

public:
	CCustomCursorListener(void);
	~CCustomCursorListener(void);
	double m_xavl;
	double m_yavl;
	CString m_str;
	void OnCursorMoved(CChartCursor *pCursor, double xValue, double yValue)  
	{  
		CString str;
		m_xavl = xValue;  
		m_yavl = yValue;  
		COleDateTime ts( CChartCtrl::ValueToDate( m_xavl));
		m_str =ts.Format("%m-%d %H:%M:%S");
		str.Format(" %.2f",m_yavl);
		m_str += str;
		//m_str.Format("%.2f %.2f",m_xavl,m_yavl);
		SendMessage(m_hwnd,MESSAGE_UPDATEPOS,(WPARAM)(m_str.GetBuffer()),0);  
		// Do something with the string...  
	}  
	void GetHwnd(HWND hwnd)  
	{  
		m_hwnd = hwnd;  
	}  
	HWND m_hwnd;  
};
