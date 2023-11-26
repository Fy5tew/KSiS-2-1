#include <string>
#include <iostream>
using namespace std;


bool CheckFormat(string formatted) {
	int points = 0;
	string buffer = "";
	
	for (char ch : (formatted + '\0')) {
		if (isdigit(ch)) {
			buffer += ch;
			continue;
		}
		if (ch == '.') {
			points++;
		}
		if (ch == '.' || ch == '\0') {
			if (buffer.empty()) {
				return false;
			}
			if (stoi(buffer) > 255) {
				return false;
			}
			buffer = "";
		}
		else {
			return false;
		}
	}

	if (points != 3) {
		return false;
	}
	return true;
}


unsigned long GetAddress(string formatted) {
	if (!CheckFormat(formatted)) {
		throw new invalid_argument("Invalid format");
	}
	
	unsigned long address = 0;
	string buffer;
	for (char ch : formatted + '\0') {
		if (isdigit(ch)) {
			buffer += ch;
		}
		else {
			address <<= 8;
			address += (unsigned long)stoi(buffer);
			buffer = "";
		}
	}

	return address;
}


string FormatAddress(unsigned long address) {
	string formatted = "";
	for (int i = 24; i >= 0; i -= 8) {		
		int part = (address & (255 << i)) >> i;
		formatted += to_string(part) + '.';
	}
	formatted.pop_back();
	return formatted;
}


bool CheckMask(unsigned long mask) {
	bool foundZero = false;
	for (int i = 24; i >= 0; i--) {
		int bit = (mask & (1 << i)) >> i;
		if (foundZero && bit == 1) {
			return false;
		}
		if (bit == 0) {
			foundZero = true;
		}
	}
	return true;
}


unsigned long GetSubnet(unsigned long ip, unsigned long mask) {
	return ip & mask;
}


unsigned long GetHost(unsigned long ip, unsigned long mask) {
	return ip & ~mask;
}


unsigned long GetBroadcast(unsigned long ip, unsigned long mask) {
	return ip & mask | ~mask;
}
