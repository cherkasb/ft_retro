// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Bullet.hpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: dborysen <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/06/07 13:02:04 by dborysen          #+#    #+#             //
/*   Updated: 2018/06/24 16:56:34 by bcherkas         ###   ########.fr       */
//                                                                            //
// ************************************************************************** //

#ifndef BULLET_HPP
# define BULLET_HPP

# include "Player.hpp"
# include <iostream>
# include <string>
# include <ncurses.h>

class Bullet
{
	public:
		Bullet(void);
		Bullet(const Bullet &other);
		Bullet(WINDOW *win, int heroX, int heroY, int xMax, int yMax,
				Player *player);
		~Bullet();

		Bullet &operator= (const Bullet &other);

		void		changeLocation(void);
		Player		*getPlayer(void) const;
		int			getX(void) const;
		int			getY(void) const;
		void		hitSomeone(void);
		const bool	&isInFly(void) const;

	private:
		Player	*_player;
		WINDOW	*_current_window;
		bool	_stillInFly;
		int		_x, _y;
		int		_xMax, _yMax;
};

#endif
