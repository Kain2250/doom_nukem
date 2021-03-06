/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 14:40:45 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/11/26 21:13:46 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static void	button_rigth_event(t_doom *doom)
{
	(void)doom;
	// scale_frame(doom->sdl.surface, doom->mouse, 0x00ff00, draw_rect);
}

static void	button_left_event(t_doom *doom)
{
	(void)doom;
	// if (is_slidebar_area(doom->screen->blocks->rect_block, doom->mouse))
	// 	doom->player.heals.cur =
	// 	doom->mouse.x - doom->screen->blocks->rect_block->x;
	// else
	// 	scale_frame(doom->sdl.surface, doom->mouse, 0xabfbc, &draw_feel_rect);
}

static void	button_midle_event(t_doom *doom)
{
	(void)doom;
	// drag_and_drop(doom->sdl.textures[texture_test], doom->sdl.surface);
}

void		mouse_events(t_doom *doom)
{
	int		button;

	is_mouse_presed(&doom->mouse);
	button = which_button(&doom->mouse.is_presed);
	if (SDL_BUTTON_RIGHT == button)
		button_rigth_event(doom);
	else if (SDL_BUTTON_LEFT == button)
		button_left_event(doom);
	else if (SDL_BUTTON_MIDDLE == button)
		button_midle_event(doom);
}
