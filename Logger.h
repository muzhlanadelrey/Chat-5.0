#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <mutex>
#include <shared_mutex>

class Logger
{
private:
	std::string _filename;
	std::ofstream _logFile;
	mutable std::shared_mutex _logMutex;


public:
	Logger(const std::string& filename);
	~Logger();

	void writeLogToFile(const std::string& logMessage);
	void readLogFromFile();

};