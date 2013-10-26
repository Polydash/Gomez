#include "FontResource.h"
#include "../GameStd.h"

FontResource::FontResource(const std::string &fileName):
m_pFont(NULL),
m_fileName(fileName)
{
}

FontResource::~FontResource()
{
	if(m_pFont)
	{
		TTF_CloseFont(m_pFont);
		m_pFont = NULL;
	}
}

bool FontResource::VLoad()
{
	if(m_pFont)
	{
		ERROR("FontResource \"" << m_fileName << "\" already loaded");
		return false;
	}
	
	m_pFont = TTF_OpenFont(m_fileName.c_str(), 72);
	if(!m_pFont)
	{
		ERROR("Failed to load \"" << m_fileName << "\"");
		return false;
	}
	
	return true;
}
