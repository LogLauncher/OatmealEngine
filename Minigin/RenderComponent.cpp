#include "MiniginPCH.h"
#include "RenderComponent.h"

#include "Texture2D.h"

void OatmealEngine::RenderComponent::SetTexture(std::weak_ptr<Texture2D> texture)
{
	m_Texture = texture;
}

void OatmealEngine::RenderComponent::Render() const
{
	if (!m_Texture.expired())
	{
		const auto& transform{GetTransform()};
		const auto& pos{transform.GetPosition()};
		const auto& scale{transform.GetScale()};
		const auto& size{m_Texture.lock()->GetSize()};
		Renderer::GetInstance().RenderTexture(*m_Texture.lock(), pos.x, pos.y, size.x * scale.x, size.y * scale.y, transform.GetRotation());
	}
}
