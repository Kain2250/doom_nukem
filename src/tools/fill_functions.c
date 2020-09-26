/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 14:48:05 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/09/17 21:09:39 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void		if_rect(SDL_Surface *src, t_rect *rsrc,
			SDL_Surface *dst, t_rect *rdst)
{
	if (rsrc == NULL)
	{
		rsrc = (t_rect *)ft_memalloc(sizeof(t_rect));
		rsrc->w = src->w;
		rsrc->h = src->h;
		rsrc->free = true;
	}
	if (rdst == NULL)
	{
		rdst = (t_rect *)ft_memalloc(sizeof(t_rect));
		rdst->w = dst->w;
		rdst->h = dst->h;
		rsrc->free = true;
	}
}

t_rect		rect_fill_no_malloc(int x, int y, int w, int h)
{
	t_rect	q;

	q.x = x;
	q.y = y;
	q.w = w;
	q.h = h;
	return (q);
}

t_rect		*rect_fill(int x, int y, int w, int h)
{
	t_rect	*rect;

	rect = (t_rect *)ft_memalloc(sizeof(t_rect));
	rect->x = x;
	rect->y = y;
	rect->w = w;
	rect->h = h;
	return (rect);
}

t_point		fill_point(int x, int y)
{
	t_point	point;

	point.x = x;
	point.y = y;
	return (point);
}

void		fill_limit_f(t_limit_f *data, float min, float cur, float max)
{
	data->min = min;
	data->cur = (cur <= min) ? min : (cur >= max) ? max : cur;
	data->max = max;
}

void		fill_limit(t_limit *data, int min, int cur, int max)
{
	data->min = min;
	data->cur = (cur <= min) ? min : (cur >= max) ? max : cur;
	data->max = max;
}
