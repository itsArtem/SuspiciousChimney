#include "Scene.h"
#include "../Game.h"
#include "../Debug.h"

namespace sus::scene
{
	Scene::Scene(const Game &game) noexcept
		: game{game},
		camera{game}
	{
	}
	
	void Scene::update() noexcept
	{
		for (auto &entity : entities)
			entity->update();
	}

	void Scene::render() const noexcept
	{
		for (const auto &entity : entities)
		{
			entity->render(game.getRenderer());
#if SUS_ENTITIES_SHOW_HITBOX
			entity->debugRender(game.getRenderer());
#endif
		}
	}
}
