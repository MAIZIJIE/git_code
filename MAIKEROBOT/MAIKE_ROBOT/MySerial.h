#include <TCHAR.H>
#include <windows.h>
using namespace std;


#ifndef __MYSERIAL_H__
#define __MYSERIAL_H__
class CSerial
{

public:

	CSerial();
	virtual ~CSerial();
	int Serial_open(LPCSTR COMx,int BaudRate);
	int Serial_read(void *OutBuf,int size);
	int Serial_write(const void *Buf,int size);
	void Serial_close(void);


};

#endif __MYSERIAL_H__