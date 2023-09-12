﻿#include "Logger.h"

Logger::Logger(const std::string& filename) : _filename(filename)
{
	std::ifstream fileExists(filename);
	if (!fileExists)
	{
		std::cout << "ОШИБКА: файл " << filename << " не найден" << std::endl;
		std::ofstream fileCreate(filename);
		if (fileCreate)
		{
			std::cout << "Создан файл " << filename << std::endl;
			fileCreate << "[" << getCurrentTime() << "] " << "Файл создан " << std::endl;
			fileCreate.close();
		}
		else
		{
			std::cout << "\nОШИБКА: файл " << filename << " не удалось создать" << std::endl;
		}
	}
	else
	{
		_logFile.open(filename, std::ios::app);
		std::cout << "Файл " << filename << " открыт" << std::endl;
	}
}

Logger::~Logger()
{
	if (_logFile.is_open())
	{
		_logFile.close();
		std::cout << "Файл log.txt закрыт" << std::endl;
	}
}

void Logger::writeLogToFile(const std::string& logMessage)
{
	std::unique_lock<std::shared_mutex> lock(_logMutex);
	if (_logFile.is_open())
	{
		_logFile << logMessage << std::endl;
	}
	else
	{
		std::cout << "\nОШИБКА: не удалось записать сообщение в файл логов" << std::endl;
	}
}

void Logger::readLogFromFile()
{
	std::shared_lock<std::shared_mutex> lock(_logMutex);
	std::ifstream inputFile(_filename);

	if (inputFile.is_open())
	{
		std::string line;
		while (std::getline(inputFile, line))
		{
			std::cout << line << std::endl;
		}

		inputFile.close();
	}
	else
	{
		std::cout << "\nОШИБКА: не удалось открыть файл логов для чтения" << std::endl;
	}
}

