#pragma once

#include "Camera.h"
#include "../Entities/Entitiy.h"

#include <SDL_rect.h>

#include <vector>
#include <memory>

namespace sus
{
	class Game;
}

namespace sus::scene
{
	class Scene final
	{
	public:
		Camera camera;
		std::vector<std::unique_ptr<entities::Entity>> entities;

		Scene(const Game &game) noexcept;

		void update() noexcept;
		void render() const noexcept;

	private:
		const Game &game;
	};
}