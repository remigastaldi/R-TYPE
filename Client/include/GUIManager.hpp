/**
 * @Author: Remi Gastaldi <gastal_r>
 * @Date:   2018-01-18T14:54:03+01:00
 * @Last modified by:   gastal_r
 * @Last modified time: 2018-01-19T23:47:18+01:00
 */


#pragma once

#include  "GUIElements.hpp"
#include <iostream>
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
			for (auto & it : _zIndex)
			{
        _elements[it]->update(_win);
			}
		}

		template<typename S, typename ... Args>
		void addElement(const std::string &name, Args&&... args)
    {
      _zIndex.emplace_back(name);
			_elements.emplace(name, std::make_shared<S>(std::forward<Args>(args)...));
		}

		template<typename S>
		std::shared_ptr<S> getElement(const std::string &name)	{
			return (_elements[name]);
		}

    template<typename C, typename S>
		void centerElementWithAnOther(const std::string &element1, const std::string &element2)
		{
      std::shared_ptr<C> firstElement(getElement<C>("element1"));
      std::shared_ptr<S> secondElement(getElement<S>("element2"));

      //TODO center second element with first
		}

		bool release(const std::string &name)
		{
      auto it = std::find(_zIndex.begin(), _zIndex.end(), name);
      _zIndex.erase(it);
      int nb = _elements.erase(name);
	    return (nb == 0 ? false : true);
		}

		void releaseAll(void)
		{
			_elements.clear();
      _zIndex.clear();
		}

	private:
		sf::RenderWindow &_win;
    std::vector<std::string>  _zIndex;
		std::unordered_map<std::string, std::shared_ptr<Element>>	_elements;
	};
}
