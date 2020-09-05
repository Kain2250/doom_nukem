/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_smoothed_rect.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 09:36:46 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/09/05 18:55:13 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static void	put_smooth_angle_pixel(SDL_Surface *dst, t_point coord,
				t_point center[4], Uint32 color)
{
	int		x_plus;
	int		x_minus;
	int		y_plus;
	int		y_minus;

	x_plus = center[1].x + coord.x;
	x_minus = center[0].x - coord.x;
	y_plus = center[2].y + coord.y;
	y_minus = center[0].y - coord.y;
	if (x_plus > dst->w - 1)
		x_plus = dst->w - 1;
	if (y_plus > dst->h - 1)
		y_plus = dst->h - 1;
	if (x_minus < 0)
		x_minus = -1;
	if (y_minus < 0)
		y_minus = 0;
	putpixel(dst, x_plus, y_plus, color);
	putpixel(dst, x_plus, y_minus, color);
	putpixel(dst, x_minus, y_plus, color);
	putpixel(dst, x_minus, y_minus, color);
}

void		draw_smooth_angle(SDL_Surface *dst, t_point center[4],
				int radius, Uint32 color)
{
	t_point	coord;
	int		delta;
	int		error;

	coord.x = 0;
	coord.y = radius;
	delta = 1 - 2 * radius;
	error = 0;
	while (coord.y >= 0)
	{
		put_smooth_angle_pixel(dst, coord, center, color);
		error = 2 * (delta + coord.y) - 1;
		if ((delta < 0) && (error <= 0))
		{
			delta += 2 * ++coord.x + 1;
			continue ;
		}
		if ((delta > 0) && (error > 0))
		{
			delta -= 2 * --coord.y + 1;
			continue ;
		}
		delta += 2 * (++coord.x - --coord.y);
	}
}

void		recurs_draw(SDL_Surface *dst, t_rect *rect,
				int rounding, Uint32 color)
{
	t_point	center[4];

	center[0].x = rect->x + rounding;
	center[0].y = rect->y + rounding;
	center[1].x = rect->x + rect->w - rounding;
	center[1].y = rect->y + rounding;
	center[2].x = rect->x + rounding;
	center[2].y = rect->y + rect->h - rounding;
	center[3].x = rect->x + rect->w - rounding;
	center[3].y = rect->y + rect->h - rounding;
	draw_line(dst, fill_point(center[0].x, rect->y),
		fill_point(center[1].x, rect->y), color);
	draw_line(dst, fill_point(center[2].x, rect->y + rect->h),
		fill_point(center[3].x, rect->y + rect->h), color);
	draw_line(dst, fill_point(rect->x, center[0].y),
		fill_point(rect->x, center[2].y), color);
	draw_line(dst, fill_point(rect->x + rect->w, center[1].y),
		fill_point(rect->x + rect->w, center[3].y), color);
	draw_smooth_angle(dst, center, rounding, color);
}

void		draw_smooth_rect(SDL_Surface *dst, t_rect *rect,
				Uint32 color, int thickness)
{
	int		rounding;
	int		i;
	int		shift;
	t_rect	tmp_rect;

	i = 0;
	rounding = (rect->w >= rect->h) ? rect->w / 10 : rect->h / 10;
	shift = 0;
	while (i < thickness)
	{
		tmp_rect = rect_fill_no_malloc(rect->x + shift, rect->y + shift,
			rect->w - shift * 2, rect->h - shift * 2);
		recurs_draw(dst, &tmp_rect, rounding, color);
		if (rounding > 1)
			rounding--;
		else
			break ;
		shift++;
		i++;
	}
}
