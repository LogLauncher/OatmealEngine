#include "MiniginPCH.h"
#include "TextureComponent.h"

#include "GameObject.h"
#include "ResourceManager.h"
#include "RenderComponent.h"

OatmealEngine::TextureComponent::TextureComponent(const std::string& filename)
	: m_pTexture{ResourceManager::GetInstance().LoadTexture(filename)}
{}

void OatmealEngine::TextureComponent::Awake()
{
	auto pRenderComponent{std::make_shared<RenderComponent>()};
	pRenderComponent->SetTexture(m_pTexture);
	GetGameObject().lock()->AddComponent(pRenderComponent);
}
