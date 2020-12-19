#pragma once

#include "GameState.h"

namespace sus::states
{
	class GameOverState final : public GameState
	{
	public:
		void update() noexcept override;
		void render() const noexcept override;

	private:
	};
}