#pragma once

#include <string>

namespace Ti
{
	//! 4 types of loggables, a problem, a success, a warning or a message.
	enum class LogType
	{
		PROBLEM = 1,
		SUCCESS = 2,
		WARNING = 3,
		MESSAGE = 4

	};

	//! Logger prints something based on it's LogType and on the LogDebugLevel (specify in the source file).
	class Logger
	{
	public:
		//! Prints a string.
		static void Print(const std::string log, const LogType type = LogType::MESSAGE);
		//! Prints a number.
		static void Print(const float number, const LogType type = LogType::MESSAGE);

	};
}