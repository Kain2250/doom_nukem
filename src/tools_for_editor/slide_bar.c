/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slide_bar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/09 14:18:54 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/09/09 19:11:48 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

float		interpolate(t_limit_f x, t_limit_f c)
{
	float	ret;

	ret = x.min + ((c.cur - c.min) / (c.max - c.min)) * ((x.max - x.min) / 1);
	return (ret);
}

void		put_slide_bar(SDL_Surface *dst, t_rect *rect,
				t_limit *data, Uint32 color)
{
	t_limit_f	x;
	t_limit_f	c;
	t_point		center;

	c.min = data->min;
	c.max = data->max;
	c.cur = data->cur;
	x.min = rect->x;
	x.max = rect->x + rect->w;
	x.cur = interpolate(x, c);
	center.x = (int)x.cur;
	center.y = rect->y + rect->h / 2;
	draw_smooth_fill_rect(dst, rect, color);
	draw_fill_circl(dst, rect->h + 1, center, color + 0xEE6256);
}

// void		change_data_from_sladebar(t_rect *rect, t_limit *data, t_mouse mouse)
// {
// 	;

// }
