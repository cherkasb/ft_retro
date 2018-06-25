// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Hero.hpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: dborysen <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/06/05 11:55:46 by dborysen          #+#    #+#             //
/*   Updated: 2018/06/24 21:51:48 by bcherkas         ###   ########.fr       */
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
# include "Player.hpp"

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

class Hero
{

	public:
		Hero(void);
		Hero(WINDOW *window, WindowMenu *game_menu, bool multiplay);
		Hero(const Hero &other);
		~Hero();

		Hero &operator= (const Hero &other);

		std::string		StartGame();

		void	createPlayer1(void);
		void	createPlayer2(void);
		
		int		getYMax(void) const;
		int		getXMax(void) const;
		WINDOW	*getWindow(void) const;
		WindowMenu	*getGameMenu(void) const;
		Player	*getPlayer1(void) const;
		Player	*getPlayer2(void) const;

	private:
		int			_yMax, _xMax;
		t_bullet	*_magazine;
		t_enemy		*_enemies;
		WINDOW		*_current_window;
		WindowMenu	*_game_menu;
		Player		*_pl1;
		Player		*_pl2;
		Player		_last_dead;
		bool		_multiplay;

		std::string	_endGame();
		void		_showPlayersInfo(int frames);
		void		_showPlayersPositions(void);
		void		_giveAmmoToPlayers(int frames);
		bool		_heroAlive(int frames);
		void		_shoot(Player *player);
		int			_getMove();
		void		_moveAllBullets();
		void		_freeBulletList();
		int			_countEnemies() const;
		void		_addNewEnemy();
		void		_moveAllEnemies();
		void		_checkHitting();
		void		_freeEnemyList();
		t_bullet	*_copyBullets(t_bullet *orig);
		t_enemy		*_copyEnemies(t_enemy *orig);
};

#endif
