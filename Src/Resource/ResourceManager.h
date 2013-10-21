#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <map>
#include <string>

#include "IResource.h"

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
