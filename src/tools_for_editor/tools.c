/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 20:40:05 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/08/24 22:09:38 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void			abs_side_frame(int *a, int *b)
{
	*a += *b;
	*b *= -1;
}

void			scale_frame_01(SDL_Surface *dst, t_mouse mouse, SDL_Surface *src)
{
	static SDL_Rect	cur;

	SDL_GetMouseState(cur.w >= 0 ? &cur.w : NULL, cur.h >= 0 ? &cur.h : NULL);
	cur.x = mouse.prew_x;
	cur.y = mouse.prew_y;
	if (cur.w >= 0)
	{
		cur.w -= cur.x;
		if (cur.w < 0)
			abs_side_frame(&cur.x, &cur.w);
	}
	else
		abs_side_frame(&cur.x, &cur.w);
	if (cur.h >= 0)
	{
		cur.h -= cur.y;
		if (cur.h < 0)
			abs_side_frame(&cur.y, &cur.h);
	}
	else
		abs_side_frame(&cur.y, &cur.h);
	blit_surface(src, NULL, dst, &cur);
	// SDL_BlitScaled(src, NULL, dst, &cur);
}

void			scale_frame(SDL_Surface *dst, t_mouse mouse, Uint32 color,
				void draw(SDL_Surface *, SDL_Rect *, Uint32, int))
{
	static SDL_Rect	cur;

	SDL_GetMouseState(cur.w >= 0 ? &cur.w : NULL, cur.h >= 0 ? &cur.h : NULL);
	cur.x = mouse.prew_x;
	cur.y = mouse.prew_y;
	if (cur.w >= 0)
	{
		cur.w -= cur.x;
		if (cur.w < 0)
			abs_side_frame(&cur.x, &cur.w);
	}
	else
		abs_side_frame(&cur.x, &cur.w);
	if (cur.h >= 0)
	{
		cur.h -= cur.y;
		if (cur.h < 0)
			abs_side_frame(&cur.y, &cur.h);
	}
	else
		abs_side_frame(&cur.y, &cur.h);
	draw(dst, &cur, color, 1);
}

void			draw_rect(SDL_Surface *dst, SDL_Rect *rect, Uint32 color, int step)
{
	register int	i;
	register int	w;
	register int	h;

	step = (step == 0) ? 1 : step;
	i = rect->x;
	w = rect->x + rect->w;
	h = rect->y + rect->h;
	while (i <= w)
	{
		putpixel(dst, i, rect->y, color);
		putpixel(dst, i, h, color);
		i += step;
	}
	i = rect->y + 1;
	while (i < h)
	{
		putpixel(dst, rect->x, i, color);
		putpixel(dst, w, i, color);
		i += step;
	}
}

void			draw_feel_rect(SDL_Surface *dst, SDL_Rect *rect,
				Uint32 color, int step)
{
	register int	x;
	register int	y;
	register int	w;
	register int	h;

	step = (step == 0) ? 1 : step;
	w = rect->x + rect->w;
	h = rect->y + rect->h;
	y = rect->y;
	while (y < h)
	{
		x = rect->x;
		while (x <= w)
		{
			putpixel(dst, x, y, color);
			x += step;
		}
		y += step;
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
