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
			gameStates.emplace_back(std::make_unique<T>(std::forward<Arg>(args)...));
		}

		void setOverlay(std::optional<SizeType> index) noexcept { overlayIndex = index; }

		void remove(SizeType index) noexcept
		{
			assert(index < gameStates.size() && "Index out of bounds!");
			removeIndex = index;
		}

		void popBack() noexcept
		{
			assert(!gameStates.empty() && "Cannot pop back an empty game state.");
			removeIndex = gameStates.size() - 1;
		}

		void update() noexcept;
		void render() const noexcept;

	private:
		std::vector<std::unique_ptr<GameState>> gameStates;
		std::optional<SizeType> removeIndex;
		std::optional<SizeType> overlayIndex;
	};
}