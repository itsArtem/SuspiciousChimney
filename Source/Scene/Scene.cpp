#include "Scene.h"
#include "../Game.h"
#include "../Debug.h"

#include <iterator>

namespace sus::scene
{
	Scene::Scene(const Game &game) noexcept
		: game{game},
		camera{game}
	{
	}
	
	void Scene::update() noexcept
	{
		for (auto it{entities.begin()}; it != entities.end();)
		{
			it->get()->update();
			if (!it->get()->active)
				it = entities.erase(it);
			else
				++it;
		}
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
