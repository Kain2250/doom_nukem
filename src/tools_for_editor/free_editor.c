/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_editor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/22 19:25:49 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/08/22 20:02:25 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void				free_editor(t_doom_nukem *doom, t_frames *frame_table)
{
	t_frames		*temp;

	while (frame_table)
	{
		temp = frame_table->next;
		free(frame_table);
		frame_table = temp;
	}
	(void)doom;
}