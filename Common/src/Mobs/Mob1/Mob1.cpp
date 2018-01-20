#include "Mob1.hpp"

Mob1::Mob1(const std::string &name, int difficulty)
{
	_name = name;
	_difficulty = difficulty;
}

Mob1::~Mob1() {}

const std::string		&Mob1::getName() const
{
	return (_name);
}

const int 					Mob1::getDifficulty()
{
	return (_difficulty);
}

void 								Mob1::update(const float time, ECS::Manager &ecs, EventManager::Manager &event)
{
	(void)time;
	(void)ecs;
	(void)event;
}
