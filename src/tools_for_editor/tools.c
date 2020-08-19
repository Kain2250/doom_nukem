/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 20:40:05 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/08/19 21:57:58 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void			scale_frame(SDL_Surface *dst, t_mouse mouse, Uint32 color)
{
	static SDL_Rect	cur;
	
	SDL_GetMouseState(cur.w >= 0 ? &cur.w : NULL, cur.h >= 0 ? &cur.h : NULL);
	cur.x = mouse.prew_x;
	cur.y = mouse.prew_y;
	if (cur.w > 0)
		cur.w -= cur.x;
	else
	{
		cur.x += cur.w;
		cur.w *= -1;
	}
	if (cur.h > 0)
		cur.h -= cur.y;
	else
	{
		cur.y += cur.h;
		cur.h *= -1;
	}
	printf("cur.x - %d cur.y - %d cur.w - %d cur.h - %d\n", cur.x, cur.y, cur.w, cur.h);
	draw_rect(dst, &cur, color);
}

void			draw_rect(SDL_Surface *dst, SDL_Rect *rect, Uint32 color)
{
	register int	i;
	register int	w;
	register int	h;

	i = rect->x;
	w = rect->x + rect->w;
	h = rect->y + rect->h;
	while (i <= w)
	{
		putpixel(dst, i, rect->y, color);
		putpixel(dst, i, h, color);
		i++;
	}
	i = rect->y + 1;
	while (i < h)
	{
		putpixel(dst, rect->x, i, color);
		putpixel(dst, w, i, color);
		i++;
	}
}

void			drag_and_drop(SDL_Surface *src, SDL_Surface *dst)
{
	SDL_Point	mouse;
	SDL_Point	screen;
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

bool		frame_master(t_doom_nukem *doom, SDL_Rect *dst)
{
	
	SDL_BlitScaled(doom->sdl.textures[texture_iron], NULL, doom->sdl.surface, dst);
	SDL_UpdateWindowSurface(doom->sdl.window);
	return (true);
}
