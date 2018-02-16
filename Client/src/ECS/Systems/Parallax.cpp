/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-02-15T00:58:40+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-02-15T22:48:27+01:00
 */


#include "ECS/Systems/Parallax.hpp"

namespace ECS
{
	namespace Systems
	{
		Parallax::Parallax(ECS::Manager &ecsManager, ResourcesManager &resourcesManager)
		: System(PARALLAX_PRIORITY, {ecsManager.GetTypeID<ECS::Components::Parallax>(), ecsManager.GetTypeID<ECS::Components::Position>(), ecsManager.GetTypeID<ECS::Components::Drawable>()}, ecsManager),
			_resourcesManager(resourcesManager)
		{}

		void	Parallax::updateEntity(float delta, Entity e)
		{
			(void) delta;
			std::shared_ptr<ECS::Components::Position> position = getManager().getComponent<ECS::Components::Position>(e);
			std::shared_ptr<ECS::Components::Parallax> parallax = getManager().getComponent<ECS::Components::Parallax>(e);
			std::shared_ptr<ECS::Components::Drawable> drawable = getManager().getComponent<ECS::Components::Drawable>(e);

			sf::Sprite &sprite = _resourcesManager.getContent<Sprite>(drawable->sprite);

			if (position->x <=  0 - sprite.getGlobalBounds().width)
			{
				position->x = 1920;
				position->y = 0;

				return;
			}

			if (parallax->xDirection != 0)
			{
				position->x = position->x + (parallax->xDirection * parallax->speed);
				//position->x += (parallax->xDirection * parallax->speed);
			}
			if (parallax->yDirection != 0)
			{
				position->y = position->y + (parallax->yDirection * parallax->speed);
				// position->y += (parallax->yDirection * parallax->speed);
			}
		}
	}
}
