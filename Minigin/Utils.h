#pragma once

namespace OatmealEngine
{
	class Utils
	{
	public:
		static inline int RandomInt(int max = 1)
		{
			return rand() % max;
		}
		static inline int RandomInt(int min, int max)
		{
			return rand() % (max - min + 1) + min;
		}

		static inline float RandomFloat(float max = 1.f)
		{
			return max * (float(rand()) / RAND_MAX);
		}
		static inline float RandomFloat(float min, float max)
		{
			auto range = max - min;
			return (range * (float(rand()) / RAND_MAX)) + min;
		}

		template<typename T>
		static inline T Lerp(T v0, T v1, float t)
		{
			return (1 - t) * v0 + t * v1;
		}

		template <typename T>
		static inline int Sign(T val)
		{
			return (T(0) < val) - (val < T(0)) > 0 ? 1 : -1;
		}
	};
}

