#pragma once
namespace OatmealEngine
{
	template <typename T>
	class Singleton
	{
	public:
		static T& GetInstance()
		{
			static T instance{};
			return instance;
		}

		virtual ~Singleton() = default;
		DEL_ROF(Singleton);

	protected:
		Singleton() = default;
	};
}