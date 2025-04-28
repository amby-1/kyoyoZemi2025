//=============================================================================//
/*!
*	@file serial.cpp
*	@brief Serial�ʐM�p�̃N���X(����)Qt(Unicode compatible)�p
*	@author k.kon (revised by amby
*	@date 2011/8/10�쐬
*	@attention windows���K�{
*
*        //! �V���A���ʐM���s�����߂̃N���X
*        //�@�@UNICODE�ɂ��Ή����邽�߁CTCHAR�^�ň������Ƃɂ���
*/
//=============================================================================//

#include "Serial.h"

//! Constructor
CSerial::CSerial()
{
	connectFlag = false;
}

//! Destructor
CSerial::~CSerial()
{
}

//! Initialize method ; return isConnect
bool CSerial::InitSerial(TCHAR *comport, int baudrate)
{
	if(connectFlag){
		return true;
	}

	//RS232C����p RS232C �̏�����
	hCom = CreateFile(comport, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
	if (hCom == INVALID_HANDLE_VALUE) {
		connectFlag = false;
		return false;
	}

	dcb.DCBlength = sizeof(DCB) ;

	GetCommState(hCom, &dcb) ;

	//�V���A���ʐM��{�ݒ�
	dcb.BaudRate = baudrate;	// �ʐM���x
	dcb.ByteSize = 8;			// �f�[�^��
	dcb.Parity = NOPARITY;		// �p���e�B�r�b�g�FEVENPARITY,MARKPARITY,NOPARITY,ODDPARITY
	dcb.StopBits = ONESTOPBIT;  // �X�g�b�v�r�b�g�FONESTOPBIT,ONE5STOPBITS,TWOSTOPBITS
	dcb.fOutxCtsFlow = FALSE;	// ���M���ɁACTS ���Ď����邩�ǂ���
	dcb.fOutxDsrFlow = FALSE;	// ���M���ɁADSR ���Ď����邩�ǂ���
	dcb.fDsrSensitivity = FALSE;// DSR ��OFF�̊Ԃ͎�M�f�[�^�𖳎����邩

	//bool flag;
	////�ǉ��ݒ�
	////�{�[���[�g�̐ݒ�

	if(SetCommState(hCom, &dcb)){
		connectFlag = true;
	}else{
		connectFlag = false;
	}

	if(connectFlag==true)
	{
		GetCommTimeouts(hCom,&ctmo);
		ctmo.ReadIntervalTimeout = 0;		    // ��M�f�[�^�Ԃ̃^�C���A�E�g����[msec]
		ctmo.ReadTotalTimeoutMultiplier = 10;	// ��M�^�C���A�E�g�g�[�^�����ԁ@���i ReadTotalTimeoutMultiplier ���@��M�\��o�C�g���@�j
		ctmo.ReadTotalTimeoutConstant = 50;		// �@�{�@ReadTotalTimeoutConstant�@[mSec]
		ctmo.WriteTotalTimeoutMultiplier = 10;	// ��M�^�C���A�E�g�g�[�^�����ԁ@���i WriteTotalTimeoutMultiplier ���@��M�\��o�C�g���@�j
		ctmo.WriteTotalTimeoutConstant = 50;	// �@�{�@WriteTotalTimeoutConstant�@[mSec]
		if(!SetCommTimeouts(hCom,&ctmo)){
			connectFlag = false;
			return false;
		}
	}

	////�ʐM�o�b�t�@�����ׂăN���A
	PurgeComm(hCom, PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR);

	return connectFlag;	
}

//! Terminate method : Close serial port
bool CSerial::CloseSerial(void)
{
	if(!connectFlag) return false;//�|�[�g���J���Ă��Ȃ��̂�CLOSE����ƃo�O��̂����P
	if(CloseHandle(hCom)){
		return true;
	}else{
		return false;
	}
}

//! send 1 byte
bool CSerial::fputc(BYTE data,bool view_enable)
{
	unsigned long byte;
	
	// 1�o�C�g���M
	if(WriteFile(hCom, &data, sizeof(BYTE), &byte, NULL)){
		//���C���o��
		if(view_enable){
			std::cout <<">>>" ;
			printf(" 0x%x",(unsigned char)data); 
			std::cout << "\n";
		}
		return true;
	}else{
		return false;
	}
}

//! send string
bool CSerial::fput(unsigned char* data, int size,bool view_enable)
{
	unsigned long byte;
	//�����񑗐M
	if(WriteFile(hCom, data, size, &byte, NULL)){
		//�o��
		if(view_enable){
			printf(">>>");
			for(int i = 0;i<size;i++){
				printf(" 0x%x",(unsigned char)data[i]);
			}
			printf("\n");
		}
		return true;
	}else{
		return false;
	}

}

//! get 1 byte
BYTE CSerial::fgetc(bool view_enable)
{
	unsigned long byte;
	BYTE data = 0x00;

	//��M�҂�	
	while(!kbhit());

	//�P�o�C�g��M
	ReadFile(hCom, &data, 1, &byte, NULL);
	
	//���C���o��
	if(view_enable){
		std::cout <<"<<<" ;
		printf(" 0x%x",(unsigned char)data); 
		std::cout << "\n"; 
	}

	return data;
}

//! get string
DWORD CSerial::fget(unsigned char* data, int size,bool view_enable)
{
	DWORD byte;

	//��M�҂�	
	while(!kbhit());

	//�������M
	ReadFile(hCom, data, size, &byte, NULL);

	//�o��
	if(view_enable){
		printf("<<<");
		for(int i = 0;i<size;i++){
			printf(" 0x%x",(unsigned char)data[i]);
		}
		printf("\n");
	}

	return byte;

}

// ��M�f�[�^�̃o�C�g���𒲂ׂĒl��Ԃ�
//! Tell how many data(bytes) we had gotten in Rx buffer
DWORD CSerial::CheckSerialData(void)
{

	DWORD	dwErrors;  // �G���[���
	COMSTAT	ComStat; // �f�o�C�X�̏��
	DWORD	dwCount;   // ��M�f�[�^�̃o�C�g��

	ClearCommError(hCom, &dwErrors, &ComStat);
	dwCount = ComStat.cbInQue;

    return dwCount;
}

//! return whether is there any data in the buffer
bool CSerial::kbhit(void)
{
	return (bool)(CheckSerialData() != 0);
}

//! CLEAR Rx Buffer
void CSerial::ClearRXbuffer(void)
{
	//��M�o�b�t�@�����ׂăN���A
	PurgeComm(hCom, PURGE_RXABORT | PURGE_RXCLEAR);
}

bool CSerial::isOpen(void){
	return connectFlag;
}
