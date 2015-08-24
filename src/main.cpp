#include "GeniEngine/Core.h"
#include "GeniEngine/World.h"

using namespace GeniEngine;

int main()
{
	auto& core = *new GeniEngine::Core{ GeniEngine::Core() };
	core.init();
	core.run();
	return 0;
}
