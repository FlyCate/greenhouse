#pragma once
#include "afxcmn.h"
#include "SQLCtl.h"

// CHisForm 对话框

class CHisForm : public CDialogEx
{
	DECLARE_DYNAMIC(CHisForm)

public:
	CHisForm(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CHisForm();

// 对话框数据
	enum { IDD = IDD_DIALOG_HIS_FORM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
private:
	void * m_parant;
public:
	CListCtrl m_list;
	afx_msg void OnPaint();

public:
	void SetFormValue(pSelectInfo info);
};
