//
// oscompat.hpp
// ~~~~~~~~~~~~
//
// Copyright (c) 2011-2011 Richard J. Whitehouse (richard at richardwhiuk dot com)
//

#include "oscompat.hpp"

#ifndef HYDRA_LINUX

int eaccess(const char *path, int amode)
{
	return access(path, amode);
}

#endif



