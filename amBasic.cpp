/***************************************************
//! amBasic ver2
//! amBasic.cpp

��������
****************************************************/

#include "amBasic.h"
#include <time.h>
#include <cstdio>  // sprintf_s のために追加

//�֗��ϐ�
namespace am{
	//! �֗��ϐ� pi
	const double pi = 4 * atan(1.);

//class Pint
	//! default constructor
	Pint::Pint(){
		x=0;
		y=0;
	}
	//! Constructor
	Pint::Pint(int _x,int _y){
		x = _x;
		y = _y;
	}

	//! �����Z
	Pint Pint::operator+(Pint obj){
		Pint ans(0,0);
		ans.x = x + obj.x;
		ans.y = y + obj.y;
		return ans;
	}
	//! �����Z
	Pint Pint::operator-(Pint obj){
		Pint ans;
		ans.x = x - obj.x;
		ans.y = y - obj.y;
		return ans;
	}
	//! �|���Z
	Pint Pint::operator*(int c){//������X�J���[(���ӁF�FPint�̌��ɃX�J���[�I�I)
		Pint ans;
		ans.x = c * x;
		ans.y = c * y;
		return ans;
	}
	//! ����
	int Pint::operator*(Pint obj){//����
		int ans;
		ans = x * obj.x + y * obj.y;
		return ans;
	}
	//! �s������
	bool Pint::operator>(Pint obj){
		return((x > obj.x) && (y > obj.y) );
	}
	//! �s������
	bool Pint::operator<(Pint obj){
		return((x < obj.x) && (y < obj.y) );
	}
	//! �s��������
	bool Pint::operator<=(Pint obj){
		return((x <= obj.x) && (y <= obj.y) );
	}
	//! �s��������
	bool Pint::operator>=(Pint obj){
		return((x >= obj.x) && (y >= obj.y) );
	}
	//! !=�I�y���[�^
	bool Pint::operator!=(Pint obj){
		return((x != obj.x) && (y != obj.y));
	}
	//! ==�I�y���[�^
	bool Pint::operator==(Pint obj){
		return((x == obj.x) && (y == obj.y));
	}

	//! ��남���C���N�������g
	Pint Pint::operator++(int){
		x = x + 1;
		y = y + 1;
		return *this;
	}
	//! ���u���f�B�N�������g
	Pint Pint::operator--(int){
		x = x - 1;
		y = y - 1;
		return *this;
	}
	//! �O�u���C���N�������g
	Pint Pint::operator++(){
		x = x + 1;
		y = y + 1;
		return *this;
	}
	//! �O�u���f�B�N�������g
	Pint Pint::operator--(){
		x = x - 1;
		y = y - 1;
		return *this;
	}
	//���Z���đ��
	Pint Pint::operator+=(Pint obj){
		x = x + obj.x;
		y = y + obj.y;
		return *this;
	}
	//���Z���đ��
	Pint Pint::operator-=(Pint obj){
		x = x - obj.x;
		y = y - obj.y;
		return *this;
	}

	
//�ʒu�`��̂��߂̕ϐ�(double)�i���W�j
//class Pdouble
	//! default constructor
	Pdouble::Pdouble(){
		x=0.;
		y=0.;
	}
	//! Constructor
	Pdouble::Pdouble(double _x,double _y){
		x = _x;
		y = _y;
	}
	//! Conv to Pint
	Pint Pdouble::Change_Pint(){
		Pint p;
		p.x = (int)(x);
		p.y = (int)(y);
		return p;
	}

	//! �����Z
	Pdouble Pdouble::operator+(Pdouble obj){
		Pdouble ans(0.,0.);
		ans.x = x + obj.x;
		ans.y = y + obj.y;
		return ans;
	}
	//! �����Z
	Pdouble Pdouble::operator-(Pdouble obj){
		Pdouble ans;
		ans.x = x - obj.x;
		ans.y = y - obj.y;
		return ans;
	}
	//! �|���Z
	Pdouble Pdouble::operator*(double c){//������X�J���[(���ӁF�FPdouble�̌��ɃX�J���[�I�I)
		Pdouble ans;
		ans.x = c * x;
		ans.y = c * y;
		return ans;
	}
	//! ����
	double Pdouble::operator*(Pdouble obj){//����
		double ans;
		ans = x * obj.x + y * obj.y;
		return ans;
	}

	//! �s���� >
	bool Pdouble::operator>(Pdouble obj){
		return((x > obj.x) && (y > obj.y) );
	}
	//! �s������
	bool Pdouble::operator<(Pdouble obj){
		return((x < obj.x) && (y < obj.y) );
	}
	//! �s��������
	bool Pdouble::operator<=(Pdouble obj){
		return((x <= obj.x) && (y <= obj.y) );
	}
	//! �s��������
	bool Pdouble::operator>=(Pdouble obj){
		return((x >= obj.x) && (y >= obj.y) );
	}
	//! �I���I�y���[�^
	bool Pdouble::operator!=(Pdouble obj){
		return((x != obj.x) && (y != obj.y));
	}
	//! ==�I�y���[�^
	bool Pdouble::operator==(Pdouble obj){
		return((x == obj.x) && (y == obj.y));
	}
	//! ���Z���đ��
	Pdouble Pdouble::operator+=(Pdouble obj){
		x = x + obj.x;
		y = y + obj.y;
		return *this;
	}
	//! ���Z���đ��
	Pdouble Pdouble::operator-=(Pdouble obj){
		x = x - obj.x;
		y = y - obj.y;
		return *this;
	}

	
//�x�N�g���N���X(3����)(double)�i���W�j
//class Vector3
	//! default Constructor
	Vector3::Vector3(){
		x=0.;
		y=0.;
		z=0.;
	}
	
	//! Constructor
	Vector3::Vector3(double _x,double _y,double _z){
		x = _x;
		y = _y;
		z = _z;
	}

	//! �����Z
	Vector3 Vector3::operator+(Vector3 obj){
		Vector3 ans(0.,0.,0.);
		ans.x = x + obj.x;
		ans.y = y + obj.y;
		ans.z = z + obj.z;
		return ans;
	}
	
	//! �����Z
	Vector3 Vector3::operator-(Vector3 obj){
		Vector3 ans;
		ans.x = x - obj.x;
		ans.y = y - obj.y;
		ans.z = z - obj.z;
		return ans;
	}
	//! �X�J���[�̊|���Z
	Vector3 Vector3::operator*(double c){//������X�J���[(���ӁF�FPdouble�̌��ɃX�J���[�I�I)
		Vector3 ans;
		ans.x = c * x;
		ans.y = c * y;
		ans.z = c * z;
		return ans;
	}

	//! �x�N�g���̓���
	double Vector3::operator*(Vector3 obj){//����
		double ans;
		ans = x * obj.x + y * obj.y + z * obj.z;
		return ans;
	}

	//! �x�N�g���̊O��
	Vector3 Vector3::operator%(Vector3 obj){//�O��
		Vector3 ans;
		ans.x = y*obj.z - z*obj.y;
		ans.y = z*obj.x - x*obj.z;
		ans.z = x*obj.y - y*obj.x;
		return ans;
	}

	//! !=���Z�q
	bool Vector3::operator!=(Vector3 obj){
		return !((x == obj.x) && (y == obj.y) && (z == obj.z));
	}
	//! ==���Z�q
	bool Vector3::operator==(Vector3 obj){
		return((x == obj.x) && (y == obj.y) && (z == obj.z));
	}

	//! ���Z���đ��
	Vector3 Vector3::operator+=(Vector3 obj){
		x = x + obj.x;
		y = y + obj.y;
		z = z + obj.z;
		return *this;
	}
	//���Z���đ��
	Vector3 Vector3::operator-=(Vector3 obj){
		x = x - obj.x;
		y = y - obj.y;
		z = z - obj.z;
		return *this;
	}

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
	/*
//class amTime

	//! Default Constructor
	amTime::amTime(){
		time(&t);
		ltm = *localtime(&t);
		year = ltm.tm_year + 1900;
		month = ltm.tm_mon + 1;
		day = ltm.tm_mday;
		hour = ltm.tm_hour;
		min = ltm.tm_min;
		sec = ltm.tm_sec;
	}
	//! ���̎��Ԃ��X�V
	void amTime::nowtime(){
		time(&t);
		ltm = *localtime(&t);
		year = ltm.tm_year + 1900;
		month = ltm.tm_mon + 1;
		day = ltm.tm_mday;
		hour = ltm.tm_hour;
		min = ltm.tm_min;
		sec = ltm.tm_sec;
	}
	/* 
	std::string get_timeStr(){
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
	*/
	/*
	//! ���ԑ҂�SLEEP
	void amTime::sleep(int millisec){//���ԑ҂�ms
//		clock_t tick;                          // �ҋ@�𔲂��鎞�� tick��
//		tick = (millisec * CLOCKS_PER_SEC) / 1000 + clock();
		long tick;
		tick = clock() + millisec;
		while(tick >=  clock());            // �ҋ@�I���� tick���Ɏ���܂Ń��[�v
	}

	//! PC����̌o�ߎ��Ԃ��炤
	long amTime::get_systime(){//PC�̊J�n����̎���(ms)�𒸂�
		return clock();
	}
	*/

	/*
	//! ��������ɓ����֐�
	std::string get_timeStr(){
		time_t     current;
		struct tm  local;
		
		time(&current);                    
		localtime_s(&local, &current);       
		
		char time[100];
		sprintf_s(time, "%4d%02d%02d_%02d%02d%02d", local.tm_year + 1900      
                                  , local.tm_mon + 1           
                                  , local.tm_mday              
                                  , local.tm_hour
								  , local.tm_min
								  , local.tm_sec);
		std::string timeStr(time);
		return timeStr;
	}
	*/

    //! ���Ԃ���ɓ����֐�
    long long get_system_time(){
        auto now = std::chrono::system_clock::now();
        auto duration = now.time_since_epoch();
        return std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
    }
    long long get_system_time_precise(){
        auto now = std::chrono::high_resolution_clock::now();
        auto duration = now.time_since_epoch();
        return std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
    }
	
	void delay_ms(int duration){
        auto start = std::chrono::high_resolution_clock::now();
        auto end = start +  std::chrono::milliseconds(duration);
        while(end > std::chrono::high_resolution_clock::now()){};
        return;
    }

	long long get_system_time_kon(){
#ifdef _WIN32
		LARGE_INTEGER freq, new_time;
		QueryPerformanceFrequency(&freq);
		QueryPerformanceCounter(&new_time);

		return (long long)((new_time.QuadPart)*1000000/freq.QuadPart)/1000;
#else
		struct timeval t1;
		gettimeofday(&t1,NULL);
		return (long long)(ToSec(t1)*1000.);
#endif
	}

	

}
