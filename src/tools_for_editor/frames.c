/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frames.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/20 20:37:35 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/08/24 22:09:17 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

t_frames			*new_frame(SDL_Rect *rect, Uint32 color,
					struct s_block *blocks)
{
	t_frames		*src;

	src = (t_frames *)ft_memalloc(sizeof(t_frames));
	src->main_frame = *rect;
	src->color = color;
	src->blocks = blocks;
	src->next = NULL;
	return (src);
}

void				blit_surface(SDL_Surface *src, SDL_Rect *rsrc, SDL_Surface *dst, SDL_Rect *rdst)
{
	register int	x[2];
	register int	y[2];
	register int	w[2];
	register int	h[2];
	double			delta_w;
	double			delta_h;
	double			i[2];
	bool			frees[2];

	frees[0] = false;
	frees[1] = false;
	if (rsrc == NULL)
	{
		rsrc = (SDL_Rect *)ft_memalloc(sizeof(SDL_Rect));
		rsrc->w = src->w;
		rsrc->h = src->h;
		frees[0] = true;
	}
	if (rdst == NULL)
	{
		rdst = (SDL_Rect *)ft_memalloc(sizeof(SDL_Rect));
		rdst->w = dst->w;
		rdst->h = dst->h;
		frees[1] = true;
	}
	if (rdst->h < rsrc->h)
	{
		delta_w = ((rsrc->w * 1.0) / (rdst->w * 1.0));
		delta_h = ((rsrc->h * 1.0) / (rdst->h * 1.0));
	}
	else if (rdst->h > rsrc->h)
	{
		delta_w = ((rdst->w * 1.0) / (rsrc->w * 1.0));
		delta_h = ((rdst->h * 1.0) / (rsrc->h * 1.0));
	}
	else if (rdst->h == rsrc->h)
	{
		delta_h = 1.0;
		delta_w = 1.0;
	}
	w[0] = rdst->w;
	w[1] = rsrc->w;
	h[0] = rdst->h;
	h[1] = rsrc->h;
	y[0] = rdst->y;
	y[1] = rsrc->y;
	i[1] = 0;
	i[0] = 0;
	while (y[0] <= h[0])
	{
		x[0] = rdst->x;
		x[1] = rsrc->x;
		while (x[0] <= w[0])
		{
			putpixel(dst, x[0], y[0], get_pixel(src, x[1], y[1]));
			if (rdst->w < rsrc->w)
				x[1] += (int)delta_w;
			else if (rdst->w > rsrc->w && i[1] >= delta_w)
			{
				i[1] = 0;
				x[1]++;
			}
			else
				i[1]++;
			x[0]++;
			// printf("x0 - %d, x1 - %d, y0 - %d, y1 - %d\n", x[0], x[1], y[0], y[1]);
		}
		if (rdst->h < rsrc->h)
			y[1] += delta_h;
		else if (rdst->h > rsrc->h && i[0] >= delta_h)
		{
			y[1]++;
			i[0] = 0;
		}
		else
			i[0]++;
		y[0]++;
		// printf("delta w - %f, Delta h - %f\n", delta_w, delta_h);
	}
	// printf("x0 - %d, x1 - %d, y0 - %d, y1 - %d\n", x[0], x[1], y[0], y[1]);
	if (frees[0])
		free(rsrc);
	if (frees[1])
		free(rdst);
}

void				frame_tamer(t_doom_nukem *doom, t_frames *frame_table)
{
	t_frames		*temp;
	
	temp = frame_table;
	SDL_BlitSurface(doom->sdl.textures[texture_editor_back], NULL, doom->sdl.surface, NULL);
	while (temp)
	{
		if (temp->next == NULL)
			draw_feel_rect(doom->sdl.surface, &temp->main_frame, temp->color, 2);
		else
			draw_feel_rect(doom->sdl.surface, &temp->main_frame, temp->color, 2);
		temp = temp->next;
	}
}