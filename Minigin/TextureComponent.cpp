#include "MiniginPCH.h"
#include "TextureComponent.h"

#include "Renderer.h"
#include "GameObject.h"
#include "ResourceManager.h"

OatmealEngine::TextureComponent::TextureComponent(const std::string& filename)
	: m_Texture{ResourceManager::GetInstance().LoadTexture(filename)}
{}

void OatmealEngine::TextureComponent::Render() const
{
	if (m_Texture != nullptr)
	{
		const auto& pos{GetGameObject().lock()->GetTransform().GetPosition()};
		Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
	}
}

OatmealEngine::TextureComponent::~TextureComponent()
{
	OutputDebugString("Destructor: TextureComponent\n");

}
