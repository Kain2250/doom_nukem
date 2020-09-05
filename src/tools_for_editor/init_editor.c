/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_editor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/22 19:24:18 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/09/05 18:19:38 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

t_frames		*init_editor(t_doom_nukem *doom)
{
	t_frames	*frame_table;
	t_frames	*temp;
	t_rect		q;

	SDL_GetWindowSize(doom->sdl.window, &doom->sdl.width, &doom->sdl.height);
	q = rect_fill_no_malloc(0, 0, doom->sdl.width, 20);
	frame_table = new_frame(&q, 0x97989a, NULL);
	temp = frame_table;
	return (temp);
}
