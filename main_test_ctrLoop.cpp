#include <iostream>
#include "Dynamixel_Mx_simple.hpp"

int main(){
	double prevTime = 0;
	double duration = 0;
	int count = 0;
	int fail_count = 0;

	std::cout << "Start program for checking dynamixel movement" << std::endl;
	getchar();

	//Set port 
	Mx28 Dyna((TCHAR*)"\\\\.\\COM4", 1000000);
	if (Dyna.is_open()) {
		std::cout << "Success to Open port" << std::endl;
	}
	else {
		std::cout << "Fail to Open port" << std::endl;
		getchar();
		return 0;
	}

	// specify ID
	int ID = 12;

	// 初期位置にゆっくり移動する
	Dyna.TurnOnLED(ID, 1);
	Dyna.SetSpeedRad(ID, 0.4);
	Dyna.SetGoalRad(ID, 0.);

	// PIDゲインを決める
	Dyna.SetPID(ID, 4., 0., 0.);
	am::delay_ms(15000);

	// 最大速度出せるようにする
	Dyna.SetSpeedRad(ID, 0);

	// sensing 値を格納する箱
	double s_angle = 0.;
	double s_omega = 0.;
	double s_load = 0.;
	double s_volt = 0.;
	double s_temp = 0.;

	static int ctrFreq = 100; //  100
	double omega = am::pi / 10.;
	double amp = 1. * am::pi / 2.;

	prevTime = am::get_system_time_kon();
	while (1) {
		count++;
		double time = count / (double)ctrFreq;
		// Command 送る
		//  安全のため，リミット付きの関数を使って下さい．リミット値入れるのを忘れずに
		Dyna.SetGoalRad_wLimit(ID, amp * sin(omega * time), -1.6, 1.6);

		// sensing する
		if (!Dyna.update(ID, s_angle, s_omega, s_load, s_volt, s_temp)) {
			std::cout << "Fail to update data" << std::endl;
		}

		if (count % 100 == 1) {
			std::cout << " Pos : " << s_angle << ", Spd : " << s_omega << std::endl;
			std::cout << " Load: " << s_load << ", Volt : " << s_volt << ", Tmp : " << s_temp << std::endl;
		}

		while( am::get_system_time_kon() - prevTime < 1000./ctrFreq){
			// wait for next command
		}
		prevTime = am::get_system_time_kon();
	}

	return 0;
}



