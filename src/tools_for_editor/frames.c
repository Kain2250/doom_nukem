/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frames.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/20 20:37:35 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/08/20 23:17:00 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

typedef struct		s_block
{
	SDL_Surface		*block_pic;
	SDL_Rect		rect_block;
	bool			is_push;
	struct s_block	*next;
}					t_block;

typedef struct		s_frames
{
	SDL_Rect		main_frame;
	SDL_Color		color;
	int				count_blocks;
	struct s_block	*blocks;
}					t_frames;

void				frame_tamer(t_doom_nukem *doom)
{
	t_frames		frame_table;

	frame_table.main_frame.x = 0;
	frame_table.main_frame.y = 0;
	frame_table.main_frame.w = 300;
	frame_table.main_frame.h = 800;
	draw_feel_rect(doom->sdl.surface, &frame_table.main_frame, 0xffffff);
	(void)doom;
}