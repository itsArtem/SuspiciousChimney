#pragma once

#include "GameState.h"

namespace sus::states
{
	class CutsceneState final : public GameState
	{
	public:
		void update() noexcept override;
		void render() const noexcept override;
	};
}