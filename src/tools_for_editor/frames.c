/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frames.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/20 20:37:35 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/08/28 17:01:29 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

t_frames			*new_frame(t_rect *rect(int x, int y, int w, int h), Uint32 color,
					struct s_block *blocks)
{
	t_frames		*src;

	src = (t_frames *)ft_memalloc(sizeof(t_frames));
	src->main_frame = rect;
	src->color = color;
	src->blocks = blocks;
	src->next = NULL;
	return (src);
}

t_rect				*rect_fill(int x, int y, int w, int h)
{
	t_rect			*rect;

	rect = (t_rect *)ft_memalloc(sizeof(t_rect));
	rect->x = x;
	rect->y = y;
	rect->w = w;
	rect->h = h;
	return (rect);
}

void				frame_tamer(t_doom_nukem *doom, t_frames *frame_table)
{
	t_frames		*temp;

	temp = frame_table;
	// blit_surf_scaled(doom->sdl.textures[texture_editor_back], NULL, doom->sdl.surface, NULL);
	while (temp)
	{
		// if (temp->next == NULL)
		// 	draw_feel_rect(doom->sdl.surface, &temp->main_frame, temp->color, 2);
		// else
		draw_feel_rect(doom->sdl.surface, temp->main_frame, temp->color, 2);
		
		temp = temp->next;
	}
}