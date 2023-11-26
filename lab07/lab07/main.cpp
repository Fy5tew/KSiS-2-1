#include <locale.h>
#include <iostream>

#include "ping.h"


using namespace std;


enum NextValueFor {
	Host,
	Count,
	Timeout,
};


void PrintHelp(char* pathname) {
	cout
		<< "�������������: " << pathname << " [-c <�����>] [-t <�����_��������>] ����" << endl
		<< "���������:" << endl
		<< "\t-c <�����>\t\t\t����� ������������ ��������." << endl
		<< "\t-t <�����_��������>\t\t����� �������� ������� ������� (� �������������)" << endl
	;
}


int main(int argc, char** argv) {
	setlocale(LC_ALL, "RUS");

	/*Ping("192.168.0.106", 60, 10);
	_getch();*/

	if (argc == 1) {
		PrintHelp(argv[0]);
	}
	else {
		char* host = nullptr;
		int count = 10;
		int timeout = 60;

		NextValueFor nextFor = NextValueFor::Host;
		for (int i = 1; i < argc; i++) {
			char* arg = argv[i];
			if (strcmp(arg, "-c") == 0) {
				nextFor = NextValueFor::Count;
				continue;
			}
			else if (strcmp(arg, "-t") == 0) {
				nextFor = NextValueFor::Timeout;
				continue;
			}

			switch (nextFor) {
				case NextValueFor::Host: {
					host = arg;
					break;
				}
				case NextValueFor::Count: {
					count = atoi(arg);
					nextFor = NextValueFor::Host;
					break;
				}
				case NextValueFor::Timeout: {
					timeout = atoi(arg);
					nextFor = NextValueFor::Host;
					break;
				}
			}
		}

		bool isInvalidInput = false;
		if (host == nullptr) {
			cout << "���������� ������� ����" << endl;
			isInvalidInput = true;
		}
		if (count <= 0) {
			cout << "������ ��� �������� ���������� ��������: " << count << endl;
			isInvalidInput = true;
		}
		if (timeout <= 0) {
			cout << "������ ��� �������� ������� ��������: " << timeout << endl;
			isInvalidInput = true;
		}

		if (isInvalidInput) {
			PrintHelp(argv[0]);
		}
		else {
			cout
				<< "������� ���������:" << endl
				<< "\t����:\t\t\t" << host << endl
				<< "\t���������� ��������:\t" << count << endl
				<< "\t����� ��������:\t\t" << timeout << endl
				<< endl
			;
			Ping(host, timeout, count);
		}
	}

	return 0;
}
