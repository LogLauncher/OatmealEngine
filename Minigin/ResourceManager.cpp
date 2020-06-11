#include "MiniginPCH.h"
#include "ResourceManager.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "Font.h"
#include "Renderer.h"
#include "Texture2D.h"

void OatmealEngine::ResourceManager::Init(const std::string& dataPath)
{
	m_DataPath = dataPath;

	// load support for png and jpg, this takes a while!

	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) 
	{
		throw std::runtime_error(std::string("Failed to load support for png's: ") + SDL_GetError());
	}

	if ((IMG_Init(IMG_INIT_JPG) & IMG_INIT_JPG) != IMG_INIT_JPG) 
	{
		throw std::runtime_error(std::string("Failed to load support for jpg's: ") + SDL_GetError());
	}

	if (TTF_Init() != 0) 
	{
		throw std::runtime_error(std::string("Failed to load support for fonts: ") + SDL_GetError());
	}
}

bool OatmealEngine::ResourceManager::AddTexture(const std::string& id, const std::string& file)
{
	const auto fullPath = m_DataPath + file;
	auto texture = IMG_LoadTexture(Renderer::GetInstance().GetSDLRenderer(), fullPath.c_str());
	if (texture == nullptr)
	{
		throw std::runtime_error(std::string("Failed to load texture: ") + SDL_GetError());
	}

	if (m_pTextures.find(id) != m_pTextures.end())
		return false;

	m_pTextures.insert(std::make_pair(id, std::make_shared<Texture2D>(texture)));
	return true;
}
std::weak_ptr<OatmealEngine::Texture2D> OatmealEngine::ResourceManager::LoadTexture(const std::string& id) const
{
	auto it{m_pTextures.find(id)};
	if (it == m_pTextures.end())
		return {};

	return (*it).second;
}

bool OatmealEngine::ResourceManager::AddFont(const std::string& id, const std::string& file, unsigned int size)
{
	if (m_pFonts.find(id) != m_pFonts.end())
		return false;

	m_pFonts.insert(std::make_pair(id, std::make_shared<Font>(m_DataPath + file, size)));
	return true;

}
std::weak_ptr<OatmealEngine::Font> OatmealEngine::ResourceManager::LoadFont(const std::string& id) const
{
	auto it{m_pFonts.find(id)};
	if (it == m_pFonts.end())
		return {};

	return (*it).second;
}
