#pragma once

#include "../Scene/Camera.h"
#include "../Debug.h"

#include <SDL_render.h>
#include <SDL_rect.h>

#include <optional>

namespace sus::entities
{
	enum class ConsumableType
	{
		none, special, health
	};

	class Entity
	{
	public:
		struct Transform final
		{
			SDL_FPoint pos{0.0f, 0.0f};
			const SDL_FPoint size{0.0f, 0.0f};

			SDL_FPoint velocity{0.0f, 0.0f};
			SDL_FPoint friction{0.0f, 0.0f};

			SDL_FRect bounds{0.0f, 0.0f, 0.0f, 0.0f};

			Transform() = default;
			Transform(const SDL_FPoint &pos, const SDL_FPoint &size, const SDL_FPoint &velocity, const SDL_FPoint &friction, const SDL_FRect &bounds) noexcept;
		};

		struct Properties final
		{
			bool despawnOnCollision{false};
			ConsumableType consumable;
			
			std::optional<int> health;
			const int maxHealth{health.value_or(0)};

			Properties() = default;
			Properties(bool despawnOnCollision, ConsumableType consumable, std::optional<int> health) noexcept;
		};

		Transform tf;
		Properties properties;

		bool active{true};

		virtual Entity::~Entity() = default;

		virtual void update() noexcept;
		virtual void render(SDL_Renderer *renderer) const noexcept = 0;
#if SUS_ENTITIES_SHOW_HITBOX
		void debugRender(SDL_Renderer *renderer) const noexcept;
#endif

		SDL_FRect getDestination() const noexcept
		{
			return {tf.pos.x - camera.pos.x, tf.pos.y - camera.pos.y, tf.size.x, tf.size.y};
		}

	protected:
		Entity(const Transform &tf, Properties properties, const scene::Camera &camera) noexcept;

		Entity(const Entity &other) = default;
		Entity(Entity &&other) = default;
		
		Entity &operator =(const Entity &other) = default;
		Entity &operator =(Entity && other) = default;

		virtual void remove() noexcept { active = false; }

	private:
		const scene::Camera &camera;
	};
}