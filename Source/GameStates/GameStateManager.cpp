#include "GameStateManager.h"

namespace sus::states
{
	void GameStateManager::update() noexcept
	{
		assert(!gameStates.empty() && "Cannot update empty game state manager.");

		for (auto &gameState : gameStates)
			gameState->update();

		if (removeIndex)
		{
			gameStates.erase(gameStates.begin() + *removeIndex);
			removeIndex.reset();
		}
	}

	void GameStateManager::render() const noexcept
	{
		assert(!gameStates.empty() && "Cannot render empty game state manager.");

		for (auto &gameState : gameStates)
			gameState->render();
		if (overlayIndex)
			gameStates[*overlayIndex]->render();
	}
}
