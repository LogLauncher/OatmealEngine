#pragma once
#include "gtc/constants.hpp"

namespace OatmealEngine
{
	class TransformComponent final
	{
	public:
		//---------
		// Position
		//---------
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
		void SetPosition(int x, int y, int z = 0)
		{
			m_Position.x = float(x);
			m_Position.y = float(y);
			m_Position.z = float(z);
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
		void Translate(int x, int y, int z = 0)
		{
			m_Position.x += float(x);
			m_Position.y += float(y);
			m_Position.z += float(z);
		}
		void Translate(const glm::vec3& position)
		{
			m_Position += position;
		}
		void Translate(const glm::vec2& position)
		{
			Translate(position.x, position.y);
		}

		//---------
		// Rotation
		//---------
		float GetRotation() const
		{
			return m_Rotation;
		}
		void SetRotaion(float angle, bool isEuler = false)
		{
			if (isEuler)
				m_Rotation = angle * (glm::pi<float>() / 180.f);
			else
				m_Rotation = angle;
		}
		void Rotate(float angle, bool isEuler = false)
		{
			if (isEuler)
				m_Rotation += angle * (glm::pi<float>() / 180.f);
			else
				m_Rotation += angle;
		}

		//------
		// Scale
		//------
		const glm::vec2& GetScale() const
		{
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
		void InvertXScale()
		{
			m_Scale.x *= -1;
		}
		void InvertYScale()
		{
			m_Scale.y *= -1;
		}

	private:
		glm::vec3 m_Position{};
		float m_Rotation{};
		glm::vec2 m_Scale{1,1};

	};
}
