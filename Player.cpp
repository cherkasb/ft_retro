// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Player.cpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: dborysen <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/06/15 15:41:34 by dborysen          #+#    #+#             //
/*   Updated: 2018/06/24 21:55:06 by bcherkas         ###   ########.fr       */
//                                                                            //
// ************************************************************************** //

#include "Player.hpp"

Player::Player()
{
	return ;
}

Player::Player(WINDOW *window, int y, int x, char c, int num)
{
	this->_current_window = window;
	this->_yPlayer = y;
	this->_xPlayer = x;
	this->_hero = c;
	this->_score = 0;
	this->_lives = 5;
	this->_ammo = 50;
	this->_maxAmmo = 50;
	this->_player = num;
	getmaxyx(window, this->_yMax, this->_xMax);
	mvwaddch(this->_current_window, this->_yPlayer, this->_xPlayer, this->_hero);	
	return ;
}

Player::Player(const Player &other)
{
	*this = other;
	return ;
}

Player::~Player()
{
	return ;
}

void	Player::moveUp()
{
	mvwaddch(this->_current_window, this->_yPlayer, this->_xPlayer, ' ');
	this->_yPlayer--;
	if (this->_yPlayer < 1)
		this->_yPlayer = 1;
	return ;
}

void	Player::moveDown()
{
	mvwaddch(this->_current_window, this->_yPlayer, this->_xPlayer, ' ');
	this->_yPlayer++;
	if (this->_yPlayer > this->_yMax - 2)
		this->_yPlayer = this->_yMax - 2;
	return ;
}

void	Player::moveLeft()
{
	mvwaddch(this->_current_window, this->_yPlayer, this->_xPlayer, ' ');
	this->_xPlayer--;
	if (this->_xPlayer < 1)
		this->_xPlayer = 1;
	return ;
}

void	Player::moveRight()
{
	mvwaddch(this->_current_window, this->_yPlayer, this->_xPlayer, ' ');
	this->_xPlayer++;
	if (this->_xPlayer > this->_xMax - 2)
		this->_xPlayer = this->_xMax - 2;
	return ;
}

void	Player::showPlayerInfo(int frames, int pos)
{
	this->_playtime = frames * ((double)500.0 / (double)GAME_SPEED);
	mvwaddstr(this->_current_window, 0, pos, "PLAYER:");
	pos += strlen("PLAYER:");
	mvwprintw(this->_current_window, 0, pos, "%2d", this->_player);
	pos += 2;
	mvwaddstr(this->_current_window, 0, pos, " SCORE: ");
	pos += strlen("SCORE: ");
	if (this->_score < 100000)
		mvwprintw(this->_current_window, 0, pos, "%6d", this->_score);
	pos += 6;
	mvwaddstr(this->_current_window, 0, pos, " AMMO:");
	pos += strlen(" AMMO:");
	mvwprintw(this->_current_window, 0, pos, "%4d ", this->_ammo);
	pos += 4;
	mvwaddstr(this->_current_window, 0, pos, " LIVES:");
	pos += strlen(" LIVES:");
	mvwprintw(this->_current_window, 0, pos, "%2d ", this->_lives);
	pos += 2;
	mvwprintw(this->_current_window, 0, pos, " TIME: %4.0f s", this->_playtime);
	return ;
}	

void	Player::changeAmmo(bool i)
{
	if (i == true)
	{
		if (this->_ammo < this->_maxAmmo)
			this->_ammo++;
	}
	else
		if (this->_ammo > 0)
			this->_ammo--;
}

void	Player::showPlayerPosition(void) const
{
	mvwaddch(this->_current_window, this->_yPlayer, this->_xPlayer, this->_hero);
	return ;
}

/*
** Get/Set
*/

void	Player::addScore(int score)
{
	if (score > 5000 || score < 1)
		return ;
	this->_score += score;
}

void	Player::getDamage(int dmg)
{
	if (dmg < 0)
		return ;
	if (this->_lives < dmg)
		dmg = this->_lives;
	this->_lives -= dmg;
}

int		Player::getPlayer() const
{
	return (this->_player);
}

int		Player::getLives() const
{
	return (this->_lives);
}

int		Player::getAmmo() const
{
	return (this->_ammo);
}

int		Player::getMaxAmmo() const
{
	return (this->_maxAmmo);
}

int		Player::getYPlayer() const
{
	return (this->_yPlayer);
}

int		Player::getXPlayer() const
{
	return (this->_xPlayer);
}

int		Player::getYMax() const
{
	return (this->_yMax);
}

int		Player::getXMax() const
{
	return (this->_xMax);
}

int		Player::getScore() const
{
	return (this->_score);
}

char	Player::getHero() const
{
	return (this->_score);
}

WINDOW	*Player::getWindow() const
{
	return (this->_current_window);
}

float	Player::getPlaytime(void) const
{
	return (this->_playtime);
}

/*
** Overloads
*/

Player &Player::operator= (const Player &other)
{
	this->_score = other.getScore();
	this->_player = other.getPlayer();
	this->_lives = other.getLives();
	this->_ammo = other.getAmmo();
	this->_maxAmmo = other.getMaxAmmo();
	this->_current_window = other.getWindow();
	this->_yPlayer = other.getYPlayer();
	this->_xPlayer = other.getXPlayer();
	this->_hero = other.getHero();
	this->_yMax = other.getYMax();
	this->_xMax = other.getXMax();
	this->_playtime = other.getPlaytime();
	return (*this);
}
