#include "Entity.h"

namespace sus::entities
{
	Entity::Transform::Transform(const SDL_FPoint &pos, const SDL_FPoint &size, const SDL_FPoint &velocity, const SDL_FPoint &friction, const SDL_FRect &bounds) noexcept
		: pos{pos},
		size{size},
		velocity{velocity},
		friction{friction},
		bounds{bounds}
	{
	}

	Entity::Properties::Properties(bool despawnOnCollision, ConsumableType consumable, std::optional<int> health) noexcept
		: despawnOnCollision{despawnOnCollision},
		consumable{consumable},
		health{health}
	{
	}
	
	void Entity::update() noexcept
	{
		tf.pos.x += tf.velocity.x;
		tf.pos.y += tf.velocity.y;

		if (tf.velocity.x < 0.0f)
		{
			tf.velocity.x += tf.friction.x;
			if (tf.velocity.x > 0.0f)
				tf.velocity.x = 0.0f;
		}

		if (tf.velocity.x > 0.0f)
		{
			tf.velocity.x -= tf.friction.x;
			if (tf.velocity.x < 0.0f)
				tf.velocity.x = 0.0f;
		}

		if (tf.velocity.y < 0.0f)
		{
			tf.velocity.y += tf.friction.y;
			if (tf.velocity.y > 0.0f)
				tf.velocity.y = 0.0f;
		}

		if (tf.velocity.y > 0.0f)
		{
			tf.velocity.y -= tf.friction.y;
			if (tf.velocity.y < 0.0f)
				tf.velocity.y = 0.0f;
		}
		
		if (properties.health && *properties.health <= 0)
			remove();
	}

#if SUS_ENTITIES_SHOW_HITBOX
	void Entity::debugRender(SDL_Renderer *renderer) const noexcept
	{
		const SDL_FRect hitbox{tf.pos.x + tf.bounds.x - camera.pos.x, tf.pos.y + tf.bounds.y - camera.pos.y, tf.bounds.w, tf.bounds.h};
		
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		SDL_RenderDrawRectF(renderer, &hitbox);
	}
#endif

	Entity::Entity(const Transform &tf, Properties properties, const scene::Camera &camera) noexcept
		: tf{tf},
		properties{properties},
		camera{camera}
	{
	}
}