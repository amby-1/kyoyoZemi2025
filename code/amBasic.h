/*\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
//! amBasic ver.2

//! amBasic.h

�֗��ϐ��p�C
Pint,Pdouble,Vector,fStr,amTime

100413 Pdouble�ǉ�
		Pdouble ���� Pint �ϊ��@�\�ǉ�
		�t�ߒ����ł��Ă��Ȃ��̂ŁA�w�b�_�ƃ\�[�X�𕪂���K�v������	

110500 Vector�ǉ�

110704 �����N�G���[�����o
�@header,���������𕪂���

141117 ���Ԍv������ chrono C++0X

150116 ���Ԍv�������@kon���񂩂�̂���

150120 ���ݎ��������ƃ����O�`���ŏo�͂�ǉ�


\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
#ifndef AMBASIC_H
#define AMBASIC_H

#include <iostream>
#include <sstream>
#include <math.h>
#include <cstdarg>
#include <string>
#include <time.h>
#include <cstdio>  // sprintf_s のために追加
#include <chrono>
#ifdef _WIN32
	#include <Windows.h>
#else
	#include <sys/time.h>
#endif

#define D_FormatStrAdressSize 1024
namespace{
	char FormatStrAdress[D_FormatStrAdressSize];
}

namespace am{
	//! �֗��ϐ� pi
	extern const double pi;

	//! �ʒu�`��̂��߂̕ϐ�(2�����������W)
	class Pint{
	public:
		int x;
		int y;

		//! Default constructor
		Pint();
		//! Constructor
		Pint(int _x,int _y);
	/*
		Pdouble Change_Pdouble(){
			Pdouble ans;
			ans.x = (double)x;
			ans.y = (double)y;
			return ans;
		}
	*/
		//! Add Operator
		Pint operator+(Pint obj);
		//! Decrease Operator
		Pint operator-(Pint obj);
		//! Multiple Operator
		Pint operator*(int c);
		//! ����
		int operator*(Pint obj);


		//! �s�����@>
		bool operator>(Pint obj);
		//! �s�����@<
		bool operator<(Pint obj);
		//! �s�����@����
		bool operator<=(Pint obj);
		//! �s�����@����
		bool operator>=(Pint obj);

		//! �s�����@!=
		bool operator!=(Pint obj);
		//! �s�����@==
		bool operator==(Pint obj);

		//! ��남���C���N��
		Pint operator++(int);
		//! ���u���f�B�N��
		Pint operator--(int);
	
		//! �O�u���C���N��
		Pint operator++();
		//! �O�u���f�B�N��
		Pint operator--();

		//! ���Z���đ��
		Pint operator+=(Pint obj);
		//! ���Y���đ��
		Pint operator-=(Pint obj);

	};


	//! �ʒu�`��̂��߂̕ϐ�(double)�i2�����_�u�����W�j
	class Pdouble{
	public:
		double x;
		double y;

		//! Default Constructor
		Pdouble();
		//! Constructor
		Pdouble(double _x,double _y);
		//! Change to Pint
		Pint Change_Pint();

		//�����Z�����Z
		//! Add
		Pdouble operator+(Pdouble obj);
		//! Decrease
		Pdouble operator-(Pdouble obj);
		//�|���Z
		//! �X�J���[�|����
		Pdouble operator*(double c);
		//! ����
		double operator*(Pdouble obj);



		//! �s����>
		bool operator>(Pdouble obj);
		//! �s����<
		bool operator<(Pdouble obj);
		//! �s��������
		bool operator<=(Pdouble obj);
		//! �s���������@
		bool operator>=(Pdouble obj);
		//! �s�����@!=
		bool operator!=(Pdouble obj);
		//! �s�����@==
		bool operator==(Pdouble obj);
		//! ���Z���đ��
		Pdouble operator+=(Pdouble obj);
		//! ���Z���đ��
		Pdouble operator-=(Pdouble obj);
	};



	//! �x�N�g���N���X(3����)(double)�i���W�j
	class Vector3{
	public:
		double x;
		double y;
		double z;

		//! default constructor
		Vector3();
		//! Constructor
		Vector3(double _x,double _y,double _z);

		//! �����Z
		Vector3 operator+(Vector3 obj);
		//! �����Z
		Vector3 operator-(Vector3 obj);

		//! �X�J���[�̊|���Z
		Vector3 operator*(double c);
		//! �x�N�g���̓���
		double operator*(Vector3 obj);
		//! �x�N�g���̊O��
		Vector3 operator%(Vector3 obj);

		//! !=���Z�q
		bool operator!=(Vector3 obj);
		//! ==���Z�q
		bool operator==(Vector3 obj);

		//! ���Z���đ��
		Vector3 operator+=(Vector3 obj);
		//! ���Z���đ��
		Vector3 operator-=(Vector3 obj);
	};

	/*
	//printf �Ɠ��l�̌`���Ł@string �o�͂ł���
	std::string fStr(const char *String, ...){
		va_list valist;
		va_start(valist, String);
		vsprintf(FormatStrAdress,String,valist);
		va_end(valist);
		std::string str(FormatStrAdress);
		return str;
	}
	*/



	//���Ԃ���ɓ����֐�
	std::string get_timeStr();
	/*
	class amTime{
	private:
		time_t t;
		struct tm ltm; 
	public:
		int year;
		int month;
		int day;
		int hour;
		int min;
		int sec;

		//! Default Constructor
		amTime();

		//! time�X�V
		void nowtime();

		std::string get_timeStr();
		/*
		{
			time(&t);
			ltm = *localtime(&t);
			year = ltm.tm_year + 1900;
			month = ltm.tm_mon + 1;
			day = ltm.tm_mday;
			hour = ltm.tm_hour;
			min = ltm.tm_min;
			sec = ltm.tm_sec;
	//		return fStr("%d�N%d��%d�� %02d:%02d:%02d",year,month,day,hour,min,sec);
		}

		//! ���ԑ҂�(ms)
		//void sleep(int millisec);

		//! PC����̎��Ԃ����炤	
		//long get_systime();

	};
	*/

    //! �V�X�e�����Ԃ���ɓ����֐� (ms)
    long long get_system_time(void);
    long long get_system_time_precise(void);
    void delay_ms(int duration); 

	//! �V�X�e�����Ԃ���ɓ����֐��ims�j�����炪�M���������I�I�I
	long long get_system_time_kon(void);
}
#endif

