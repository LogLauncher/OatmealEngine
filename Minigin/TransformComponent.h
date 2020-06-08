#pragma once
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
#pragma warning(pop)

namespace OatmealEngine
{
	class TransformComponent final
	{
	public:
		const glm::vec3& GetPosition() const
		{
			return m_Position; 
		}
		void SetPosition(float x, float y, float z = 0)
		{
			m_Position.x = x;
			m_Position.y = y;
			m_Position.z = z;
		}

	private:
		glm::vec3 m_Position;

	};
}
