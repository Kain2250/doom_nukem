/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_editor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/22 19:25:49 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/09/10 15:20:53 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void				free_editor(t_frames *frame_table)
{
	t_frames		*temp;
	t_block			*temp_block;

	while (frame_table)
	{
		temp = frame_table->next;
		if (frame_table->blocks)
		{
			while (frame_table->blocks)
			{
				temp_block = frame_table->blocks->next;
				free(frame_table->blocks);
				frame_table->blocks = temp_block;
			}
		}
		free(frame_table);
		frame_table = temp;
	}
}
