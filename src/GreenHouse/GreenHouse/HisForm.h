#pragma once
#include "afxcmn.h"
#include "SQLCtl.h"

// CHisForm �Ի���

class CHisForm : public CDialogEx
{
	DECLARE_DYNAMIC(CHisForm)

public:
	CHisForm(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CHisForm();

// �Ի�������
	enum { IDD = IDD_DIALOG_HIS_FORM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
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
