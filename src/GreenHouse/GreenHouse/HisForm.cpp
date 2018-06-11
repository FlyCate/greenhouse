// HisForm.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "GreenHouse.h"
#include "HisForm.h"
#include "afxdialogex.h"
#include "GreenHouseDlg.h"


// CHisForm �Ի���

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


// CHisForm ��Ϣ�������

BOOL CHisForm::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	LONG lStyle; 
	lStyle = GetWindowLong(m_list.m_hWnd, GWL_STYLE);// ��ȡ��ǰ����style 
	lStyle &= ~LVS_TYPEMASK; // �����ʾ��ʽλ 
	lStyle |= LVS_REPORT; // ����style 
	SetWindowLong(m_list.m_hWnd, GWL_STYLE, lStyle);// ����style 
	DWORD dwStyle = m_list.GetExtendedStyle(); 
	dwStyle |= LVS_EX_FULLROWSELECT;// ѡ��ĳ��ʹ���и�����ֻ������report ����listctrl �� 
	dwStyle |= LVS_EX_GRIDLINES;// �����ߣ�ֻ������report ����listctrl �� 
	//dwStyle |= LVS_EX_CHECKBOXES;//item ǰ����checkbox �ؼ� 

	m_list.SetExtendedStyle(dwStyle); // ������չ��� 

	RECT rect;
	GetClientRect(&rect);
	int width = rect.right - rect.left;
	m_list.InsertColumn( 0, "ʱ��", LVCFMT_CENTER, width/3 );// ������ 
	m_list.InsertColumn( 1, "����������", LVCFMT_CENTER, width*2/3 );

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CHisForm::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
	RECT rect;
	GetClientRect(&rect);
	m_list.MoveWindow(&rect);

	int width = rect.right - rect.left;
	m_list.SetColumnWidth( 0, width/3 );// ������ 
	m_list.SetColumnWidth( 1, width*2/3 - 4);
}

void CHisForm::SetFormValue(pSelectInfo info)
{
	m_list.DeleteAllItems();
	for (vector<BaseInfo>::iterator iter = info->infoList.begin(); iter != info->infoList.end(); iter++)
	{
		int nRow = m_list.InsertItem(0, iter->time.GetBuffer());// ������
		m_list.SetItemText(nRow, 1, iter->info.GetBuffer());// ��������������
	}
}