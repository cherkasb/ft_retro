// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Hero.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: dborysen <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/06/15 15:41:34 by dborysen          #+#    #+#             //
/*   Updated: 2018/06/24 21:52:10 by bcherkas         ###   ########.fr       */
//                                                                            //
// ************************************************************************** //

#include "Hero.hpp"

Hero::Hero()
{
	return ;
}

Hero::Hero(WINDOW *window, WindowMenu *game_menu, bool multiplay)
{
	this->_multiplay = multiplay;
	this->_current_window = window;
	this->_game_menu = game_menu;
	this->_magazine = nullptr;
	this->_enemies = nullptr;
	this->_pl1 = nullptr;
	this->_pl2 = nullptr;
	getmaxyx(window, this->_yMax, this->_xMax);
	return ;
}

Hero::Hero(const Hero &other)
{
	*this = other;
	return ;
}

Hero::~Hero()
{
	return ;
}

/*
** Players
*/

void	Hero::createPlayer1(void)
{
	this->_pl1 = new Player(this->_current_window, 5, 5, '}', 1);
}

void	Hero::createPlayer2(void)
{
	this->_pl2 = new Player(this->_current_window, 15, 5, '[', 2);
}

int		Hero::_getMove()
{
	std::string	str[2] = {"Resume", "Exit"};
	int choise = wgetch(this->_current_window);

	if (this->_pl1 != nullptr)
	{
		if (choise == SPACE)
			this->_shoot(this->_pl1);
		else if (choise == 119)
			this->_pl1->moveUp();
		else if (choise == 115)
			this->_pl1->moveDown();
		else if (choise == 97)
			this->_pl1->moveLeft();
		else if (choise == 100)
			this->_pl1->moveRight();
	}
	if (this->_pl2 != nullptr)
	{
		if (choise == 10)
			this->_shoot(this->_pl2);
		else if (choise == KEY_UP)
			this->_pl2->moveUp();
		else if (choise == KEY_DOWN)
			this->_pl2->moveDown();
		else if (choise == KEY_LEFT)
			this->_pl2->moveLeft();
		else if (choise == KEY_RIGHT)
			this->_pl2->moveRight();
	}
	if (choise == ESC)
	{
		if (this->_game_menu->enter(this->_current_window, str, 2) == false)
			return (0);
	}
	return (choise);
}

std::string	Hero::StartGame()
{
	std::string	res;
	size_t	frames = 1;

	while (this->_getMove() && this->_heroAlive(frames))
	{
		this->_showPlayersPositions();
		if (this->_countEnemies() < ENEMY_COUNT)
			this->_addNewEnemy();
		this->_moveAllBullets();
		this->_moveAllEnemies();
		this->_checkHitting();
		this->_showPlayersInfo(frames);
		this->_giveAmmoToPlayers(frames);
		frames++;
		wrefresh(this->_current_window);
		usleep(GAME_SPEED);
	}
	res = this->_endGame();
	this->_freeEnemyList();
	this->_freeBulletList();
	return (res);
}

std::string	Hero::_endGame(void)
{
	std::string	res;

	if (this->_pl1 != nullptr && this->_pl2 == nullptr)
	{
		this->_last_dead = *(this->_pl1);
		delete this->_pl1;
	}
	else if (this->_pl2 != nullptr && this->_pl1 == nullptr)
	{
		this->_last_dead = *(this->_pl2);
		delete this->_pl2;
	}
	if (this->_multiplay == true)
	{
		if (this->_last_dead.getPlayer() == 0)
		{
			res = "There are no winner, because all players were alive when game ended";
			delete this->_pl1;
			delete this->_pl2;
		}
		else if (this->_last_dead.getPlayer() != 0)
			res = "The winner is Player " + std::to_string(this->_last_dead.getPlayer())
				+ " with score " + std::to_string(this->_last_dead.getScore())
				+ " and lifetime " + std::to_string(this->_last_dead.getPlaytime()) + " seconds";
	}
	else
		res = "Your score is " + std::to_string(this->_last_dead.getScore())
			+ " and your lifetime is " + std::to_string(this->_last_dead.getPlaytime()) + " seconds";
	return (res);
}

void	Hero::_checkHitting()
{
	t_bullet	*tmpBullet;
	t_enemy		*tmpEnemy;

	tmpEnemy = this->_enemies;
	while (tmpEnemy != nullptr)
	{
		tmpBullet = this->_magazine;
		while (tmpBullet != nullptr)
		{
			if (abs(tmpEnemy->newOne->getX() - tmpBullet->newOne->getX()) < 2 &&
				tmpEnemy->newOne->getY() == tmpBullet->newOne->getY() &&
				tmpBullet->newOne->isInFly() == TRUE)
			{
				if (tmpEnemy->newOne->getDamage(1))
					tmpBullet->newOne->getPlayer()->addScore(tmpEnemy->newOne->getScoreAward());
				tmpBullet->newOne->hitSomeone();
			}
			tmpBullet = tmpBullet->next;
		}
		tmpEnemy = tmpEnemy->next;
	}
	return ;
}

bool	Hero::_heroAlive(int frames)
{
	Player	*player;
	t_enemy *tmp;

	tmp = this->_enemies;
	while (tmp != nullptr)
	{
		player = nullptr;
		if (this->_pl1 != nullptr && tmp->newOne->getX() == this->_pl1->getXPlayer() && 
			tmp->newOne->getY() == this->_pl1->getYPlayer())
			player = this->_pl1;	
		else if (this->_pl2 != nullptr && tmp->newOne->getX() == this->_pl2->getXPlayer() && 
			tmp->newOne->getY() == this->_pl2->getYPlayer())
			player = this->_pl2;
		if (player != nullptr)
		{
			(player)->getDamage(tmp->newOne->doDamage());
			tmp->newOne->getDamage(100);
			if ((player)->getLives() == 0)
			{
				this->_showPlayersInfo(frames);
				this->_last_dead = *player;
				delete player;
				if (player == this->_pl1)
					this->_pl1 = nullptr;
				else
					this->_pl2 = nullptr;
				mvwprintw(this->_current_window, player->getYPlayer(), player->getXPlayer(), " ");
			}
		}	
		tmp = tmp->next;
	}
	if (this->_pl1 == nullptr && this->_pl2 == nullptr)
		return (FALSE);
	return (TRUE);
}

void	Hero::_showPlayersInfo(int frames)
{
	int		messagelen = 55;

	if (this->_pl1 != nullptr)
		this->_pl1->showPlayerInfo(frames, 1);
	if (this->_pl2 != nullptr)
		this->_pl2->showPlayerInfo(frames, COLS - messagelen);
}

void	Hero::_giveAmmoToPlayers(int frames)
{
	if (frames % 100 == 0)
	{
		if (this->_pl2 != nullptr)
			this->_pl2->changeAmmo(true);
		if (this->_pl1 != nullptr)
			this->_pl1->changeAmmo(true);
	}
}

void	Hero::_showPlayersPositions(void)
{
	if (this->_pl2 != nullptr)
		this->_pl2->showPlayerPosition();
	if (this->_pl1 != nullptr)
		this->_pl1->showPlayerPosition();
}

void	Hero::_freeEnemyList()
{
	t_enemy *tmp;

	while (this->_enemies != nullptr)
	{
		tmp = this->_enemies->next;
		delete this->_enemies->newOne;
		delete this->_enemies;
		this->_enemies = tmp;
	}
	return;
}

void		Hero::_freeBulletList()
{
	t_bullet *tmp;

	while (this->_magazine != nullptr)
	{
		tmp = this->_magazine->next;
		delete this->_magazine->newOne;
		delete this->_magazine;
		this->_magazine = tmp;
	}
	return;
}

void		Hero::_moveAllEnemies()
{
	t_enemy *tmp;

	tmp = this->_enemies;
	while (tmp != nullptr)
	{
		tmp->newOne->fly();
		tmp = tmp->next;
	}
	return ;
}

void		Hero::_addNewEnemy()
{
	t_enemy	*newNode;
	t_enemy	*tmp;
	Enemy	*newEnemy;

	if (rand() % 100 < 10)
	{
		newNode = new t_enemy;
		if (rand() % 2 == 0)
			newEnemy = new Enemy(this->_current_window, this->_xMax, this->_yMax);
		else
			newEnemy = new Ghost(this->_current_window, this->_xMax, this->_yMax);
		newNode->newOne = newEnemy;
		newNode->next = nullptr;
		tmp = this->_enemies;
		if (this->_enemies == nullptr)
			this->_enemies = newNode;
		else
		{
			while (tmp->next != nullptr)
				tmp = tmp->next;
			tmp->next = newNode;
		}
	}
	return ;
}

int		Hero::_countEnemies() const
{
	t_enemy *tmp;
	int		i;

	i = 0;
	tmp = this->_enemies;
	while (tmp != nullptr)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

void	Hero::_shoot(Player *player)
{
	t_bullet	*newNode;
	t_bullet	*tmp;
	Bullet		*newBullet;

	if (player->getAmmo() == 0)
		return ;
	newNode = new t_bullet;
	newBullet = new Bullet(this->_current_window, player->getXPlayer(), player->getYPlayer(), this->_xMax, this->_yMax, player);
	newNode->newOne = newBullet;
	newNode->next = nullptr;
	tmp = this->_magazine;
	if (this->_magazine == nullptr)
		this->_magazine = newNode;
	else
	{
		while (tmp->next != nullptr)
			tmp = tmp->next;
		tmp->next = newNode;
	}
	player->changeAmmo(false);
	return ;
}

void	Hero::_moveAllBullets()
{
	t_bullet	*tmp;

	tmp = this->_magazine;
	while (tmp != nullptr)
	{
		tmp->newOne->changeLocation();
		tmp = tmp->next;
	}
	return ;
}

t_bullet	*Hero::_copyBullets(t_bullet *orig)
{
	t_bullet 	*newMagazine;
	t_bullet	*tmp;

	newMagazine = nullptr;
	while (orig != nullptr)
	{
		t_bullet *newNode = new t_bullet;
		Bullet	*newOne = new Bullet;
		newNode->newOne = newOne;
		newNode->next = nullptr;
		tmp = newMagazine;
		if (newMagazine == nullptr)
			newMagazine = newNode;
		else
		{
			while (tmp->next != nullptr)
				tmp = tmp->next;
			tmp->next = newNode;
		}
		orig = orig->next;
	}
	return (newMagazine);
}

t_enemy	*Hero::_copyEnemies(t_enemy *orig)
{
	t_enemy *newEnemies;
	t_enemy	*tmp;

	newEnemies = nullptr;
	while (orig != nullptr)
	{
		t_enemy *newNode = new t_enemy;
		Enemy	*newOne = new Enemy;
		newNode->newOne = newOne;
		newNode->next = nullptr;
		tmp = newEnemies;
		if (newEnemies == nullptr)
			newEnemies = newNode;
		else
		{
			while (tmp->next != nullptr)
				tmp = tmp->next;
			tmp->next = newNode;
		}
		orig = orig->next;
	}
	return (newEnemies);
}

/*
** Get/Set
*/

int		Hero::getYMax(void) const
{
	return (this->_yMax);
}

int		Hero::getXMax(void) const
{
	return (this->_xMax);
}

WINDOW	*Hero::getWindow(void) const
{
	return ((this->_current_window));
}

WindowMenu	*Hero::getGameMenu(void) const
{
	return ((this->_game_menu));
}

Player	*Hero::getPlayer1(void) const
{
	return (this->_pl1);
}

Player	*Hero::getPlayer2(void) const
{
	return (this->_pl2);
}

/*
** Overloads
*/

Hero &Hero::operator= (const Hero &other)
{
	this->_enemies = _copyEnemies(other._enemies);
	this->_magazine = _copyBullets(other._magazine);
	this->_current_window = other.getWindow();
	this->_game_menu = other.getGameMenu();
	this->_pl1 = other.getPlayer1();
	this->_pl2 = other.getPlayer2();
	this->_xMax = other.getXMax();
	this->_yMax = other.getYMax();

	return (*this);
}
