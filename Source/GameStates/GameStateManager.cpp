#include "GameStateManager.h"

#include <iterator>
#include <utility>

namespace sus::states
{
	void GameStateManager::update() noexcept
	{
		for (auto &it{removeQueue.begin()}; it != removeQueue.end();)
		{
			gameStates.erase(gameStates.begin() + *it);
			it = removeQueue.erase(it);
		}

		for (auto &it{emplaceQueue.begin()}; it != emplaceQueue.end();)
		{
			gameStates.emplace_back(std::move(*it));
			it = emplaceQueue.erase(it);
		}

		assert(!gameStates.empty() && "Cannot update empty game state manager.");
		gameStates.back()->update();
	}

	void GameStateManager::render() const noexcept
	{
		assert(!gameStates.empty() && "Cannot render empty game state manager.");

		gameStates.back()->render();
		if (overlayIndex)
			gameStates[*overlayIndex]->render();
	}
}
