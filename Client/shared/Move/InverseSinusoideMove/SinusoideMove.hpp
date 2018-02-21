/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-02-16T15:34:14+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-02-19T14:59:45+01:00
 */


#pragma once

#include "IMove.hpp"

class SinusoideMove : public IMove
{
  private:
    GameEngine::GameManagers &_gameManagers;
    ECS::Manager &_ecs;
    EventManager::Manager &_event;
    LibLoader &_loader;

    ECS::Entity _owner;

  public:
    SinusoideMove(GameEngine::GameManagers &gameManagers, ECS::Entity entity, int direction, int speed);
    ~SinusoideMove() override;

    void update() override;
    ECS::Entity getID(void) const;
};


#ifdef WIN32
extern "C" 
{
	char const  __declspec(dllexport) *getName()
	{
		return "InverseSinusoideMove";
	}

	IMove __declspec(dllexport) *getSymbol(GameEngine::GameManagers &gameManagers, ECS::Entity parent, int direction, int speed)
	{
		return new SinusoideMove(gameManagers, parent, direction, speed);
	}
}
#else

extern "C" char const * getName()
{
  return "InverseSinusoideMove";
}

extern "C" IMove *getSymbol(GameEngine::GameManagers &gameManagers, ECS::Entity parent, int direction, int speed)
{
  return new SinusoideMove(gameManagers, parent, direction, speed);
}

#endif
