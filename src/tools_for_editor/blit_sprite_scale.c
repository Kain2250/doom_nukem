/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blit_sprite_scale.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 21:03:55 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/11/26 21:34:19 by bdrinkin         ###   ########.fr       */
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

static void			while_scale_pic(t_sprite *src, t_rect *rsrc,
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
		while (crd[0].x < rdst->w || crd[0].x < rdst->x + rdst->w)
		{
			color = get_pixel_sprite(src, crd[1].x, crd[1].y);
			if (color == 0xFFFFFFFF)
			{
				(crd[1].x += delta.w) && crd[0].x++;
				continue ;
			}
			putpixel(dst, crd[0].x, crd[0].y, color);
			(crd[1].x += delta.w) && crd[0].x++;
		}
		(crd[1].y += delta.h) && crd[0].y++;
	}
}

void				blit_sprite_scaled(t_sprite *src, t_rect *rsrc,
						SDL_Surface *dst, t_rect *rdst)
{
	t_rect			tmp_rsrc;
	t_rect			tmp_rdst;
	int32_t			tmp_top_offset;
	int32_t			tmp_left_offset;

	tmp_top_offset = src->top_offset;
	tmp_left_offset = src->left_offset;
	if (rsrc == NULL)
		tmp_rsrc = (t_rect){0, 0, src->w, src->h, false};
	if (rdst == NULL)
		tmp_rdst = (t_rect){0, 0, dst->w, dst->h, false};
	else
	{
		// src->left_offset += src->w - rdst->w;
		// src->top_offset += src->h - rdst->h;
		rdst->x += src->left_offset - rdst->w / 2;
		rdst->y += src->top_offset - rdst->h / 2;
	}
	while_scale_pic(src, rsrc != NULL ? rsrc : &tmp_rsrc,
		dst, rdst != NULL ? rdst : &tmp_rdst);
	src->top_offset = tmp_top_offset;
	src->left_offset = tmp_left_offset;
}
