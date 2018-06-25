// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Ghost.hpp                                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: dborysen <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/06/11 14:37:57 by dborysen          #+#    #+#             //
/*   Updated: 2018/06/23 20:14:06 by bcherkas         ###   ########.fr       */
//                                                                            //
// ************************************************************************** //

#ifndef GHOST_HPP
# define GHOST_HPP

# include <iostream>
# include <string>
# include <ncurses.h>
# include <ctime>
# include "Enemy.hpp"

class Ghost : public Enemy
{
	public:
		Ghost(void);
		Ghost(WINDOW *window, int xMax, int yMax);
		Ghost(const Ghost &other);
		~Ghost();

		Ghost &operator= (const Ghost &other);
		
		void		fly(void);
		const int	&getX(void) const;
		const int	&getY(void) const;
		int			getDamage(int dmg);
		int			doDamage(void) const;
		int			getScoreAward(void) const;

	private:

		WINDOW		*_current_window;
		int			_x, _y;
		int			_xMax, _yMax;
		int			_HP;
		int			_damage;
		int			_score_award;

		int			_getRandomCoord(void);

};

#endif
