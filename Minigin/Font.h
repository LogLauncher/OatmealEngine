#pragma once

struct _TTF_Font;
namespace OatmealEngine
{
	/**
	 * Simple RAII wrapper for an _TTF_Font
	 */
	class Font
	{
	public:
		_TTF_Font* GetFont() const;
		explicit Font(const std::string& fullPath, unsigned int size);
		~Font();
		DEL_ROF(Font);

	private:
		_TTF_Font* m_Font;
		unsigned int m_Size;
	};
}
