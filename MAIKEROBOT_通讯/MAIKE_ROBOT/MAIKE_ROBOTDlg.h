
// MAIKE_ROBOTDlg.h : ͷ�ļ�
//

#pragma once


// CMAIKE_ROBOTDlg �Ի���
class CMAIKE_ROBOTDlg : public CDialogEx
{
// ����
public:
	CMAIKE_ROBOTDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MAIKE_ROBOT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString m_READ_COM;
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	afx_msg void OnBnClickedOpenCom();
	afx_msg void OnBnClickedClosedCom();
};
