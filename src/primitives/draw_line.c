/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/04 16:04:59 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/09/05 18:37:55 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void		draw_line(SDL_Surface *dst, t_point start,
			t_point end, Uint32 color)
{
	int		error[2];
	t_point	delta;
	t_point	sign;
	t_point	tek;

	delta.x = abs(end.x - start.x);
	delta.y = abs(end.y - start.y);
	sign.x = start.x < end.x ? 1 : -1;
	sign.y = start.y < end.y ? 1 : -1;
	error[0] = delta.x - delta.y;
	tek = start;
	while (tek.x != end.x || tek.y != end.y)
	{
		putpixel(dst, tek.x, tek.y, color);
		if ((error[1] = error[0] * 2) > -delta.y)
		{
			error[0] -= delta.y;
			tek.x += sign.x;
		}
		if (error[1] < delta.x)
		{
			error[0] += delta.x;
			tek.y += sign.y;
		}
	}
}
