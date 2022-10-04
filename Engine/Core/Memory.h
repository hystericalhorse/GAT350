#ifndef _MEMORY_H
#define _MEMORY_H

// C++ DEBUGGING UTILS
#include <stdlib.h>
#include <crtdbg.h>

#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
// Use _NORMAL_BLOCK
#define new new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the allocations to be of _CLIENT_BLOCK type
#else
#define new new
#endif // _DEBUG

namespace en
{
	void flag_memory_debug();
	void run_memory_debug();
}

#endif // _MEMORY_H