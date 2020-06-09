#pragma once

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
		void SetPosition(const glm::vec3& position)
		{
			m_Position = position;
		}
		void Translate(float x, float y, float z = 0)
		{
			m_Position.x += x;
			m_Position.y += y;
			m_Position.z += z;
		}
		void Translate(const glm::vec3& position)
		{
			m_Position += position;
		}
		void Translate(const glm::vec2& position)
		{
			Translate(position.x, position.y);
		}

		const glm::vec2& GetScale() const {
			return m_Scale;
		}
		void SetScale(const glm::vec2& scale)
		{
			m_Scale = scale;
		}
		void SetScale(float x, float y)
		{
			m_Scale.x = x;
			m_Scale.y = y;
		}

	private:
		glm::vec3 m_Position;
		glm::vec2 m_Scale{1,1};

	};
}
