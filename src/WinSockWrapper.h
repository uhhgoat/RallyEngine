//-----------------------------------------------------------------------------
// Copyright Ed Keenan 2017
// Real-Time Networking
//----------------------------------------------------------------------------- 

#ifndef WINDOWS_WRAPPER_H
#define WINDOWS_WRAPPER_H

// Needs to be included because winsock2.h sucks for advanced warnings
#pragma warning( push )
#pragma warning( disable : 4820 )
#pragma warning( disable : 4668 )
#pragma warning( disable : 4005 )

#include <winsock2.h>

#pragma warning( pop ) 

#endif
