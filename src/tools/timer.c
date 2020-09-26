/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 14:15:36 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/08/15 09:11:27 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

Uint32		get_ticks(t_timer *time)
{
	Uint32	time_temp;

	time_temp = 0;
	if (time->started)
	{
		if (time->paused)
			time_temp = time->paused_ticks;
		else
			time_temp = SDL_GetTicks() - time->start_ticks;
	}
	return (time_temp);
}

bool		time_is_started(t_timer *time)
{
	return (time->started);
}

bool		time_is_paused(t_timer *time)
{
	return (time->paused);
}

void		fps_counter(t_timer *time)
{
	if (get_ticks(time) >= 1000)
	{
		ft_putstr("FPS: ");
		ft_putnbr(time->counted_frames);
		ft_putchar('\n');
		timer_stop(time);
		timer_start(time);
		time->counted_frames = 0;
	}
	else
		time->counted_frames++;
}
