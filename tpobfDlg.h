
// tpobfDlg.h: 头文件
//

#pragma once

#include "MemoryDC.h"
// CtpobfDlg 对话框
class CtpobfDlg : public CDialogEx
{
// 构造
public:
	CtpobfDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TPOBF_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
	enum { FLYS_COUNT = 7 };
	int m_nIndex = 0;
	CMemoryDC m_dcFlys[FLYS_COUNT];
	CMemoryDC m_dcBack;
	CPoint m_pos;
	CRgn m_rs[FLYS_COUNT];
	BOOL LoadPictures();
public:
	//afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//afx_msg void OnTimer(UINT_PTR nIDEvent);
};
