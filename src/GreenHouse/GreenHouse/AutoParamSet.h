#pragma once
#include "afxwin.h"


// AutoParamSet �Ի���

class AutoParamSet : public CDialogEx
{
	DECLARE_DYNAMIC(AutoParamSet)

public:
	AutoParamSet(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~AutoParamSet();

// �Ի�������
	enum { IDD = IDD_DIALOG_PARAM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_editLight;
	CEdit m_editSoil;
	CEdit m_editTemp;
	CEdit m_editHum;
	void * m_parent;
	afx_msg void OnBnClickedOk();
};
