// Winddlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "GreenHouse.h"
#include "Winddlg.h"
#include "afxdialogex.h"
#include <math.h>
#define  PI  3.1415926535
// Winddlg �Ի���

IMPLEMENT_DYNAMIC(Winddlg, CDialogEx)

Winddlg::Winddlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Winddlg::IDD, pParent)
	, m_ptOrigin (0)
	, m_num(0)
{

}

Winddlg::~Winddlg()
{
}

void Winddlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Winddlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// Winddlg ��Ϣ�������


BOOL Winddlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CRect   temprect(0,0,255,228);
	
	CWnd::SetWindowPos(NULL,0,0,temprect.Width()+6,temprect.Height()+28,SWP_NOZORDER|SWP_NOMOVE);
	//CRect rt;
	//GetClientRect(&rt);
	//SetTimer(123,50,NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
void Winddlg::DrawBmp(CString name)
{
	CString dstname;

	
	if (name== "")return;

	dstname =  name; 
	HBITMAP hbmp = (HBITMAP)::LoadImage(AfxGetInstanceHandle(),
		dstname, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION|LR_LOADFROMFILE); 
	if (!hbmp)return;
	CBitmap bitmap;
	bitmap.Attach(hbmp); //����λͼ����  
	CDC *pDC = GetDC();
	CDC memdc;
	memdc.CreateCompatibleDC(pDC);
	memdc.SelectObject(&bitmap);
	BITMAP bmp;

	bitmap.GetBitmap(&bmp);
	CRect bmpRC;
	this->GetWindowRect(&bmpRC);
	::SetBrushOrgEx(::GetDC(this->GetSafeHwnd()),0,0,NULL);
	pDC->SetStretchBltMode(HALFTONE);
	//pDC->StretchBlt(0,0,bmpRC.Width(),bmpRC.Height(),&memdc,0,0,bmp.bmWidth,bmp.bmHeight,SRCCOPY);
	pDC->StretchBlt(0,0,bmp.bmWidth,bmp.bmHeight,&memdc,0,0,bmp.bmWidth,bmp.bmHeight,SRCCOPY);
	//pDC->BitBlt(0,0,bmp.bmWidth,bmp.bmHeight,&memdc,0,0,SRCCOPY); //��ʾ

	bitmap.DeleteObject();
	ReleaseDC(pDC);
	memdc.DeleteDC();
} 

void Winddlg::OnPaint()
{
	
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
	DrawWindPic(m_num);

}
void Winddlg::DrawCenterCircle(CPoint  point)
{
	CClientDC dc(this);
	CPen pen(PS_SOLID,2,RGB(255,0,0));
	dc.SelectObject(&pen);
	CBrush *pBrush=new CBrush(RGB(0,225,0));
	dc.SelectObject(pBrush);
	dc.Ellipse(point.x-10,point.y-10,point.x+10,point.y+10);
}
void Winddlg::DrawLine(CPoint  point,CPoint newpoint)
{
	m_ptOrigin.x =point.x;
	m_ptOrigin.y =point.y;
	CPen pen(PS_SOLID,4,RGB(255,0,0));    //���廭��
	CClientDC dc(this);        //����
	CPen *pOldPen=dc.SelectObject(&pen);
	dc.MoveTo(m_ptOrigin);
	dc.LineTo(newpoint);
	dc.SelectObject(pOldPen);
}
void Winddlg::DrawNewLine(DWORD num)
{
	CPoint p1;
	CPoint p2(120,117);
	p1.x = sin(((double)num *360 /1600 + 180) * PI/180)*85 + p2.x ;
	p1.y = cos(((double)num *360 /1600 + 180) * PI/180)*85 + p2.y ;
	DrawLine( p2, p1);
}
void Winddlg::DrawWindPic(DWORD num)
{
	if (num >= 1600)
	{
		num = 0;
	}
	m_num = num;
	CPoint point(120,117);
	DrawBmp("fengsu3.bmp");
	DrawCenterCircle(point);
	DrawNewLine(num);
}

void Winddlg::OnTimer(UINT_PTR nIDEvent)
{
	static int num =0;
	
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (nIDEvent == 123)
	{	
		if (num++ >=1600)
		{
			num =0;
		}
		DrawWindPic( num++);
	}
	CDialogEx::OnTimer(nIDEvent);
}
