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

	while (1) {
		count++;
		//Dyna.TurnOnLED(i, (count+i)%8);
		//am::delay_ms(1);
		//Dyna.SetGoalAngle(i, 150 * sin(count*0.0314/3.));
		Dyna.SetGoalRad(ID, 1. * am::pi / 6. * sin(count *am::pi / 1000.));
		//Dyna.SetGoalPos(i, 100);
		if (!Dyna.update(ID, s_angle, s_omega, s_load, s_volt, s_temp)) {
			fail_count++;
		}

		if (count % 100 == 1) {
			duration = am::get_system_time_kon() - prevTime;
			prevTime = am::get_system_time_kon();
			// ���Ԃ̕\��
			std::cout << "Time: for 100 commands : " << duration << "ms" << std::endl;
			std::cout << " Pos : " << s_angle << ", Spd : " << s_omega << std::endl;
			std::cout << " Load: " << s_load << ", Volt : " << s_volt << ", Tmp : " << s_temp << std::endl;
			std::cout << " Fail rate :" << (double)fail_count/(double)count * 100. << "%" <<  std::endl;
		}
	}

	return 0;
}



