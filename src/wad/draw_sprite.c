/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 14:35:50 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/12/21 19:52:07 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	draw_sprite_sdl(t_doom *doom, SDL_Surface **sprite,
			t_rect rect, Uint32 delay)
{
	t_rect		new_rect;
	static int	i = 0;

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

void	draw_sprite_anim(SDL_Surface *screen, t_wad_sprite **sprite, Uint32 delay, t_sub_sprite sub)
{
	static t_timer	time;
	static int		i = 0;
	
	if (!time_is_started(&time))
		timer_start(&time);
	blit_sprite_scaled(sprite[i], screen, sub);
	if (get_ticks(&time) >= delay)
	{
		i += 5;
		if (sprite[i] == NULL || i > peh_d8)
			i = 0;
		timer_stop(&time);
		timer_start(&time);
	}
}

int		clamp(int x, int min, int max)
{
	if (x < min)
		x = min;
	else if (x > max)
		x = max;
	return (x);
}

void	wad_draw_gun(SDL_Surface *screen, t_wad_sprite **sprite,
			Uint32 delay, t_sub_gun sub)
{
	static t_timer	time;
	static int		i = gun_b0;
	
	if ((!sub.status && i == gun_b0) || sub.ammo->cur == sub.ammo->min)
		blit_gan_scaled(sprite[gun_a0], screen);
	else if ((sub.status || i <= gun_e0) && sub.ammo->cur != sub.ammo->min)
	{
		if (!time_is_started(&time))
			timer_start(&time);
		blit_gan_scaled(sprite[i], screen);
		if (i == gun_d0)
			blit_gan_scaled(sprite[gun_f0], screen);
		if (get_ticks(&time) >= delay)
		{
			i++;
			if (sprite[i] == NULL || i > gun_e0)
			{
				i = gun_b0;
				sub.ammo->cur = clamp(sub.ammo->cur - 1, 0, sub.ammo->max);
			}
			timer_stop(&time);
			timer_start(&time);
		}
	}
}
