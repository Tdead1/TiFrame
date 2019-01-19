#pragma once
#include <chrono>
#include <iostream>

#include <Utility/Logger.h>
namespace Ti
{
	//! A static header only timer class. Call Start() to start counting, call Stop() to stop the timer and then call Print() to print it.
	class Timer
	{
	public:
		//! Starts the clock.
		void start()
		{
			startTime = std::chrono::high_resolution_clock::now();
		};
		//! Stops the clock.
		float stop()
		{
			endTime = std::chrono::high_resolution_clock::now();
			// In seconds
			deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count() * 0.000001;
			return (float) deltaTime;
		};
		//! Prints end time minus start time.
		void print()
		{
			deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count() * 0.000001;
			Logger::Print("This took " + std::to_string(deltaTime) + " seconds.");
		};

	private:
		std::chrono::steady_clock::time_point startTime;
		std::chrono::steady_clock::time_point endTime;
		double deltaTime;
	};
}
