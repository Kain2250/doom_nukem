/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frames.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/20 20:37:35 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/09/09 20:18:18 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

t_frames		*new_frame(t_rect *rect, Uint32 color,
					struct s_block *blocks)
{
	t_frames	*src;

	src = (t_frames *)ft_memalloc(sizeof(t_frames));
	src->main_frame = (t_rect *)ft_memalloc(sizeof(t_rect));
	src->main_frame->x = rect->x;
	src->main_frame->y = rect->y;
	src->main_frame->w = rect->w;
	src->main_frame->h = rect->h;
	src->color = color;
	src->blocks = blocks;
	src->next = NULL;
	return (src);
}

t_rect			*rect_fill(int x, int y, int w, int h)
{
	t_rect		*rect;

	rect = (t_rect *)ft_memalloc(sizeof(t_rect));
	rect->x = x;
	rect->y = y;
	rect->w = w;
	rect->h = h;
	rect->free = true;
	return (rect);
}

void			frame_tamer(t_doom_nukem *doom, t_frames *frame_table)
{
	t_frames	*temp;
	
	temp = frame_table;
	blit_surf_scaled(doom->sdl.textures[texture_editor_back],
		NULL, doom->sdl.surface, NULL);
	while (temp)
	{
		draw_feel_rect(doom->sdl.surface, temp->main_frame, temp->color, 0);
		if (temp->blocks != NULL)
			put_slide_bar(doom->sdl.surface, temp->blocks->rect_block, &doom->player.heals, 0xffffff);
		temp = temp->next;
	}
}
