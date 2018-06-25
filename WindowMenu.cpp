/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WindowMenu.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcherkas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/23 20:42:08 by bcherkas          #+#    #+#             */
/*   Updated: 2018/06/24 21:22:12 by bcherkas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WindowMenu.hpp"

WindowMenu::WindowMenu()
	: _y(LINES / 4), _x(COLS / 4), _yLen(LINES / 2), _xLen(COLS / 2)
{
	this->_window = newwin(LINES / 2, COLS / 2, LINES / 4, COLS / 4);
	box(this->_window, 0, 0);
	wrefresh(this->_window);
	nodelay(this->_window, true);
    return ;
}

WindowMenu::WindowMenu(int y, int x, int yLen, int xLen)
	: _y(y), _x(x), _yLen(yLen), _xLen(xLen)
{
	this->_window = newwin(y, x, yLen, xLen);
	box(this->_window, 0, 0);
	wrefresh(this->_window);
	nodelay(this->_window, true);
	return ;
}

WindowMenu::WindowMenu(const WindowMenu &other)
{
    (*this) = other;
    return ;
}

WindowMenu::~WindowMenu()
{
	delwin(this->_window);
    return ;
}

/*
** Methods
*/

bool	WindowMenu::enter(WINDOW *other, std::string *menus, int max) const
{
	int		active = 0;
	int		field;
	int		x;
	int		y;

	getmaxyx(this->_window, y, x);
	y /= 2;
	x = x / 2 - 3;
	keypad(this->_window, TRUE);
	keypad(other, false);
	redrawwin(this->_window);
	box(this->_window, 0, 0);
	while (1)
	{
		for (int j = 0; j < max; j++)
		{
			if (j == active)
				wattron(this->_window, A_REVERSE);
			mvwprintw(this->_window, y + j, x, menus[j].c_str());
			if (j == active)
				wattroff(this->_window, A_REVERSE);
		}
		wrefresh(this->_window);
		field = wgetch(this->_window);
		switch (field)
		{
			case KEY_UP:
				active--;
				break ;
			case KEY_DOWN:
				active++;
				break ;
			case ESC:
				active = 0;
				field = 10;
				break ;
			default:
				break ;
		}
		active %= 2;
		active = active < 0 ? 1 : active;
		if (field == 10)
			break ;
	}
	wclear(this->_window);
	keypad(this->_window, FALSE);
	keypad(other, true);
	redrawwin(other);
	wrefresh(other);
	if (active == 0)
		return (true);
	else
		return (false);
}

/*
** Get/Set
*/

WINDOW	*WindowMenu::getWindow(void) const {
	return (this->_window);
}

int		WindowMenu::getYStart(void) const {
	return (this->_y);
}

int		WindowMenu::getXStart(void) const {
	return (this->_x);
}

int		WindowMenu::getYLen(void) const {
	return (this->_yLen);
}

int		WindowMenu::getXLen(void) const {
	return (this->_xLen);
}

/*
** Overloads
*/

WindowMenu &WindowMenu::operator= (const WindowMenu &other)
{
	this->_window = other.getWindow();
	this->_x = other.getXStart();
	this->_y = other.getXStart();
	this->_xLen = other.getXLen();
	this->_yLen = other.getYLen();
    return (*this);
}
