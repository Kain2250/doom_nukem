/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_editor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/22 19:24:18 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/08/24 20:42:23 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

t_frames			*init_editor(t_doom_nukem *doom)
{
	t_frames		*frame_table;
	t_frames		*temp;
	SDL_Rect		rect;
	SDL_Rect		canvas;

	SDL_GetWindowSize(doom->sdl.window, &doom->sdl.width, &doom->sdl.height);
	rect.x = 0;
	rect.y = 0;
	rect.w = doom->sdl.width / 5;
	rect.h = doom->sdl.height;
	canvas.x = rect.w;
	canvas.y = 0;
	frame_table = new_frame(&rect, 0xffffff, NULL);
	temp = frame_table;
	rect.x = frame_table->main_frame.w * 4;
	rect.y = 0;
	rect.w = frame_table->main_frame.w;
	rect.h = frame_table->main_frame.h;
	frame_table->next = new_frame(&rect, 0xffffff, NULL);
	frame_table = frame_table->next;
	rect.x = frame_table->main_frame.w + 1;
	rect.y = frame_table->main_frame.h / 5 * 4;
	canvas.h = rect.y;
	rect.h = doom->sdl.height / 5;
	rect.w = frame_table->main_frame.w * 3 - 2;
	canvas.w = rect.w + 1;
	frame_table->next = new_frame(&rect, 0xffffff, NULL);
	// frame_table = frame_table->next;
	// frame_table->next = new_frame(&canvas, 0x0, NULL);
	return (temp);
}
