#ifndef IRESOURCE_H
#define IRESOURCE_H

/**
 * \file IResource.h 
 * \brief Resource interface
 */

/// Enumeration defining every Resource type
enum eResType{ RT_IMG,
			   RT_FONT,
			   RESOURCE_NB
			 };

/**
 * \class IResource 
 * \brief Resource interface
 * 
 * Resource interface needed by ResourceManager.
 */
class IResource
{
public :

	virtual ~IResource(){}	
	virtual bool VLoad() = 0;
};

#endif
