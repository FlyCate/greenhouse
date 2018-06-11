// HisForm.cpp : 实现文件
//

#include "stdafx.h"
#include "GreenHouse.h"
#include "HisForm.h"
#include "afxdialogex.h"
#include "GreenHouseDlg.h"


// CHisForm 对话框

IMPLEMENT_DYNAMIC(CHisForm, CDialogEx)

CHisForm::CHisForm(CWnd* pParent /*=NULL*/)
	: CDialogEx(CHisForm::IDD, pParent)
{
	m_parant = (void *)pParent;
}

CHisForm::~CHisForm()
{
}

void CHisForm::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_HIS_FORM, m_list);
}


BEGIN_MESSAGE_MAP(CHisForm, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CHisForm 消息处理程序

BOOL CHisForm::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO: 在此添加额外的初始化代码

	LONG lStyle; 
	lStyle = GetWindowLong(m_list.m_hWnd, GWL_STYLE);// 获取当前窗口style 
	lStyle &= ~LVS_TYPEMASK; // 清除显示方式位 
	lStyle |= LVS_REPORT; // 设置style 
	SetWindowLong(m_list.m_hWnd, GWL_STYLE, lStyle);// 设置style 
	DWORD dwStyle = m_list.GetExtendedStyle(); 
	dwStyle |= LVS_EX_FULLROWSELECT;// 选中某行使整行高亮（只适用与report 风格的listctrl ） 
	dwStyle |= LVS_EX_GRIDLINES;// 网格线（只适用与report 风格的listctrl ） 
	//dwStyle |= LVS_EX_CHECKBOXES;//item 前生成checkbox 控件 

	m_list.SetExtendedStyle(dwStyle); // 设置扩展风格 

	RECT rect;
	GetClientRect(&rect);
	int width = rect.right - rect.left;
	m_list.InsertColumn( 0, "时间", LVCFMT_CENTER, width/3 );// 插入列 
	m_list.InsertColumn( 1, "传感器数据", LVCFMT_CENTER, width*2/3 );

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CHisForm::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()
	RECT rect;
	GetClientRect(&rect);
	m_list.MoveWindow(&rect);

	int width = rect.right - rect.left;
	m_list.SetColumnWidth( 0, width/3 );// 插入列 
	m_list.SetColumnWidth( 1, width*2/3 - 4);
}

void CHisForm::SetFormValue(pSelectInfo info)
{
	m_list.DeleteAllItems();
	for (vector<BaseInfo>::iterator iter = info->infoList.begin(); iter != info->infoList.end(); iter++)
	{
		int nRow = m_list.InsertItem(0, iter->time.GetBuffer());// 插入行
		m_list.SetItemText(nRow, 1, iter->info.GetBuffer());// 设置其它列数据
	}
}