#pragma once
#include <cmath>
namespace Ti
{
	//! Contains basic functions to edit values.
	class Math
	{
	public:
		//! Fast absolute calculation for floats.
		inline static float Absf(float f) { return (f < 0) ? -f : f; };

		//! Fast absolute calculation for ints.																			
		inline static int Absi(int i) { return (i < 0) ? -i : i; };

		static float Clamp(float x, float i, float j) { return x > j ? j : (x < i ? i : x); };
		static float Mod(float x, float y) { return Fract(x / y) * y; };
		static float Floor(float x) { return floor(x); };
		static float Fract(float x) { return x - Floor(x); };
		static float Min(float x, float y) { return x < y ? x : y; };
		static float Max(float x, float y) { return x > y ? x : y; };
		static float Sqrt(float x) { return sqrt(x); };
		static float Ceil(float x) { return floor(x) == x ? x : floor(x) + 1 * (x < 0 ? -1 : 1); };

	};
}