#include "CutsceneState.h"

#include <iostream>

namespace sus::states
{
	void states::CutsceneState::update() noexcept
	{
		std::cout << "Hello from cutscene state!\n";
	}

	void states::CutsceneState::render() const noexcept
	{
	}
}
