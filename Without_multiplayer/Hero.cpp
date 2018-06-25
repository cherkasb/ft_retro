// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Hero.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: dborysen <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/06/15 15:41:34 by dborysen          #+#    #+#             //
/*   Updated: 2018/06/24 12:54:56 by bcherkas         ###   ########.fr       */
//                                                                            //
// ************************************************************************** //

#include "Hero.hpp"

Hero::Hero()
{
	return ;
}

Hero::Hero(WINDOW *window, WindowMenu *game_menu, int y, int x, char c)
{
	this->_current_window = window;
	this->_game_menu = game_menu;
	this->_yHero = y;
	this->_xHero = x;
	this->_hero = c;
	this->_score = 0;
	this->_lives = 5;
	this->_ammo = 50;
	this->_maxAmmo = 50;
	this->_player = 1;
	this->_magazine = nullptr;
	this->_enemies = nullptr;
	getmaxyx(window, this->_yMax, this->_xMax);
	mvwaddch(this->_current_window, this->_yHero, this->_xHero, this->_hero);	
	this->_controlTheShip();
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

void	Hero::_moveUp()
{
	mvwaddch(this->_current_window, this->_yHero, this->_xHero, ' ');
	this->_yHero--;
	if (this->_yHero < 1)
		this->_yHero = 1;
	return ;
}

void	Hero::_moveDown()
{
	mvwaddch(this->_current_window, this->_yHero, this->_xHero, ' ');
	this->_yHero++;
	if (this->_yHero > this->_yMax - 2)
		this->_yHero = this->_yMax - 2;
	return ;
}

void	Hero::_moveLeft()
{
	mvwaddch(this->_current_window, this->_yHero, this->_xHero, ' ');
	this->_xHero--;
	if (this->_xHero < 1)
		this->_xHero = 1;
	return ;
}

void	Hero::_moveRight()
{
	mvwaddch(this->_current_window, this->_yHero, this->_xHero, ' ');
	this->_xHero++;
	if (this->_xHero > this->_xMax - 2)
		this->_xHero = this->_xMax - 2;
	return ;
}

int		Hero::_getMove()
{
	std::string	str[2] = {"Resume", "Exit"};
	int choise = wgetch(this->_current_window);

	switch(choise)
	{
		case KEY_UP:
			this->_moveUp();
			break ;
		case KEY_DOWN:
			this->_moveDown();
			break ;
		case KEY_LEFT:
			this->_moveLeft();
			break ;
		case KEY_RIGHT:
			this->_moveRight();
			break ;
		case SPACE:
			this->_shoot();
			break ;
		case ESC:
			if (this->_game_menu->enter(this->_current_window, str, 2) == false)
				return (0);
			break ;
		default:
			break ;
	}
	return (choise);
}

void	Hero::_controlTheShip()
{
	size_t	frames = 1;

	while (this->_getMove() && this->_heroAlive() == TRUE)
	{
		this->_showHeroPosition();
		if (this->_countEnemies() < ENEMY_COUNT)
			this->_addNewEnemy();
		this->_moveAllBullets();
		this->_moveAllEnemies();
		this->_checkHitting();
		this->_showPlayerInfo(frames);
		this->_giveAmmo(frames);
		frames++;
		wrefresh(this->_current_window);
		usleep(GAME_SPEED);
	}
	this->_freeEnemyList();
	this->_freeBulletList();
	return ;
}

void	Hero::_showPlayerInfo(int frames) const
{
	float	seconds;
	int		pos = 1;

	seconds = frames * ((double)500.0 / (double)GAME_SPEED);
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
	mvwprintw(this->_current_window, 0, pos, " TIME: %4.0f s", seconds);
	return ;
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
					this->_score += tmpEnemy->newOne->getScoreAward();
				tmpBullet->newOne->hitSomeone();
			}
			tmpBullet = tmpBullet->next;
		}
		tmpEnemy = tmpEnemy->next;
	}
	return ;
}

const int	&Hero::getScore() const
{
	return (this->_score);
}

bool	Hero::_heroAlive()
{
	t_enemy *tmp;

	tmp = this->_enemies;
	while (tmp != nullptr)
	{
		if (tmp->newOne->getX() == this->_xHero && 
			tmp->newOne->getY() == this->_yHero)
		{
			this->_lives -= tmp->newOne->doDamage();
			tmp->newOne->getDamage(100);
		}
		if (this->_lives <= 0)
			return (FALSE);
		tmp = tmp->next;
	}
	return (TRUE);
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

void	Hero::_giveAmmo(int frames)
{
	if (frames % 100 == 0 && this->_ammo <= this->_maxAmmo)
		this->_ammo++;
}

void	Hero::_shoot()
{
	t_bullet	*newNode;
	t_bullet	*tmp;
	Bullet		*newBullet;

	if (this->_ammo == 0)
		return ;
	newNode = new t_bullet;
	newBullet = new Bullet(this->_current_window, this->_xHero, this->_yHero,
													this->_xMax, this->_yMax);
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
	this->_ammo--;
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

void	Hero::_showHeroPosition() const
{
	mvwaddch(this->_current_window, this->_yHero, this->_xHero, this->_hero);
	return ;
}

Hero::t_bullet	*Hero::_copyBullets(t_bullet *orig)
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

Hero::t_enemy	*Hero::_copyEnemies(t_enemy *orig)
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
** Overloads
*/

Hero &Hero::operator= (const Hero &other)
{
	this->_enemies = _copyEnemies(other._enemies);
	this->_magazine = _copyBullets(other._magazine);
	this->_current_window = other._current_window;
	this->_yHero = other._yHero ;
	this->_xHero = other._xHero;
	this->_hero = other._hero;
	this->_yMax = other._yMax;
	this->_xMax = other._xMax;
	return (*this);
}
