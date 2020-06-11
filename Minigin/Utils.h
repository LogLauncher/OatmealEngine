#pragma once

namespace OatmealEngine
{
	class Utils
	{
	public:
		inline int RandomInt(int max = 1)
		{
			return rand() % max;
		}
		inline int RandomInt(int min, int max)
		{
			return rand() % (max - min + 1) + min;
		}

		inline float RandomFloat(float max = 1.f)
		{
			return max * (float(rand()) / RAND_MAX);
		}
		inline float RandomFloat(float min, float max)
		{
			auto range = max - min;
			return (range * (float(rand()) / RAND_MAX)) + min;
		}

		template<typename T>
		inline T Lerp(T v0, T v1, float t)
		{
			return (1 - t) * v0 + t * v1;
		}

		template <typename T>
		static int Sign(T val)
		{
			return (T(0) < val) - (val < T(0));
		}
	};
}

