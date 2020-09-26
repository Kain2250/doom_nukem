/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drag_and_drop.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/04 16:06:01 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/09/04 16:06:23 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void			drag_and_drop(SDL_Surface *src, SDL_Surface *dst)
{
	t_point		mouse;
	t_point		screen;
	int			x;
	int			y;

	SDL_GetMouseState(&mouse.x, &mouse.y);
	screen.y = 0;
	while (screen.y < src->h)
	{
		screen.x = 0;
		while (screen.x < src->w)
		{
			x = (mouse.x + screen.x >= dst->w) ?
				dst->w - 1 : mouse.x + screen.x;
			y = (mouse.y + screen.y >= dst->h) ?
				dst->h - 1 : mouse.y + screen.y;
			putpixel(dst, x, y, get_pixel(src, screen.x, screen.y));
			screen.x++;
		}
		screen.y++;
	}
}
