#include "Memory.h"

void en::flag_memory_debug()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
}
void en::run_memory_debug()
{
	_CrtDumpMemoryLeaks();
}