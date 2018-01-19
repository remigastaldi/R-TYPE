/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-01-18T14:54:03+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-01-18T23:28:53+01:00
 */


#pragma once

#include  "GUIElements.hpp"

namespace GUI
{
  class Manager
	{
	public:
		explicit Manager(sf::RenderWindow &win)
			:	_win(win),
				_elements()
			{}

		void update(float delta)
		{
			//TODO use delta
			(void) delta;
			for (auto & it : _elements)
			{
				it.second->update(_win);
			}
		}

		template<typename S, typename ... Args>
		void addElement(const std::string &name, Args&&... args) {
			_elements.emplace(name, std::make_shared<S>(std::forward<Args>(args)...));
		}

		template<typename S>
		std::shared_ptr<S> getElement(const std::string &name)	{
			return (_elements[name]);
		}

		bool release(const std::string &name)
		{
			auto it = _elements.find(name);
	    return (it == _elements.end() ? false : true);
		}

		void releaseAll(void)
		{
			_elements.clear();
		}

	private:
		sf::RenderWindow &_win;
		std::unordered_map<std::string, std::shared_ptr<Element>>	_elements;
	};
}
