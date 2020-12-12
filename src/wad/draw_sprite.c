/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 14:35:50 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/12/12 20:50:46 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	draw_sprite_sdl(t_doom *doom, SDL_Surface **sprite,
			t_rect rect, Uint32 delay)
{
	static int	i = 0;
	t_rect		new_rect;

	new_rect.x = rect.x / 4;
	new_rect.y = rect.y - sprite[i]->h * rect.h;
	new_rect.w = sprite[i]->w * rect.w;
	new_rect.h = sprite[i]->h * rect.h;
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

void	draw_gun_anim(t_doom *doom, t_wad_sprite **sprite, Uint32 delay)
{
	static int	i = 0;

	blit_gan_scaled(sprite[i], doom->sdl.surface);
	if (get_ticks(&doom->time) >= delay)
	{
		++i;
		timer_stop(&doom->time);
		timer_start(&doom->time);
		if (sprite[i] == NULL)
			i = 0;
	}
}

void	draw_sprite_anim(t_doom *doom, t_wad_sprite **sprite,
			Uint32 delay, t_rectf rect)
{
	static int	i = 0;
	

	blit_sprite_scale(sprite[i], doom->sdl.surface, rect);
	if (get_ticks(&doom->time) >= delay)
	{
		++i;
		if (sprite[i] == NULL)
			i = 0;
		timer_stop(&doom->time);
		timer_start(&doom->time);
	}
}

// void	wad_draw_sprite(SDL_Surface *screen, char *name, t_wad *wad, bool invers)
// {
	
// }
