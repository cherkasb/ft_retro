// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Bullet.cpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: dborysen <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/06/15 16:19:05 by dborysen          #+#    #+#             //
/*   Updated: 2018/06/24 16:58:30 by bcherkas         ###   ########.fr       */
//                                                                            //
// ************************************************************************** //

#include "Bullet.hpp"

Bullet::Bullet()
{
	return ;
}

Bullet::Bullet(WINDOW *win, int heroX, int heroY, int xMax, int yMax, Player *player)
{
	this->_player = player;
	this->_current_window = win;
	this->_x = heroX + 2;
	this->_y = heroY;
	this->_xMax = xMax;
	this->_yMax = yMax;
	this->_stillInFly = TRUE;
	return ;
}

Bullet::Bullet(const Bullet &other)
{
	*this = other;
	return ;
}

Bullet::~Bullet()
{
	return ;
}

void	Bullet::hitSomeone(void)
{
	this->_stillInFly = FALSE;
	mvwaddch(this->_current_window, this->_y, this->_x - 1, ' ');
	return ; 
}

const bool	&Bullet::isInFly(void) const
{
	return (this->_stillInFly);
}

Player		*Bullet::getPlayer(void) const
{
	return (this->_player);
}

int			Bullet::getY(void) const
{
	return (this->_y);
}

int			Bullet::getX(void) const
{
	return (this->_x);
}

void		Bullet::changeLocation(void)
{
	if (this->_x <= this->_xMax - 2 && this->_stillInFly == TRUE)
	{
		mvwaddch(this->_current_window, this->_y, this->_x, '-');
		mvwaddch(this->_current_window, this->_y, this->_x - 1, ' ');
		this->_x++;	
	}
	else if (this->_x > this->_xMax - 2)
	{
		this->_stillInFly = FALSE;
		mvwaddch(this->_current_window, this->_y, this->_x - 1, ' ');
	}
}

Bullet &Bullet::operator= (const Bullet &other)
{
	this->_stillInFly = other._stillInFly;
	this->_x = other._x;
	this->_y = other._y;
	this->_xMax = other._xMax;
	this->_yMax = other._yMax;
	return (*this);
}
