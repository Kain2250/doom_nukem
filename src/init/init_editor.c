/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_editor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/22 19:24:18 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/12/12 16:15:22 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

t_block			*new_block(int type, t_rect rect, SDL_Surface *pic)
{
	t_block		*block;

	block = (t_block *)ft_xmemalloc(sizeof(t_block));
	block->type_block = type;
	block->block_pic = pic;
	block->rect_block = &(t_rect){rect.x, rect.y, rect.w, rect.h};
	return (block);
}

t_frames		*init_editor(t_doom *doom)
{
	t_frames	*frame_table;
	t_frames	*temp;
	t_block		*temp_block;
	t_rect		q;

	q = (t_rect){0, 0, doom->sdl.width, 20};
	frame_table = new_frame(q, 0x97989a, NULL);
	//Заполнение блоков
	q = (t_rect){20, 2, 16, 16};
	frame_table->blocks = new_block(1, q, doom->sdl.textures[texture_cursor0]);
	temp_block = frame_table->blocks;
	q = (t_rect){50, 2, 16, 16};
	temp_block->next = new_block(1, q, doom->sdl.textures[texture_cursor0]);
	temp_block = temp_block->next;
	
	temp = frame_table;

	return (temp);
}
