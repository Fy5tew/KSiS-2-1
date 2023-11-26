#pragma once
#include <string>


bool CheckFormat(std::string ip);

unsigned long GetAddress(std::string formatted);

std::string FormatAddress(unsigned long address);

bool CheckMask(unsigned long mask);

unsigned long GetSubnet(unsigned long ip, unsigned long mask);


unsigned long GetHost(unsigned long ip, unsigned long mask);


unsigned long GetBroadcast(unsigned long ip, unsigned long mask);
