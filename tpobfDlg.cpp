
// tpobfDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "tpobf.h"
#include "tpobfDlg.h"
#include "afxdialogex.h"
#include <typeinfo>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif



CtpobfDlg::CtpobfDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TPOBF_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CtpobfDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CtpobfDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_ERASEBKGND()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CtpobfDlg 消息处理程序

BOOL CtpobfDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	LoadPictures();
	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}



// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CtpobfDlg::OnPaint()
{
	CPaintDC dc(this); // 用于绘制的设备上下文

	CRect a(0, 0, 350, 350);
	Sleep(25);
	InvalidateRect(&a,0);  //0背景不重画  1背景重画  BOOLEAN值
	CMemoryDC* pDC = &m_dcBack;
	dc.BitBlt(0, 0, pDC->GetWidth(), pDC->GetHeight(), pDC, 0, 0, SRCCOPY);
	pDC = m_dcFlys + m_nIndex++;
	m_nIndex %= FLYS_COUNT;
	pDC->BitTrans(m_pos.x, m_pos.y, pDC->GetWidth(), pDC->GetHeight(), &dc, 0, 0, 0xFF00FF);

	/***************************************************************************************************/


	/****************************************************************************************************/
	CRgn rgn1;
	rgn1.CreateEllipticRgn(500, 500, 1000, 1000);//创建一个圆形区域
	CRgn rgn2;
	rgn2.CreateRectRgn(525, 575, 1000, 600);//创建一个矩形区域
	//区域运算
	rgn1.CombineRgn(&rgn1, &rgn2, RGN_DIFF);//两个区域进行逻辑运算


	//绘制区域
	//CClientDC dc(this);

	CBrush brush1/*(HS_DIAGCROSS, RGB(100, 100, 100))*/;
	dc.FillRgn(&rgn1, &brush1);//填充绘制
	CBrush brush2(RGB(0, 0, 255));
	dc.FrameRgn(&rgn1, &brush2, 2, 2);//边框绘制
	//释放资源
	rgn1.DeleteObject();
	rgn2.DeleteObject();
	brush1.DeleteObject();
	brush2.DeleteObject();
	/****************************************************************************************************/

	//Sleep(25);
	////Invalidate();
	//RedrawWindow();

	/****************************************************************************************************/
	Sleep(30);

}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CtpobfDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



BOOL CtpobfDlg::LoadPictures()
{
	int cx = GetSystemMetrics(SM_CXSCREEN);
	int cy = GetSystemMetrics(SM_CYSCREEN);
	MoveWindow(0, 0, cx, cy, true);
	m_pos.x = rand() % cx;
	m_pos.y = rand() % cy;

	m_dcBack.Create(cx, cy);
	CMemoryDC mdc;
	if (!mdc.LoadBitmap(_T("./Flys/Back.bmp")))
		return FALSE;
	m_dcBack.StretchBlt(0, 0, cx, cy, &mdc, 0, 0, mdc.GetWidth(), mdc.GetHeight(), SRCCOPY);
	int i = -1;
	CString str;
	while (++i < FLYS_COUNT)
	{
		str.Format(_T("./Flys/%03d.bmp"), i + 1);
		if (!m_dcFlys[i].LoadBitmap(str))
			return FALSE;
		m_dcFlys[i].MakeRgn(m_rs[i], 0xFF00FF);
	}
	return TRUE;
}


//
//void CtpobfDlg::OnTimer(UINT_PTR nIDEvent)
//{
//	// TODO: 在此添加消息处理程序代码和/或调用默认值
//
//	CDialogEx::OnTimer(nIDEvent);
//}
//BOOL CtpobfDlg::OnEraseBkgnd(CDC* pDC)
//{
//	// TODO: 在此添加消息处理程序代码和/或调用默认值
//
//	/*return CDialogEx::OnEraseBkgnd(pDC);*/
//	return FALSE;
//}