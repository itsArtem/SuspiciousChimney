#pragma once

#include "Entity.h"
#include "../Graphics/Animation.h"
#include "../Game.h"

#include <SDL_render.h>
#include <SDL_rect.h>

namespace sus::scene
{
	class Camera;
}

namespace sus::entities
{
	class Spikes final : public Entity
	{
	public:
		Spikes(const SDL_FPoint &pos, SDL_Texture *texture, const SDL_Rect &src, const scene::Camera &camera) noexcept;

		void render(SDL_Renderer *renderer) const noexcept override
		{
			SDL_RenderCopyF(renderer, texture, &src, &getDestination());
		}

	private:
		SDL_Texture *const texture;
		const SDL_Rect src;
	};

	class CandyCane final : public Entity
	{
	public:
		CandyCane(const SDL_FPoint &pos, SDL_Texture *texture, const SDL_Rect &src, const scene::Camera &camera) noexcept;

		void render(SDL_Renderer *renderer) const noexcept override
		{
			SDL_RenderCopyF(renderer, texture, &src, &getDestination());
		}

	private:
		SDL_Texture *const texture;
		const SDL_Rect src;
	};

	class Tentacle final : public Entity
	{
	public:
		Tentacle(const SDL_FPoint &pos, SDL_Texture *texture, const SDL_Rect &src, const scene::Camera &camera) noexcept;

		void render(SDL_Renderer *renderer) const noexcept override
		{
			SDL_RenderCopyF(renderer, texture, &src, &getDestination());
		}

	private:
		SDL_Texture *const texture;
		const SDL_Rect src;
	};

	class Demon final : public Entity
	{
	public:
		Demon(const SDL_FPoint &pos, const gfx::Animation &animation, const scene::Camera &camera, const Game &game) noexcept;

		void update() noexcept;
		void render(SDL_Renderer *renderer) const noexcept override
		{
			animation.render(renderer, getDestination());
		}

	private:
		gfx::Animation animation;
		const Game &game;
	};

	class Wall final : public Entity
	{
	public:
		Wall(const SDL_FPoint &pos, SDL_Texture *texture, const SDL_Rect &src, const scene::Camera &camera) noexcept;

		void render(SDL_Renderer *renderer) const noexcept override
		{
			SDL_RenderCopyF(renderer, texture, &src, &getDestination());
		}

	private:
		SDL_Texture *const texture;
		const SDL_Rect src;
	};
}