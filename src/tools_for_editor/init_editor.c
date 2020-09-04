/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_editor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/22 19:24:18 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/09/04 15:51:44 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"


t_frames			*init_editor(t_doom_nukem *doom)
{
	t_frames		*frame_table;
	t_frames		*temp;
	// t_rect			canvas;
	t_rect			q;;

	SDL_GetWindowSize(doom->sdl.window, &doom->sdl.width, &doom->sdl.height);
	// q = oblast(0, 0, doom->sdl.width / 5, doom->sdl.height);
	q = rect_fill_no_malloc(0, 0, doom->sdl.width, 20);
	frame_table = new_frame(&q, 0x97989a, NULL);
	// canvas.x = frame_table->main_frame->w;
	// canvas.y = 0;
	temp = frame_table;
	// q = rect_fill_no_malloc(frame_table->main_frame->w * 4, 0, frame_table->main_frame->w, frame_table->main_frame->h);
	// frame_table->next = new_frame(&q, 0xffffff, NULL);
	// frame_table = frame_table->next;
	// q = rect_fill_no_malloc(frame_table->main_frame->w + 1, frame_table->main_frame->h / 5 * 4, doom->sdl.width / 5 * 3, frame_table->main_frame->h / 5);
	// frame_table->next = new_frame(&q, 0xffff0f, NULL);
	// frame_table = frame_table->next;
	// canvas.h = frame_table->main_frame->y;
	// canvas.w = frame_table->main_frame->w + 1;

	// frame_table->next = new_frame(&canvas, 0x0, NULL);

	return (temp);
}
