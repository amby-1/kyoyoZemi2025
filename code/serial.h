//=============================================================================//
/*!
*	@file Serial.h
*	@brief Serial�ʐM�p�̃N���X(�錾)Qt(Unicode compatible)�p
*	@author k.kon (revised by amby
*	@date 2011/8/10�쐬
*	@attention windows���K�{
*
*        //! �V���A���ʐM���s�����߂̃N���X
*        //�@�@UNICODE�ɂ��Ή����邽�߁CTCHAR�^�ň������Ƃɂ���
*/
//=============================================================================//


#pragma once

#include <iostream>
#include <windows.h>
#include <tchar.h>

#ifndef  SERIAL_H
#define SERIAL_H

//! class CSerial:this class controll the Serial Communication
class CSerial{

public:
	CSerial();
	virtual ~CSerial();
	bool InitSerial(TCHAR *comport, int baudrate);
	bool CloseSerial(void);
	bool fputc(BYTE data,bool view_enable = false);
	bool fput(unsigned char* data, int size, bool view_enable = false);
	BYTE fgetc(bool view_enable = false);
	DWORD fget(unsigned char* data, int size, bool view_enable = false);
	DWORD CheckSerialData(void);
	void ClearRXbuffer(void);
	bool kbhit(void);
	bool isOpen(void);

protected:
	HANDLE hCom;
	DCB dcb;
	BOOL fRetVal ;
	BYTE bSet ;
	COMMTIMEOUTS ctmo;
private:
	bool connectFlag;

};

#endif
//SERIAL_H
