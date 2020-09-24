/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 20:40:05 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/09/22 22:22:21 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void				abs_side_frame(int *a, int *b)
{
	*a += *b;
	*b *= -1;
}

void		put_button(SDL_Surface *dst, t_rect *rect,
				Uint32 color_fill, Uint32 color_frame)
{
	draw_smooth_fill_rect(dst, rect, color_fill);
	draw_smooth_rect(dst, rect, color_frame, 20);
}

void				scale_rect_texture(SDL_Surface *dst,
						t_mouse mouse, SDL_Surface *src)
{
	static t_rect	cur;

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
	blit_surf_scaled(src, NULL, dst, &cur);
}

void				scale_frame(SDL_Surface *dst, t_mouse mouse, Uint32 color,
						void draw(SDL_Surface *, t_rect *, Uint32, int))
{
	static t_rect	cur;

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
	(void)draw;
	draw(dst, &cur, color, 1);
	// draw_circl(dst, cur.w, fill_point(500, 500), color);
}
