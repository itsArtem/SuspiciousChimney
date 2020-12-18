#include "Entitiy.h"

namespace sus::entities
{
	void Entity::update() noexcept
	{
		pos.x += velocity.x;
		pos.y += velocity.y;

		if (velocity.x < 0.0f)
		{
			velocity.x += friction.x;
			if (velocity.x > 0.0f)
				velocity.x = 0.0f;
		}

		if (velocity.x > 0.0f)
		{
			velocity.x -= friction.x;
			if (velocity.x < 0.0f)
				velocity.x = 0.0f;
		}

		if (velocity.y < 0.0f)
		{
			velocity.y += friction.y;
			if (velocity.y > 0.0f)
				velocity.y = 0.0f;
		}

		if (velocity.y > 0.0f)
		{
			velocity.y -= friction.y;
			if (velocity.y < 0.0f)
				velocity.y = 0.0f;
		}
	}

#if SUS_ENTITIES_SHOW_HITBOX
	void Entity::debugRender(SDL_Renderer *renderer) const noexcept
	{
		const SDL_FRect hitbox{pos.x + bounds.x - camera.pos.x, pos.y + bounds.y - camera.pos.y, bounds.w, bounds.h};
		
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		SDL_RenderDrawRectF(renderer, &hitbox);
	}
#endif

	Entity::Entity(const SDL_FPoint &pos, const SDL_FPoint &size, const scene::Camera &camera) noexcept
		: pos{pos},
		size{size},
		camera{camera}
	{
	}
	
	Entity::Entity(const SDL_FPoint &pos, const SDL_FPoint &size, const SDL_FPoint &velocity, const SDL_FPoint &friction, const SDL_FRect &bounds, const scene::Camera &camera) noexcept
		: pos{pos},
		size{size},
		velocity{velocity},
		friction{friction},
		bounds{bounds},
		camera{camera}
	{
	}
}