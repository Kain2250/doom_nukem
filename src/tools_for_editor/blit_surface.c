/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blit_surface.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/04 12:16:13 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/09/10 14:51:01 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void		free_rect(t_rect *rect)
{
	if (rect->free == true)
		free(rect);
}

void		check_scale(SDL_Surface *source, t_rect *src)
{
	if (src->w > source->w)
		src->w = source->w;
	if (src->h > source->h)
		src->h = source->h;
}

void		blit_surface(SDL_Surface *src, t_rect *rsrc,
			SDL_Surface *dst, t_rect *rdst)
{
	t_point	source;
	t_point	dest;

	if_rect(src, rsrc, dst, rdst);
	check_scale(src, rsrc);
	source.y = rsrc->y;
	dest.y = rdst->y;
	while (source.y != rsrc->h)
	{
		source.x = rsrc->x;
		dest.x = rdst->x;
		while (source.x != rsrc->w)
		{
			putpixel(dst, dest.x++, dest.y,
				get_pixel(src, source.x++, source.y));
			if (source.x > rdst->w)
				break ;
		}
		source.y++;
		dest.y++;
		if (source.y > rdst->h)
			break ;
	}
	free_rect(rsrc);
	free_rect(rdst);
}
