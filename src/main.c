/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarc <mcarc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/15 06:55:31 by bdrinkin          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2020/08/18 17:48:44 by mcarc            ###   ########.fr       */
=======
/*   Updated: 2020/08/18 17:15:03 by bdrinkin         ###   ########.fr       */
>>>>>>> 277554ca838e4d226c77240317edbe9fca3a18e2
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
		load_res(doom);
		timer_start(&time);
		while (doom->quit == false)
		{
			// editor_map(doom);
			event_list(doom);
			// fps_counter(&time);
		}
		doom_exit(doom);
		(void)av;
	}
	else
		ft_putendl(USAGE_DOOM);
	return (0);
}
