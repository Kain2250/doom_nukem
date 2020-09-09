/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_editor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/22 19:24:18 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/09/09 20:19:38 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

t_frames		*init_editor(t_doom_nukem *doom)
{
	t_frames	*frame_table;
	t_frames	*temp;
	t_rect		q;

	q = rect_fill_no_malloc(0, 0, doom->sdl.width, 20);
	frame_table = new_frame(&q, 0x97989a, NULL);
	frame_table->blocks = (t_block *)ft_memalloc(sizeof(t_block));
	frame_table->blocks->rect_block = rect_fill(500, 500, 200, 5);
	temp = frame_table;
	return (temp);
}
