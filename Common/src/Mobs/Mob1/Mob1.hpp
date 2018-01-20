#include "IMob.hpp"

class Mob1 : public IMob
{
public:
	Mob1(const std::string &name, int difficulty);
	~Mob1();

	const int 					getDifficulty();
	const std::string		&getName() const;

	void 								update(const float time, ECS::Manager &ecs, EventManager::Manager &event);

private:
	int 								_difficulty;
	std::string					_name;
};
