#include "pch.h"
std::string DateTime::getNowFormatted() {
	std::time_t now = std::time(nullptr);
	std::tm ltm = *std::localtime(&now);
	std::stringstream ss;
	ss << std::put_time(&ltm, "%Y%m%d_%H%M%S");
	std::string time = ss.str();
	return time;
}