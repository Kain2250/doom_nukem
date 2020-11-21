/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 14:35:50 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/11/21 19:32:16 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void				draw_sprite(t_doom *doom, SDL_Surface **sprite, t_rect rect, Uint32 delay)
{
	static int		i = 0;
	t_rect		new_rect;

	new_rect.x = rect.x / 4;
	new_rect.y = rect.y - sprite[i]->h * rect.h;
	new_rect.w = sprite[i]->w * rect.w;
	new_rect.h = sprite[i]->h * rect.h;
	new_rect.free = rect.free;
	blit_surf_scaled(sprite[i], NULL, doom->sdl.surface, &new_rect);
	if (get_ticks(&doom->time) >= delay)
	{
		++i;
		timer_stop(&doom->time);
		timer_start(&doom->time);
		if (sprite[i] == NULL)
			i = 0;
	}
}
