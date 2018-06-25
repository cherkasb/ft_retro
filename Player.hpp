// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Player.hpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: dborysen <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/06/05 11:55:46 by dborysen          #+#    #+#             //
/*   Updated: 2018/06/24 21:06:03 by bcherkas         ###   ########.fr       */
//                                                                            //
// ************************************************************************** //

#ifndef PLAYER_HPP
# define PLAYER_HPP

# define GAME_SPEED		20000
# define ENEMY_COUNT	100
# define BULLET_NUM		10

# include <iostream>
# include <string>
# include <ncurses.h>
# include <cmath>
# include <cstdlib>
# include <unistd.h>

class Player
{
	public:
		Player(void);
		Player(WINDOW *window, int y, int x, char c, int num);
		Player(const Player &other);
		~Player();

		Player &operator= (const Player &other);

		int			getPlayer() const;
		int			getLives() const;
		int			getAmmo() const;
		int			getMaxAmmo() const;
		int			getYPlayer() const;
		int			getXPlayer() const;
		int			getYMax() const;
		int			getXMax() const;
		int			getScore() const;
		char		getHero() const;
		WINDOW		*getWindow() const;
		float		getPlaytime() const;

		void		getDamage(int dmg);
		void		addScore(int score);

		void		moveUp();
		void		moveDown();
		void		moveLeft();
		void		moveRight();

		void		changeAmmo(bool i);

		void		showPlayerPosition() const;
		void		showPlayerInfo(int frames, int pos);

	private:

		float		_playtime;
		int			_player;
		int			_lives;
		int			_ammo;
		int			_maxAmmo;
		int			_yPlayer, _xPlayer;
		int			_yMax, _xMax;
		int			_score;
		char		_hero;
		WINDOW		*_current_window;

};

#endif
