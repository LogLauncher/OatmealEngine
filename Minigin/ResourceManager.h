#pragma once
#include "Singleton.h"

#include <map>

namespace OatmealEngine
{
	class Texture2D;
	class Font;

	class ResourceManager final : public Singleton<ResourceManager>
	{
	public:
		void Init(const std::string& data);

		bool AddTexture(const std::string& id, const std::string& file);
		std::weak_ptr<Texture2D> LoadTexture(const std::string& id) const;

		bool AddFont(const std::string& id, const std::string& file, unsigned int size);
		std::weak_ptr<Font> LoadFont(const std::string& id) const;

	private:
		friend class Singleton<ResourceManager>;
		ResourceManager() = default;
		
		std::string m_DataPath;
		std::map<std::string, std::shared_ptr<Texture2D>> m_pTextures;
		std::map<std::string, std::shared_ptr<Font>> m_pFonts;

	};
}
