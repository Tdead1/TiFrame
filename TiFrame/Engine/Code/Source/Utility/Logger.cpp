#include <Utility/Logger.h>

#include <iostream>

using namespace Ti;

// The log level defines what is printed and what isn't.
#define LogDebugLevel 4

void Logger::Print(const std::string log, const LogType type)
{
	if (LogDebugLevel == 0 || (int) type <= LogDebugLevel)
	{
		switch (type)
		{
		case LogType::PROBLEM:
			std::cout << "<X>  ";
			break;			   
		case LogType::SUCCESS: 
			std::cout << "<+>  ";
			break;			   
		case LogType::WARNING: 
			std::cout << "<W>  ";
			break;			   
		case LogType::MESSAGE: 
			std::cout << "<i>  ";
			break;			   
		default:			   
			std::cout << "<i>  ";
			break;
		}
		std::cout << log << "\n";
	}
}

void Logger::Print(const float number, const LogType type)
{
	if (LogDebugLevel == 0 || (int)type <= LogDebugLevel)
	{
		switch (type)
		{
		case LogType::PROBLEM:
			std::cout << "<X>  ";
			break;			   
		case LogType::SUCCESS: 
			std::cout << "<+>  ";
			break;			   
		case LogType::WARNING: 
			std::cout << "<W>  ";
			break;			   
		case LogType::MESSAGE: 
			std::cout << "<i>  ";
			break;			   
		default:			   
			std::cout << "<i>  ";
			break;
		}
		std::cout << std::to_string(number) << "\n";
	}
}
