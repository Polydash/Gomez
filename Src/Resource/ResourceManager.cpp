#include "ResourceManager.h"
#include "GfxResource.h"
#include "../GameStd.h"
#include "../GameApp/SDLApp.h"

ResourceManager* ResourceManager::s_pInstance = NULL;

ResourceManager::ResourceManager()
{
	CreateFilePaths();
}

ResourceManager::~ResourceManager()
{
	Clear();
}

void ResourceManager::Create()
{
	if(s_pInstance)
		ERROR("ResourceManager already created");
	else
		s_pInstance = new ResourceManager;
}

ResourceManager* ResourceManager::Get()
{
	return s_pInstance;
}

void ResourceManager::Destroy()
{
	SAFE_DELETE(s_pInstance);
}

const IResource* ResourceManager::GetResource(const std::string &fileName, eResType resType)
{
	ResourceMap::const_iterator i = m_resources.find(fileName);
	
	if(i != m_resources.end())
		return i->second;

	IResource* pResource = CreateResource(fileName, resType);
	if(!pResource || !pResource->VLoad())
		return NULL;
	
	m_resources.insert(std::make_pair(fileName, pResource));

	return pResource;
}

void ResourceManager::Clear()
{
	ResourceMap::iterator i;
	for(i = m_resources.begin(); i != m_resources.end(); i++)
	{
		delete i->second;
		i->second = NULL;
	}
	
	m_resources.clear();
}

IResource* ResourceManager::CreateResource(const std::string &fileName, eResType resType)
{
	std::string filePath = m_filePaths[resType] + '/' + fileName;
	
	if(resType == RT_IMG)
		return new GfxResource(filePath);
		
	ERROR("Unrecognized Resource type");
	return NULL;
}

void ResourceManager::CreateFilePaths()
{
	m_filePaths[RT_IMG] = g_pApp->GetImgPath();
}
