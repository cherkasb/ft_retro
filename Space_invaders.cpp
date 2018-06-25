// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Space_invaders.cpp                                 :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: dborysen <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/06/15 14:32:47 by dborysen          #+#    #+#             //
/*   Updated: 2018/06/24 21:20:04 by bcherkas         ###   ########.fr       */
//                                                                            //
// ************************************************************************** //

#include "Space_invaders.hpp"

Space_invaders::Space_invaders() : _yStart(0), _xStart(0)
{
	this->_ship = nullptr;
	this->_multiplay = 0;
	return ;
}

Space_invaders::Space_invaders(const Space_invaders &other)
{
	(*this) = other;
	return ;
}

Space_invaders::~Space_invaders()
{
	return ;
}

/*
** Methods
*/

void	Space_invaders::startGame()
{
	std::string	str[2] = {"Start", "Exit"};
	std::string	pl[2] = {"Multiplayer", "Singleplayer"};
	std::string	finalinfo;

	this->_startNcursesMode();
	this->_game_menu = new WindowMenu();
	this->_game_field = new WindowMenu(LINES - 1, COLS, 1, 0);
	if (this->_game_menu->enter(_game_field->getWindow(), str, 2) == true)
	{
		this->_multiplay = this->_game_menu->enter(_game_field->getWindow(), pl, 2);
		this->_ship = new Hero(this->_game_field->getWindow(), this->_game_menu, this->_multiplay);
		this->_ship->createPlayer1();
		if (this->_multiplay == true)
			this->_ship->createPlayer2();
		finalinfo = this->_ship->StartGame();
	}
	getch();
	endwin();
	delete this->_game_menu;
	delete this->_game_field;
	if (this->_ship != nullptr)
	{
		std::cout << std::endl << "   -GAME OVER-" << std::endl;
		std::cout << finalinfo << std::endl << std::endl;
		delete this->_ship;
	}
}

void	Space_invaders::_startNcursesMode()
{
	initscr();
	noecho();
	cbreak();
	srand(time(NULL));
	curs_set(0);
	timeout(0);
	return ;
}

void	Space_invaders::_endNcursesMode() const
{
	return ;
}

/*
** Overloads
*/

Space_invaders &Space_invaders::operator= (const Space_invaders &other)
{
	this->_shipForm = other._shipForm;
	this->_yStart = other._yStart;
	this->_xStart = other._xStart;
	if (this->_ship != nullptr)
		delete this->_ship;
	this->_ship = other._ship;
	this->_game_field = other._game_field;
	return (*this);
}
