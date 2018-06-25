// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Enemy.hpp                                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: dborysen <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/06/11 14:37:57 by dborysen          #+#    #+#             //
/*   Updated: 2018/06/23 20:14:01 by bcherkas         ###   ########.fr       */
//                                                                            //
// ************************************************************************** //

#ifndef ENEMY_HPP
# define ENEMY_HPP

# include <iostream>
# include <string>
# include <ncurses.h>
# include <ctime>

class Enemy
{
	public:
		Enemy(void);
		Enemy(WINDOW *window, int xMax, int yMax);
		Enemy(const Enemy &other);
		virtual ~Enemy();

		Enemy &operator= (const Enemy &other);
		
		virtual void	fly(void);
		virtual const int	&getX(void) const;
		virtual const int	&getY(void) const;
		virtual int		getDamage(int dmg);
		virtual int		doDamage(void) const;
		virtual int		getScoreAward(void) const;

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
