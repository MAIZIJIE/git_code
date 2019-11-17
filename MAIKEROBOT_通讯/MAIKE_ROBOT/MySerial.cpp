
#include "StdAfx.h"
#include "MySerial.h"
//#include <TCHAR.H>
//#include <windows.h>


HANDLE hCom;

/**
  open serial 
  @param COMx: eg:_T("COM1")
  @param BaudRate:
  return 0 success ,return Negative is haed err 
*/
CSerial::CSerial()
{
}

CSerial::~CSerial()
{
}

int  CSerial::Serial_open(LPCSTR COMx,int BaudRate)
{
	DCB dcb={0};
	hCom =CreateFile(COMx,
		GENERIC_READ|GENERIC_WRITE, 
		0,
		0,
		OPEN_EXISTING,
		0,//FILE_FLAG_OVERLAPPED,	//ͬ����ʽ �� �ص���ʽ
		0
		);

	if(hCom ==INVALID_HANDLE_VALUE)
	{
		DWORD dwError=GetLastError();
		//printf("Sorry, failed to open the serial\n");
		return -1;
	}

	dcb.DCBlength = sizeof(DCB);

	if(!GetCommState(hCom,&dcb))
	{
		DWORD dwError=GetLastError();
		return -1;
	}

	dcb.BaudRate = BaudRate;	//������
	dcb.ByteSize = 8;			//λ��
	dcb.Parity = NOPARITY;		//��ż����
	dcb.StopBits =ONESTOPBIT;	//ֹͣλ��

	if(!SetCommState(hCom,&dcb))
	{
		DWORD dwError=GetLastError();
		return -1;
	}
	if( !PurgeComm( hCom, PURGE_RXCLEAR ) )    return -1;

	SetupComm(hCom,1024,1024);
	return 0;
}

/**
  serial read
  @param Buf:data buf
  @param size:
  @return The len of read
*/
int CSerial::Serial_read(void *OutBuf,int size)
{
	DWORD cnt=0;
	ReadFile(hCom,OutBuf,size,&cnt,0);
	return cnt;

}

/**
  serial write
  @param Buf:data buf
  @param size:bytes of Buf
  @return The len of writen
*/
int CSerial::Serial_write(const void *Buf,int size)
{
	DWORD dw;
	WriteFile(hCom,Buf,size,&dw,NULL);
	return dw;
}

/**
  serial close
*/
void CSerial::Serial_close(void)
{
	CloseHandle(hCom);
}
