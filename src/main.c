/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/15 06:55:31 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/08/15 09:47:06 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

int					main(int ac, char **av)
{
	t_doom_nukem	*doom;
	t_timer			time;

	if (ac == 1)
	{
		doom = ft_memalloc(sizeof(t_doom_nukem));
		init_lib_sdl(doom);
		timer_start(&time);
		while (doom->quit == false)
		{
			event_list(doom);
			fps_counter(&time);
		}
		doom_exit(doom);
		(void)av;
	}
	else
		ft_putendl(USAGE_DOOM);
	return (0);
}
