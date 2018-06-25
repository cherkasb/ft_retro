// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Hero.hpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: dborysen <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/06/05 11:55:46 by dborysen          #+#    #+#             //
/*   Updated: 2018/06/24 12:28:35 by bcherkas         ###   ########.fr       */
//                                                                            //
// ************************************************************************** //

#ifndef HERO_HPP
# define HERO_HPP
# define GAME_SPEED		20000
# define ENEMY_COUNT	100
# define BULLET_NUM		10

# include <iostream>
# include <string>
# include <ncurses.h>
# include <ctime>
# include <cmath>
# include <cstdlib>
# include <unistd.h>
# include "Bullet.hpp"
# include "Enemy.hpp"
# include "Ghost.hpp"
# include "WindowMenu.hpp"

class Hero
{
	typedef struct	s_bullet
	{
		Bullet 			*newOne;
		struct s_bullet	*next;
	}				t_bullet;

	typedef struct	s_enemy
	{
		Enemy 			*newOne;
		struct s_enemy	*next;
	}				t_enemy;

	public:
		Hero(void);
		Hero(WINDOW *window, WindowMenu *game_menu, int y, int x, char c);
		Hero(const Hero &other);
		~Hero();

		Hero &operator= (const Hero &other);

		const int	&getScore() const;

	private:
		int			_player;
		int			_lives;
		int			_ammo;
		int			_maxAmmo;
		int			_yHero, _xHero;
		int			_yMax, _xMax;
		int			_score;
		char		_hero;
		t_bullet	*_magazine;
		t_enemy		*_enemies;
		WINDOW		*_current_window;
		WindowMenu	*_game_menu;

		void		_giveAmmo(int frames);
		void		_shoot();
		void		_moveUp();
		void		_moveDown();
		void		_moveLeft();
		void		_moveRight();
		int			_getMove();
		void		_showHeroPosition() const;
		void		_moveAllBullets();
		void		_freeBulletList();
		void		_controlTheShip();
		int			_countEnemies() const;
		void		_addNewEnemy();
		void		_moveAllEnemies();
		void		_checkHitting();
		void		_freeEnemyList();
		bool		_heroAlive();
		void		_showPlayerInfo(int frames) const;
		t_bullet	*_copyBullets(t_bullet *orig);
		t_enemy		*_copyEnemies(t_enemy *orig);

		bool		_enterMenu(void) const;
};

#endif
