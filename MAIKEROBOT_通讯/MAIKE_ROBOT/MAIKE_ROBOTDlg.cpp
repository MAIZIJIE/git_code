
// MAIKE_ROBOTDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MAIKE_ROBOT.h"
#include "MAIKE_ROBOTDlg.h"
#include "afxdialogex.h"
#include "MySerial.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CSerial My_Serial;//串口通信类
unsigned char RECEIVE_BUF[20];
unsigned char WRITE_BUF[19];
int jishu=0;
unsigned char READ_BUF[40];
static int jishu_j=0;
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMAIKE_ROBOTDlg 对话框



CMAIKE_ROBOTDlg::CMAIKE_ROBOTDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMAIKE_ROBOTDlg::IDD, pParent)
	, m_READ_COM(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMAIKE_ROBOTDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_READ_COM, m_READ_COM);
}

BEGIN_MESSAGE_MAP(CMAIKE_ROBOTDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()

	ON_BN_CLICKED(IDC_OPEN_COM, &CMAIKE_ROBOTDlg::OnBnClickedOpenCom)
	ON_BN_CLICKED(IDC_CLOSED_COM, &CMAIKE_ROBOTDlg::OnBnClickedClosedCom)
END_MESSAGE_MAP()


// CMAIKE_ROBOTDlg 消息处理程序

BOOL CMAIKE_ROBOTDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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




	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE



}

void CMAIKE_ROBOTDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMAIKE_ROBOTDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMAIKE_ROBOTDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMAIKE_ROBOTDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialogEx::OnTimer(nIDEvent);
	CString strtemp;
	int i;
	CString strtemp_kongge = _T(" "); //换行

		//m_Serial.Serial_open(_T("COM3"),115200);//_T("COM2")是将LPCWSTR型的实参转化为LPCSTR型的形参
	WRITE_BUF[0] = 0X55;
	WRITE_BUF[1] = 0XAA;
	WRITE_BUF[2] = jishu;
	WRITE_BUF[3] = 0x00;
	WRITE_BUF[4] = 0x00;
	WRITE_BUF[17] = 0XAB;
	WRITE_BUF[18] = 0X56;


	My_Serial.Serial_write(&WRITE_BUF,19); //发数据
	
	My_Serial.Serial_read(&READ_BUF,40);//读取40个字节的数据

    m_READ_COM = "数据：";
      for (i=0;i<20;i++)
		{
			
			if(READ_BUF[i]==0X55 && READ_BUF[i+19]==0XAA)
		{

		  for (jishu_j=0;jishu_j<20;jishu_j++)
			{

          RECEIVE_BUF[jishu_j] = READ_BUF[i+jishu_j]; //赋值为 RECEIVE_BUF

		  strtemp.Format(_T("%x"), RECEIVE_BUF[jishu_j]);
		  m_READ_COM += strtemp;

		  m_READ_COM += strtemp_kongge;
		  }

		  READ_BUF[i+jishu_j]=0;

		  }
	   }

		UpdateData(false); //更新编辑框内容}
		jishu++;
}




void CMAIKE_ROBOTDlg::OnBnClickedOpenCom()
{
	// TODO: 在此添加控件通知处理程序代码
	My_Serial.Serial_open(_T("COM3"),115200);//_T("COM2")是将LPCWSTR型的实参转化为LPCSTR型的形参
	SetTimer(1,10,NULL); //开启定时器
}


void CMAIKE_ROBOTDlg::OnBnClickedClosedCom()
{
	// TODO: 在此添加控件通知处理程序代码
	My_Serial.Serial_close();
}
