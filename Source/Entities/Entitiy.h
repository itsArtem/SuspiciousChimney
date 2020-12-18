#pragma once

#include "../Scene/Camera.h"
#include "../Debug.h"

#include <SDL_render.h>
#include <SDL_rect.h>

namespace sus::entities
{
	class Entity
	{
	public:
		SDL_FPoint pos;
		const SDL_FPoint size;

		SDL_FPoint velocity{0.0f, 0.0f};
		SDL_FPoint friction{0.0f, 0.0f};

		SDL_FRect bounds{0.0f, 0.0f, 0.0f, 0.0f};

		virtual Entity::~Entity() = default;

		virtual void update() noexcept;
		virtual void render(SDL_Renderer *renderer) const noexcept = 0;
#if SUS_ENTITIES_SHOW_HITBOX
		void debugRender(SDL_Renderer *renderer) const noexcept;
#endif

		SDL_FRect getDestination() const noexcept
		{
			return {pos.x - camera.pos.x, pos.y - camera.pos.y, size.x, size.y};
		}

	protected:
		Entity(const SDL_FPoint &pos, const SDL_FPoint &size, const scene::Camera &camera) noexcept;
		Entity(const SDL_FPoint &pos, const SDL_FPoint &size, const SDL_FPoint &velocity, const SDL_FPoint &friction, const SDL_FRect &bounds, const scene::Camera &camera) noexcept;

		Entity(const Entity &other) = default;
		Entity(Entity &&other) = default;
		
		Entity &operator =(const Entity &other) = default;
		Entity &operator =(Entity && other) = default;

	private:
		const scene::Camera &camera;
	};
}