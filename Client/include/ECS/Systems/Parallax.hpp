/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-02-14T19:31:43+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-02-15T21:54:30+01:00
 */


#pragma once

#include  "ECS/Manager.hpp"
#include  "ECS/Systems/SystemsPriotity.hpp"
#include  "ECS/Components/Components.hpp"
#include  "ECS/Components/CommonComponents.hpp"

#include	"ResourcesManager.hpp"
#include	"Resources.hpp"
#include	<SFML/System.hpp>
#include	<SFML/Graphics.hpp>

namespace ECS
{
	namespace Systems
	{
	class Parallax : public ECS::System
		{
		public:
			Parallax(ECS::Manager &ecsManager, ResourcesManager&);

			void	updateEntity(float delta, Entity e) override;

		private:
			ResourcesManager		&_resourcesManager;
		};
	}
}
