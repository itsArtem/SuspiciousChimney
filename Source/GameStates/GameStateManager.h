#pragma once

#include "GameState.h"

#include <vector>
#include <memory>
#include <type_traits>
#include <optional>
#include <cassert>

namespace sus::states
{
	class GameStateManager final
	{
	public:
		using SizeType = std::vector<std::unique_ptr<GameState>>::size_type;

		template<typename T, typename ...Arg>
		void emplaceBack(Arg &&...args) noexcept
		{
			emplaceQueue.emplace_back(std::make_unique<T>(std::forward<Arg>(args)...));
		}

		void setOverlay(std::optional<SizeType> index) noexcept { overlayIndex = index; }

		void remove(SizeType index) noexcept
		{
			assert(index < gameStates.size() && "Index out of bounds!");
			removeQueue.emplace_back(index);
		}

		void popBack() noexcept
		{
			assert(!gameStates.empty() && "Cannot pop back an empty game state.");
			removeQueue.emplace_back(gameStates.size() - 1);
		}

		SizeType getSize() const noexcept { return gameStates.size(); }

		void update() noexcept;
		void render() const noexcept;

	private:
		std::vector<std::unique_ptr<GameState>> gameStates;
		std::vector<std::unique_ptr<GameState>> emplaceQueue;
		std::vector<SizeType> removeQueue;

		std::optional<SizeType> overlayIndex;
	};
}