/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blit_surface.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 21:03:55 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/08/29 21:18:30 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static t_rectf		check_scale_delta(t_rect *rdst, t_rect *rsrc)
{
	t_rectf			delta;

	if (rdst->h == rsrc->h)
		delta.h = 1.0;
	else
		delta.h = ((rsrc->h * 1.0) / (rdst->h * 1.0));
	if (rdst->w == rsrc->w)
		delta.w = 1.0;
	else
		delta.w = ((rsrc->w * 1.0) / (rdst->w * 1.0));
	return (delta);
}

static void			while_scale_pic(SDL_Surface *src, t_rect *rsrc,
					SDL_Surface *dst, t_rect *rdst)
{
	t_pointf		crd[2];
	t_rectf			delta;
	Uint32			color;

	delta = check_scale_delta(rdst, rsrc);
	crd[0].y = rdst->y;
	crd[1].y = rsrc->y;
	while (crd[0].y < rdst->h || crd[0].y < rdst->y + rdst->h)
	{
		crd[0].x = rdst->x;
		crd[1].x = rsrc->x;
		color = get_pixel(src, crd[1].x, crd[1].y);
		while (crd[0].x < rdst->w || crd[0].x < rdst->x + rdst->w)
		{
			color = get_pixel(src, crd[1].x, crd[1].y);
			putpixel(dst, crd[0].x, crd[0].y, color);
			crd[1].x += delta.w;
			crd[0].x++;
		}
		crd[1].y += delta.h;
		crd[0].y++;
	}
}

void				blit_surf_scaled(SDL_Surface *src, t_rect *rsrc,
					SDL_Surface *dst, t_rect *rdst)
{
	bool			frees[2];

	frees[0] = false;
	frees[1] = false;
	if (rsrc == NULL)
	{
		rsrc = rect_fill(0, 0, src->w, src->h);
		frees[0] = true;
	}
	if (rdst == NULL)
	{
		rdst = rect_fill(0, 0, dst->w, dst->h);
		frees[1] = true;
	}
	while_scale_pic(src, rsrc, dst, rdst);
	if (frees[0])
		free(rsrc);
	if (frees[1])
		free(rdst);
}
