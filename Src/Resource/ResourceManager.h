#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

/**
 * \file ResourceManager.h 
 * \brief Manager allowing resources to be loaded
 */

#include <map>
#include <string>

#include "IResource.h"

/**
 * \class ResourceManager 
 * \brief Manager allowing resources to be loaded
 * 
 * This Manager allows resources to be loaded in a ResourceMap. It is
 * convenient to keep resources in RAM and avoid multiple loadings. 
 */
class ResourceManager
{	
private :

	static ResourceManager *s_pInstance;

	typedef std::map<std::string, IResource*> ResourceMap;
	
	ResourceMap m_resources;
	std::string m_filePaths[RESOURCE_NB];

public :
	
	static void Create();
	static ResourceManager* Get();
	static void Destroy();
	
	const IResource* GetResource(const std::string &fileName, eResType resType);
	void Clear();
	
private :

	
	ResourceManager();
	~ResourceManager();

	IResource* CreateResource(const std::string &fileName, eResType resType);
	void CreateFilePaths();
};

#endif
