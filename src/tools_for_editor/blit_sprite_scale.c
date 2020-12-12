/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blit_sprite_scale.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 21:03:55 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/12/12 21:05:06 by bdrinkin         ###   ########.fr       */
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

static void			while_scale_pic(t_wad_sprite *src, t_rect *rsrc,
					SDL_Surface *dst, t_rect *rdst)
{
	t_pointf		crd[2];
	t_rectf			delta;
	Uint32			color;
	int				temp;

	delta = check_scale_delta(rdst, rsrc);
	crd[0].y = rdst->y;
	crd[1].y = rsrc->y;
	while (crd[1].y < rsrc->h || crd[0].y < rdst->y + rdst->h)
	{
		crd[0].x = rdst->x;
		temp = 
		crd[1].x = rsrc->x;
		while (crd[1].x < rsrc->w || crd[0].x < rdst->x + rdst->w)
		{
			color = get_pixel_sprite(src, crd[1].x, crd[1].y);
			if (color == 0xFFFFFFFF)
			{
				(crd[1].x += delta.w) && crd[0].x++;
				continue ;
			}
			if (rdst->w < 0)
			{
				putpixel(dst, crd[0].x, crd[0].y, color);
			}
			putpixel(dst, crd[0].x, crd[0].y, color);
			(crd[1].x += delta.w) && crd[0].x++;
		}
		(crd[1].y += delta.h) && crd[0].y++;
	}
}

void				blit_gan_scaled(t_wad_sprite *src, SDL_Surface *dst)
{
	t_rect			rsrc;
	t_rect			rdst;

	rsrc = (t_rect){0, 0, src->w, src->h};
	rdst.w = SCALING_W(src->w);
	rdst.h = SCALING_H(src->h);
	rdst.x = -(SCALING_W(src->left_offset));
	rdst.y = -(SCALING_H(src->top_offset));
	while_scale_pic(src, &rsrc, dst, &rdst);
}

void				blit_hud_scaled(t_wad_sprite *src, SDL_Surface *dst)
{
	t_rect			rsrc;
	t_rect			rdst;

	rsrc = (t_rect){0, 0, src->w, src->h};
	rdst.w = SCALING_W(src->w);
	rdst.h = SCALING_H(src->h);
	rdst.x = 0;
	rdst.y = HEIGHT_WIN - rdst.h;
	while_scale_pic(src, &rsrc, dst, &rdst);
}

void				blit_sprite_scale(t_wad_sprite *src, SDL_Surface *dst,
						t_rectf rdst)
{
	t_rect			rsrc;
	t_rect			rdst_temp;
	int32_t			temp_w;
	
	temp_w = 0;
	if (rdst.w < 0)
	{
		temp_w = rdst.w;
		rdst.w = -rdst.w;
	}
	rdst_temp.w = SCALING_W(src->w) * rdst.w;
	rdst_temp.h = SCALING_H(src->h) * rdst.h;
	rdst_temp.x = rdst.x - SCALING_W(src->left_offset);
	rdst_temp.y = rdst.y - SCALING_H(src->top_offset);
	if (temp_w < 0)
	{
		rdst.w = -rdst.w;
	}
	rsrc = (t_rect){0, 0, src->w, src->h};
	while_scale_pic(src, &rsrc, dst, &rdst_temp);
}