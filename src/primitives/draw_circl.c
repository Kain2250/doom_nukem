/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_circl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 18:36:42 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/12/12 13:09:09 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static void	put_fill_circl_pixel(SDL_Surface *dst, t_point coord,
			t_point center, Uint32 color)
{
	int		x_plus;
	int		x_minus;
	int		y_plus;
	int		y_minus;

	x_plus = center.x + coord.x;
	x_minus = center.x - coord.x;
	y_plus = center.y + coord.y;
	y_minus = center.y - coord.y;
	if (x_plus > dst->w - 1)
		x_plus = dst->w - 1;
	if (y_plus > dst->h - 1)
		y_plus = dst->h - 1;
	if (x_minus < 0)
		x_minus = -1;
	if (y_minus < 0)
		y_minus = 0;
	draw_line(dst, (t_point){x_plus, y_plus},
		(t_point){x_minus, y_plus}, color);
	draw_line(dst, (t_point){x_plus, y_minus},
		(t_point){x_minus, y_minus}, color);
}

void		draw_fill_circl(SDL_Surface *dst, int radius,
			t_point center, Uint32 color)
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
		put_fill_circl_pixel(dst, coord, center, color);
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

static void	put_circl_pixel(SDL_Surface *dst, t_point coord,
			t_point center, Uint32 color)
{
	int		x_plus;
	int		x_minus;
	int		y_plus;
	int		y_minus;

	x_plus = center.x + coord.x;
	x_minus = center.x - coord.x;
	y_plus = center.y + coord.y;
	y_minus = center.y - coord.y;
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

void		draw_circl(SDL_Surface *dst, int radius,
					t_point center, Uint32 color)
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
		put_circl_pixel(dst, coord, center, color);
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
