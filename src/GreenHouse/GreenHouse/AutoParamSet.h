#pragma once
#include "afxwin.h"


// AutoParamSet 对话框

class AutoParamSet : public CDialogEx
{
	DECLARE_DYNAMIC(AutoParamSet)

public:
	AutoParamSet(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~AutoParamSet();

// 对话框数据
	enum { IDD = IDD_DIALOG_PARAM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_editLight;
	CEdit m_editSoil;
	CEdit m_editTemp;
	CEdit m_editHum;
	void * m_parent;
	afx_msg void OnBnClickedOk();
};
