/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarc <mcarc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/15 06:55:31 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/08/18 23:04:52 by mcarc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

int					main(int ac, char **av)
{
	t_doom_nukem	*doom;
	t_timer			time;
	t_map_editor	*map_editor;

	if (ac == 1)
	{
		doom = ft_memalloc(sizeof(t_doom_nukem));
		init_lib_sdl(doom);
		if (!(map_editor = map_editor_init(doom)))
			perror("map init\n");
		// load_res(doom);
		timer_start(&time);
		while (doom->quit == false)
		{
			editor_map(map_editor);
			// event_list(doom, map_editor);
			// fps_counter(&time);
		}
		doom_exit(doom);
		(void)av;
	}
	else
		ft_putendl(USAGE_DOOM);
	return (0);
}
