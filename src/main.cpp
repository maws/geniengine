#include "GeniEngine/Core.hpp"
#include "GeniEngine/World.hpp"

using namespace GeniEngine;

int main()
{
	auto& core = *new GeniEngine::Core{ GeniEngine::Core() };
	core.init();
	core.run();
	return 0;
}
