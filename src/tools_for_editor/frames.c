/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frames.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/20 20:37:35 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/11/17 21:01:24 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

t_frames		*new_frame(t_rect rect, Uint32 color,
					struct s_block *blocks)
{
	t_frames	*src;

	src = (t_frames *)ft_memalloc(sizeof(t_frames));
	src->main_frame = rect_fill(rect.x, rect.y, rect.w, rect.h);
	src->color = color;
	src->blocks = blocks;
	src->next = NULL;
	return (src);
}

void			frame_tamer(t_doom *doom, t_frames *frame_table)
{
	t_frames	*temp;
	t_block		*temp_block;
	
	temp = frame_table;
	blit_surf_scaled(doom->sdl.textures[texture_editor_back],
		NULL, doom->sdl.surface, NULL);
	while (temp)
	{
		draw_feel_rect(doom->sdl.surface, temp->main_frame, temp->color, 1);
		temp_block = temp->blocks;
		while (temp_block)
		{
			blit_surf_scaled(temp_block->block_pic, NULL, doom->sdl.surface, temp_block->rect_block);
			temp_block = temp_block->next;
		}
		temp = temp->next;
	}
}
