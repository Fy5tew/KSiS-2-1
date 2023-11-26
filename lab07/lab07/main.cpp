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
		<< "Использование: " << pathname << " [-c <число>] [-t <время_ожидания>] хост" << endl
		<< "Параметры:" << endl
		<< "\t-c <число>\t\t\tЧисло отправляемых запросов." << endl
		<< "\t-t <время_ожидания>\t\tВремя ожидания каждого запроса (в миллисекундах)" << endl
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
			cout << "Необходимо указать хост" << endl;
			isInvalidInput = true;
		}
		if (count <= 0) {
			cout << "Ошибка при указании количества запросов: " << count << endl;
			isInvalidInput = true;
		}
		if (timeout <= 0) {
			cout << "Ошибка при указании времени ожидания: " << timeout << endl;
			isInvalidInput = true;
		}

		if (isInvalidInput) {
			PrintHelp(argv[0]);
		}
		else {
			cout
				<< "Входные параметры:" << endl
				<< "\tХост:\t\t\t" << host << endl
				<< "\tКоличество запросов:\t" << count << endl
				<< "\tВремя ожидания:\t\t" << timeout << endl
				<< endl
			;
			Ping(host, timeout, count);
		}
	}

	return 0;
}
