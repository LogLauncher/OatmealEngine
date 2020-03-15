#include "MiniginPCH.h"

#include "TextureComponent.h"
#include "GameObject.h"
#include "Renderer.h"
#include "ResourceManager.h"

dae::TextureComponent::TextureComponent(const std::string& filename)
	: m_Texture{ResourceManager::GetInstance().LoadTexture(filename)}
{}

void dae::TextureComponent::Update(float)
{}

void dae::TextureComponent::Render() const
{
	if (m_Texture != nullptr)
	{
		const auto& pos{GetGameObject().lock()->GetTransform().GetPosition()};
		Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
	}
}

dae::TextureComponent::~TextureComponent()
{
	OutputDebugString("Destructor: TextureComponent\n");

}
