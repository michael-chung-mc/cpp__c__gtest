#pragma once
#ifndef PCH_H
#define PCH_H

#include <gtest/gtest.h>

#include <iomanip>
#include <ctime>
#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <memory>

inline std::string getPPMFilename(bool linuxPath) {
	std::time_t now = std::time(nullptr);
	std::tm ltm = *std::localtime(&now);
	std::stringstream ss;
	ss << std::put_time(&ltm, "%Y%m%d_%H%M%S");
	std::string time = ss.str();
	std::string dirWindows = "./data/";
	std::string dirLinux = ".\\data\\";
	std::string dir = linuxPath ? dirLinux : dirWindows;
	std::string path = dir + time + ".ppm";
	std::cout << path << std::endl;
	return path;
}
inline float getEpsilon() {
	return 0.0001;
	// return 0.00001;
}
inline int getPPMWidth() {
	return 720;
}
inline int getPPMHeight() {
	return 480;
}
inline int getPPMLineWidth() {
	return 70;
}
inline double getPI()
{
	return 3.141592653589793238463;
}

#endif