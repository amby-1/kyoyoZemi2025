/* ***********************************************************************


Dynamixel_Mx Mx-28 用クラス Ver 1
Configuration 
 Dynamixel : Read Only mode
 Return wait : 10us

 2018.3.7 Start development
2025.4.28 Redesign for class
 ************************************************************************ */

#ifndef Dynamixel_MX_SIMPLE_HPP
#define Dynamixel_MX_SIMPLE_HPP

#include <iostream>
#include "serial.h"
#include "amBasic.h"

#define WAIT_TIME 20// 通信待機時間 (ms)

// CSerial Com1; // SerialClass

// ダイナミクセルのデータ取得用変数

// ダイナミクセル通信クラス
class Mx28{
private:
	CSerial serial;
	unsigned char buf[100];// 通信管理用バッファ

	// data acquision 


public:
	Mx28(TCHAR* comport, int baudrate):serial(){
		serial.InitSerial(comport, baudrate);
	}

	virtual ~Mx28(){
		serial.CloseSerial();
	}	

	bool is_open() {
		return serial.isOpen();
	}


private:
	bool write_data(unsigned char ID, unsigned char address, unsigned char num, unsigned char* data){
		buf[0] = (unsigned char)0xFF;//header
		buf[1] = (unsigned char)0xFF;//header
		buf[2] = ID;
		buf[3] = num + 3;//data_num
		buf[4] = 0x03;//instruction
		buf[5] = address;//address
//printf("%d s_start \n",amTime.get_systime());
		for(int i = 0;i<num;i++){
			buf[6+i] = data[i];
		}
		buf[num + 6 ] = 0;
		for(int i = 2;i<(num+6 );i++){
			buf[num + 6 ] = (unsigned char)(buf[num + 6] + buf[i]);
		}
		buf[num + 6] = ~buf[num + 6];

		serial.ClearRXbuffer();

		serial.fput(buf, num+7);

		return true;
	}

	bool read_data(unsigned char ID, unsigned char address, unsigned char num, unsigned char* data, unsigned char& error1){
		buf[0] = (unsigned char)0xFF;//header
		buf[1] = (unsigned char)0xFF;//header
		buf[2] = ID;
		buf[3] = 0x04;//data_num
		buf[4] = 0x02;//instruction
		buf[5] = address;
		buf[6] = num;//�ǂݍ��ސ�
		buf[7] = 0;
		for(int i = 2;i<7;i++){
			buf[7] = (unsigned char)(buf[7] + buf[i]);
		}

		buf[7] = ~buf[7];
		serial.ClearRXbuffer();

		serial.fput(buf, 8);

		long long time;
		time = am::get_system_time_kon();

		while (1){
			// data acquisition
			if (serial.kbhit()) {
				if ((unsigned char)(serial.fgetc(false)) == 0xFF) {
					break;
				}
			}
			// time over
			if (am::get_system_time_kon() > (time + WAIT_TIME)) {
				std::cout << "timeout :" << am::get_system_time_kon() <<  std::endl;
				return false;
			}
		}

		while((unsigned char)(serial.CheckSerialData()) < (num + 5)){
			if(am::get_system_time_kon() > (time + WAIT_TIME)){
				return false;
			}
		}

		serial.fget(buf,num + 5, false);
		if(buf[0] != (unsigned char)0xFF){
			return false;
		}else if(buf[1] != ID ){
			return false;
		}else if(buf[2] != (num + 2) ){
			return false;
		}else{		
			error1 = buf[3];

			for(int i = 0;i<num;i++){
				data[i] = buf[i + 4];
			}
			return true;
		}
	}

	bool set_data(unsigned char ID, unsigned char address, unsigned char num, unsigned char* data){
		buf[0] = (unsigned char)0xFF;//header
		buf[1] = (unsigned char)0xFF;//header
		buf[2] = ID;
		buf[3] = num + 3;//data_num
		buf[4] = 0x04;//instruction
		buf[5] = address;//address
		for(int i = 0;i<num;i++){//�������݃f�[�^
			buf[6+i] = data[i];
		}
		buf[num + 6 ] = 0;
		for(int i = 2;i<(num+6 );i++){
			buf[num + 6 ] = (unsigned char)(buf[num + 6] + buf[i]);
		}
		buf[num + 6] = ~buf[num + 6];

		serial.ClearRXbuffer();
		serial.fput(buf, num+7);

		return true;
	}

	bool action(void){
		buf[0] = (unsigned char)0xFF;//header
		buf[1] = (unsigned char)0xFF;//header
		buf[2] = 0xFE;//�S�Ă��w��
		buf[3] = 2;//data_num
		buf[4] = 0x05;//instruction
		buf[5] = buf[2] + buf[3] + buf[4];
		buf[5] = ~buf[5];

		serial.ClearRXbuffer();

		//���M
		serial.fput(buf, 6);
		return true;
	}


public:
	// set goal position with angle (degree)	
	void SetGoalAngle(uint8_t ID, double angle){
		uint16_t pos = static_cast<uint16_t>(angle / 180. * 2048 + 2048);
		if (pos > 4095) {
			pos = 4095;
		}
		unsigned char data[2];
		data[0] = (unsigned char)(pos);
		data[1] = (unsigned char)((pos)/256);

		write_data(ID, 0x1E, 2, data);
	}

	// set goal position with angle (rad)	
	void SetGoalRad(uint8_t id, double angleRad) {
		uint16_t pos = static_cast<uint16_t>(angleRad / ( am::pi) * 2048 + 2048);
		if (pos > 4095) {
			pos = 4095;
		}
		unsigned char data[2];
		data[0] = (unsigned char)(pos);
		data[1] = (unsigned char)((pos) / 256);

		write_data(id, 0x1E, 2, data);
	}

	// set goal position with angle (rad)	
	void SetGoalRad_wLimit(uint8_t id, double angleRad, double minRad=-am::pi/2., double maxRad=am::pi/2.) {
		if(angleRad>maxRad){
			std::cout << "Cmd angle goes over upped bound -- cmd angle=" << angleRad << std::endl;
			angleRad=maxRad;
		}else if(angleRad<minRad){
			std::cout << "Cmd angle goes under lower bound -- cmd angle=" << angleRad << std::endl;
			angleRad=minRad;
		}
		uint16_t pos = static_cast<uint16_t>(angleRad / ( am::pi) * 2048 + 2048);
		if (pos > 4095) {
			pos = 4095;
		}
		unsigned char data[2];
		data[0] = (unsigned char)(pos);
		data[1] = (unsigned char)((pos) / 256);

		write_data(id, 0x1E, 2, data);
	}

	// set maximum speed with radian (rad/s)
	//  if you want to set MAXIMUM speed that motor can realize, please set speed as zero
	void SetSpeedRad(uint8_t id, double speedRad) {
		uint16_t spd = static_cast<uint16_t>(speedRad / (2. * am::pi) * 60. /0.114 );
		if (spd > 2047) {
			spd = 2047;
		}
		unsigned char data[2];
		data[0] = (unsigned char)(spd);
		data[1] = (unsigned char)((spd) / 256);

		write_data(id, 0x20, 2, data);
	}

	// Tor	// Torque ON/OFF
	void SetTorqueEn(uint8_t ID, uint8_t enable){
		unsigned char data;
		data = enable;
		write_data(ID,0x18,1,&data);
	}

	// LED 	// LED ON/OFF
	void TurnOnLED(uint8_t ID, uint8_t led) {
		unsigned char data;
		data = led;
		write_data(ID, 0x19, 1, &data);
	}

	// PID 
	// This is dicimal value
	void SetPID(uint8_t ID, double P_, double I_, double D_) {
		unsigned char data[3];
		if (P_ < 0.) {
			P_ = 0.;
		}else if (P_ > 254 ) {
			P_ = 254;
		}

		if (I_ < 0.) {
			I_ = 0.;
		}else if ( I_ > 254  ) {
			I_ = 254 ;
		}
		
		if (D_ < 0.) {
			D_ = 0.;
		}else if (D_ > 254. ) {
			D_ = 254. ;
		}

		// out
		data[0] = static_cast<uint8_t>(D_ );
		data[1] = static_cast<uint8_t>(I_ );
		data[2] = static_cast<uint8_t>(P_ );
		write_data(ID, 0x1A, 3, data);
	}

	// Data 取得関数（通信コストを抑えるために一括でデータを取得する）
	// すべての観測データをまとめて取得する関数
	// 取得するデータは以下の通り
	//  angle [rad], speed [rad/s], load(non dimensional value: 0 to 1), volt [V], temprature [cersius deg] 
	//  error 
	//	 Bit 6 Instruction Error
	//	 Bit 5 Overload Error
	//	 Bit 4 Checksum Error
	//	 Bit 3 Range Error
	//	 Bit 2 Overheating Error
	//	 Bit 1 Angle Limit Error
	//	 Bit 0 Input Voltage Error
	bool update(unsigned char ID, double& angle, double& speed, double& load, double& volt, double &temprature, unsigned char& error) {
		//ID�Ŏw�肵�āA�ʒu�A���x�A�׏d�A�d���A���x��ԐM
		unsigned char data[8];
		if (read_data(ID, 0x24, 8, data, error)) {
			//�p�x�̍X�V
			angle = ( (double)( (uint16_t)data[0] +  (uint16_t)(data[1]) * 256 ) - 2048. ) * am::pi / 2048.;

			//���x�̍X�V
			int spd_int = (int)(((uint16_t)data[2]) + ((uint16_t)(data[3]) * 256));
			if (((spd_int & 0x0400) != 0)){
				spd_int = -spd_int;
			}
			spd_int = spd_int % 1024;
			speed = spd_int * 0.114 * 2. * am::pi / 60.;

			//�׏d�̍X�V
			int load_int = (int)((uint16_t)data[4] + (uint16_t)(data[5]) * 256);
			if (((load_int & 0x0400) != 0)) {
				load_int = -load_int;
			}
			load_int = load_int % 1024;
			load = load_int / 1024.;

			//Volt�̍X�V(V)
			volt = (double)(data[6]) * 0.1;

			//���x�̍X�V(��)
			temprature = (double)data[7];

			return true;

		}
		else {
			return false;
		}
	}

	// without taking Error variable   
	bool update(unsigned char ID, double& angle, double& speed, double& load, double& volt, double &temprature) {
		unsigned char error;
		return update(ID, angle, speed, load, volt, temprature, error);
	}

};


#endif


