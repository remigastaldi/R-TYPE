#include "Map1.hpp"

//Map1::Map1(std::string name, std::pair<int, int> level)
//{
//	_name = name;
//	_level = level;
//}

Map1::~Map1() {}

const std::string						&Map1::getName() const
{
	return (_name);
}

const std::pair<int, int>		&Map1::getNeededLevel() const
{
	return (_level);
}

void 												update(const float time, ECS::Manager &ecs, EventManager::Manager &event)
{
	(void)time;
	(void)ecs;
	(void)event;
}
