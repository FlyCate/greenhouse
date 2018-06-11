#pragma once


// Winddlg 对话框

class Winddlg : public CDialogEx
{
	DECLARE_DYNAMIC(Winddlg)

public:
	Winddlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Winddlg();

// 对话框数据
	enum { IDD = IDD_DLG_WIND };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	void DrawBmp(CString name);
	afx_msg void OnPaint();
	void DrawCenterCircle(CPoint  point);
	void DrawLine(CPoint  point,CPoint newpoint);
	CPoint m_ptOrigin;
	void DrawNewLine(DWORD num);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	int m_num;
public:

	void DrawWindPic(DWORD num);//画实时风向图
};
