// AutoParamSet.cpp : 实现文件
//

#include "stdafx.h"
#include "GreenHouse.h"
#include "AutoParamSet.h"
#include "afxdialogex.h"
#include "GreenHouseDlg.h"


// AutoParamSet 对话框

IMPLEMENT_DYNAMIC(AutoParamSet, CDialogEx)

AutoParamSet::AutoParamSet(CWnd* pParent /*=NULL*/)
	: CDialogEx(AutoParamSet::IDD, pParent)
{
	m_parent = (void *)pParent;
}

AutoParamSet::~AutoParamSet()
{
}

void AutoParamSet::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_LIGHT, m_editLight);
	DDX_Control(pDX, IDC_EDIT_SOIL, m_editSoil);
	DDX_Control(pDX, IDC_EDIT_TEMP, m_editTemp);
	DDX_Control(pDX, IDC_EDIT_HUM, m_editHum);
}


BEGIN_MESSAGE_MAP(AutoParamSet, CDialogEx)
	ON_BN_CLICKED(IDOK, &AutoParamSet::OnBnClickedOk)
END_MESSAGE_MAP()


// AutoParamSet 消息处理程序


void AutoParamSet::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CGreenHouseDlg * parent = (CGreenHouseDlg *) m_parent;
	CString str = "";

	m_editLight.GetWindowTextA(str);
	if (str == "")
	{
		MessageBox("光照参数不能为空！");
		return;
	}
	parent->m_AutoCtrlLight = atof(str.GetBuffer());

	m_editSoil.GetWindowTextA(str);
	if (str == "")
	{
		MessageBox("土壤湿度参数不能为空！");
		return;
	}
	parent->m_AutoCtrlSoilHum = atof(str.GetBuffer());

	m_editTemp.GetWindowTextA(str);
	if (str == "")
	{
		MessageBox("大棚温度参数不能为空！");
		return;
	}
	parent->m_AutoCtrlTemp = atof(str.GetBuffer());

	m_editHum.GetWindowTextA(str);
	if (str == "")
	{
		MessageBox("大棚湿度参数不能为空！");
		return;
	}
	parent->m_AutoCtrlHum = atof(str.GetBuffer());
	CDialogEx::OnOK();
}
