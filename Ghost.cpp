// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Ghost.cpp                                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: dborysen <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/06/15 17:09:44 by dborysen          #+#    #+#             //
/*   Updated: 2018/06/24 21:09:14 by bcherkas         ###   ########.fr       */
//                                                                            //
// ************************************************************************** //

#include "Ghost.hpp"

Ghost::Ghost()
{
	return ;
}

Ghost::Ghost(WINDOW *win, int xMax, int yMax)
{
	this->_current_window = win;
	this->_xMax = xMax;
	this->_yMax = yMax;
	this->_x = this->_xMax - 4;
	this->_y = this->_getRandomCoord();
	this->_HP = 5;
	this->_damage = 3;
	this->_score_award = 115;
	if (this->_y == 0)
		this->_y = 1;
	wattron(this->_current_window, A_BOLD);
	mvwaddch(this->_current_window, this->_y, this->_x, '<');
	wattroff(this->_current_window, A_BOLD);
	return ;
}

Ghost::Ghost(const Ghost &other) : _xMax(0), _yMax(0)
{
	*this = other;
	return ;
}

Ghost::~Ghost()
{
	return ;
}

int		Ghost::getDamage(int dmg)
{
	if (rand() % 2 && dmg != 100)
		return (0);
	dmg = dmg < 1 ? 1 : dmg;
	this->_HP -= dmg;
	if (this->_HP <= 0)
	{
		mvwaddch(this->_current_window, this->_y, this->_x + 1, ' ');
		this->_x = this->_xMax - 4;
		this->_y = this->_getRandomCoord();
		if (this->_y == 0)
			this->_y = 1;
		this->_HP = 2;
		return (1);
	}
	return (0);
}

int		Ghost::doDamage(void) const
{
	return (this->_damage);
}

void		Ghost::fly(void)
{
	if (this->_x > 1)
	{
		wattron(this->_current_window, A_BOLD);
		mvwaddch(this->_current_window, this->_y, this->_x, '<');
		wattroff(this->_current_window, A_BOLD);
		mvwaddch(this->_current_window, this->_y, this->_x + 1, ' ');
		this->_x--;	
	}
	else if (this->_x == 1)
	{
		mvwaddch(this->_current_window, this->_y, this->_x + 1, ' ');
		this->_x = this->_xMax - 4;
		this->_y = this->_getRandomCoord();
		if (this->_y == 0)
			this->_y = 1;
	}
}

const int	&Ghost::getX(void) const
{
	return (this->_x);
}

const int	&Ghost::getY(void) const
{
	return (this->_y);
}

int			Ghost::_getRandomCoord(void)
{
	return (rand() % LINES - 2);
}

int		Ghost::getScoreAward(void) const
{
	return this->_score_award;
}

Ghost &Ghost::operator= (const Ghost &other)
{
	this->_current_window = other._current_window;
	this->_x = other._x;
	this->_y = other._y;
	this->_xMax = other._xMax;
	this->_yMax = other._yMax;
	return (*this);
}
