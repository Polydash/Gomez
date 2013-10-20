#ifndef IRESOURCE_H
#define IRESOURCE_H

enum eResType{ RT_IMG,
			   RESOURCE_NB
			 };

class IResource
{
public :

	virtual ~IResource(){}	
	virtual bool VLoad() = 0;
};

#endif
