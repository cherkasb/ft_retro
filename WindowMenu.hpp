/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WindowM.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcherkas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/23 20:42:18 by bcherkas          #+#    #+#             */
/*   Updated: 2018/06/24 12:53:14 by bcherkas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOWMENU_HPP
# define WINDOWMENU_HPP

# define ESC 27
# define SPACE 32

# include <iostream>
# include <string>
# include <ncurses.h>
# include <cstdlib>

class	WindowMenu {

public:

	WindowMenu(void);
	WindowMenu(int y, int x, int yLen, int xLen);
	WindowMenu(const WindowMenu &other);
	~WindowMenu();

	WINDOW	*getWindow(void) const;

	WindowMenu &operator= (const WindowMenu &other);
	int		getXStart(void) const;
	int		getYStart(void) const;
	int		getYLen(void) const;
	int		getXLen(void) const;

	bool	enter(WINDOW *other, std::string *menus, int max) const;

private:

	WINDOW	*_window;
	int		_y;
	int		_x;
	int		_yLen;
	int		_xLen;

};

#endif
