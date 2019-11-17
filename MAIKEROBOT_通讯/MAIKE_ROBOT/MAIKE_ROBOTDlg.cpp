
// MAIKE_ROBOTDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MAIKE_ROBOT.h"
#include "MAIKE_ROBOTDlg.h"
#include "afxdialogex.h"
#include "MySerial.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CSerial My_Serial;//����ͨ����
unsigned char RECEIVE_BUF[20];
unsigned char WRITE_BUF[19];
int jishu=0;
unsigned char READ_BUF[40];
static int jishu_j=0;
// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CMAIKE_ROBOTDlg �Ի���



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


// CMAIKE_ROBOTDlg ��Ϣ�������

BOOL CMAIKE_ROBOTDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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




	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE



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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMAIKE_ROBOTDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMAIKE_ROBOTDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMAIKE_ROBOTDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CDialogEx::OnTimer(nIDEvent);
	CString strtemp;
	int i;
	CString strtemp_kongge = _T(" "); //����

		//m_Serial.Serial_open(_T("COM3"),115200);//_T("COM2")�ǽ�LPCWSTR�͵�ʵ��ת��ΪLPCSTR�͵��β�
	WRITE_BUF[0] = 0X55;
	WRITE_BUF[1] = 0XAA;
	WRITE_BUF[2] = jishu;
	WRITE_BUF[3] = 0x00;
	WRITE_BUF[4] = 0x00;
	WRITE_BUF[17] = 0XAB;
	WRITE_BUF[18] = 0X56;


	My_Serial.Serial_write(&WRITE_BUF,19); //������
	
	My_Serial.Serial_read(&READ_BUF,40);//��ȡ40���ֽڵ�����

    m_READ_COM = "���ݣ�";
      for (i=0;i<20;i++)
		{
			
			if(READ_BUF[i]==0X55 && READ_BUF[i+19]==0XAA)
		{

		  for (jishu_j=0;jishu_j<20;jishu_j++)
			{

          RECEIVE_BUF[jishu_j] = READ_BUF[i+jishu_j]; //��ֵΪ RECEIVE_BUF

		  strtemp.Format(_T("%x"), RECEIVE_BUF[jishu_j]);
		  m_READ_COM += strtemp;

		  m_READ_COM += strtemp_kongge;
		  }

		  READ_BUF[i+jishu_j]=0;

		  }
	   }

		UpdateData(false); //���±༭������}
		jishu++;
}




void CMAIKE_ROBOTDlg::OnBnClickedOpenCom()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	My_Serial.Serial_open(_T("COM3"),115200);//_T("COM2")�ǽ�LPCWSTR�͵�ʵ��ת��ΪLPCSTR�͵��β�
	SetTimer(1,10,NULL); //������ʱ��
}


void CMAIKE_ROBOTDlg::OnBnClickedClosedCom()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	My_Serial.Serial_close();
}
