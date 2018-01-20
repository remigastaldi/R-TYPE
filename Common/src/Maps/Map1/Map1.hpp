#include "IMap.hpp"

class Map1 : public IMap
{
public:
	Map1(std::string name, std::pair<int, int> level);
	~Map1();

	const std::string						&getName() const;
	const std::pair<int, int>		&getNeededLevel() const;

	void 												update(const float time, ECS::Manager &ecs, EventManager::Manager &event);

private:
	std::string									_name;
	std::pair<int, int>					_level;
};
