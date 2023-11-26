#include <string>
#include <iostream>
#include "iputils.h"
using namespace std;


int main(int argc, char* argv[]) {
	setlocale(LC_CTYPE, "Rus");

	string input_ip, input_mask;
	unsigned long ip, mask, subnet, host, broadcast;
	string formatted_ip, formatted_mask, formatted_subnet, formatted_host, formatted_broadcast;

	if (argc < 3) {
		cout << "Usage: " << argv[0] << " <ip> <mask>";
		return 0;
	}
	
	input_ip = argv[1];
	input_mask = argv[2];

	if (!CheckFormat(input_ip)) {
		cout << "�������� ������ IP-������" << endl;
		return 0;
	}
	if (!CheckFormat(input_mask)) {
		cout << "�������� ������ �����" << endl;
		return 0;
	}

	ip = GetAddress(input_ip);
	mask = GetAddress(input_mask);

	if (!CheckMask(mask)) {
		cout << "������������ �����" << endl;
		return 0;
	}

	subnet = GetSubnet(ip, mask);
	host = GetHost(ip, mask);
	broadcast = GetBroadcast(ip, mask);

	formatted_ip = FormatAddress(ip);
	formatted_mask = FormatAddress(mask);
	formatted_subnet = FormatAddress(subnet);
	formatted_host = FormatAddress(host);
	formatted_broadcast = FormatAddress(broadcast);

	cout 
		<< "IP:\t\t\t" << formatted_ip << endl
		<< "�����:\t\t\t" << formatted_mask << endl
		<< "ID �������:\t\t" << formatted_subnet << endl
		<< "ID �����:\t\t" << formatted_host << endl
		<< "Broadcast �����:\t" << formatted_broadcast << endl
	;

	return 0;
}
