#include <iostream>
#include <unistd.h>
#include <sys/time.h>
#include <signal.h>
#include "dxl.hpp"
using namespace std;
bool ctrl_c_pressed = false;
void ctrlc_handler(int) { ctrl_c_pressed = true; }
int main(void)
{
	Dxl mx;
	struct timeval start, end1;
	double time1;
	int vel1 = 0, vel2 = 0;
	signal(SIGINT, ctrlc_handler);
	if (!mx.open()) { cout << "dynamixel open error" << endl; return -1; }
	while (true)
	{
		gettimeofday(&start, NULL);
		if (mx.kbhit()) //Ű�����Է� üũ
		{
			char c = mx.getch(); //Ű�Է� �ޱ�
			switch (c)
			{
			case 's': vel1 = 0; vel2 = 0; break; //����
			case 'f': vel1 = 50; vel2 = -50; break; //����
				case 'b': vel1 = -50; vel2 = 50; break; //����
				case 'l': vel1 = -50; vel2 = -50; break; //��ȸ��
				case 'r': vel1 = 50; vel2 = 50; break; //��ȸ��
				default: vel1 = 0; vel2 = 0; break; //����
			}
			mx.setVelocity(vel1, vel2);
		}
		if (ctrl_c_pressed) break; //Ctrl+c�Է½� Ż��
		usleep(20 * 1000);
		gettimeofday(&end1, NULL);
		time1 = end1.tv_sec - start.tv_sec
			+ (end1.tv_usec - start.tv_usec) / 1000000.0;
		cout << "vel1:" << vel1 << ',' << "vel2:" << vel2 <<
			��, time:"<<time1<< endl;
	}
	mx.close(); // ��ġ�ݱ�
	return 0;
}