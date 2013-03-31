//
// oscompat.hpp
// ~~~~~~~~~~~~
//
// Copyright (c) 2011-2011 Richard J. Whitehouse (richard at richardwhiuk dot com)
//

#if defined(__unix__) || (defined(__APPLE__) && defined(__MACH__))
#include <sys/param.h>
#if defined(BSD)
#define HYDRA_BSD
#endif
#endif

#ifndef HYDRA_BSD
#define HYDRA_LINUX
#endif

#ifdef HYDRA_LINUX
#include <sys/sysinfo.h>
#else
#include <sys/sysctl.h>
#endif

#include <unistd.h>

#ifndef HYDRA_LINUX

int eaccess(const char *path, int amode);

#endif


