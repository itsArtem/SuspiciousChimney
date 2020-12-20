#pragma once

#include "Entity.h"
#include "../Graphics/Animation.h"
#include "../Game.h"

#include <SDL_render.h>
#include <SDL_rect.h>

namespace sus
{
	class Game;
}

namespace sus::scene
{
	class Camera;
}

namespace sus::states
{
	class GameplayState;
}

namespace sus::entities
{
	class Hostile : public Entity
	{
	public:
		virtual ~Hostile() = default;

		void remove() noexcept;

	protected:
		Hostile(const Transform &tf, Properties properties, const scene::Camera &camera, states::GameplayState &gameplay) noexcept;

		Hostile(const Hostile &hostile) = default;
		Hostile(Hostile &&hostile) = default;
		
		Hostile &operator =(const Hostile &hostile) = default;
		Hostile &operator =(Hostile &&hostile) = default;

	private:
		states::GameplayState &gameplay;
	};

	class Spikes final : public Hostile
	{
	public:
		Spikes(const SDL_FPoint &pos, SDL_Texture *texture, const SDL_Rect &src, const scene::Camera &camera, states::GameplayState &gameplay) noexcept;

		void render(SDL_Renderer *renderer) const noexcept override
		{
			SDL_RenderCopyF(renderer, texture, &src, &getDestination());
		}

	private:
		SDL_Texture *const texture;
		const SDL_Rect src;
	};

	class CandyCane final : public Hostile
	{
	public:
		CandyCane(const SDL_FPoint &pos, SDL_Texture *texture, const SDL_Rect &src, const scene::Camera &camera, states::GameplayState &gameplay) noexcept;

		void render(SDL_Renderer *renderer) const noexcept override
		{
			SDL_RenderCopyF(renderer, texture, &src, &getDestination());
		}

	private:
		SDL_Texture *const texture;
		const SDL_Rect src;
	};

	class TentacleMonster final : public Hostile
	{
	public:
		TentacleMonster(const SDL_FPoint &pos, const gfx::Animation &animation, const scene::Camera &camera, states::GameplayState &gameplay, const Game &game) noexcept;

		void update() noexcept;
		void render(SDL_Renderer *renderer) const noexcept override
		{
			animation.render(renderer, getDestination());
		}

	private:
		gfx::Animation animation;
		const Game &game;
	};

	class Demon final : public Hostile
	{
	public:
		Demon(const SDL_FPoint &pos, const gfx::Animation &animation, const scene::Camera &camera, states::GameplayState &gameplay, const Game &game) noexcept;

		void update() noexcept;
		void render(SDL_Renderer *renderer) const noexcept override
		{
			animation.render(renderer, getDestination());
		}

	private:
		gfx::Animation animation;
		const Game &game;

		float move{0.0f};
	};

	class Wall final : public Hostile
	{
	public:
		Wall(const SDL_FPoint &pos, SDL_Texture *texture, const SDL_Rect &src, const scene::Camera &camera, states::GameplayState &gameplay) noexcept;

		void render(SDL_Renderer *renderer) const noexcept override
		{
			SDL_RenderCopyF(renderer, texture, &src, &getDestination());
		}

	private:
		SDL_Texture *const texture;
		const SDL_Rect src;
	};
}