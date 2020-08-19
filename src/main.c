/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/15 06:55:31 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/08/19 21:34:18 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

// void				user_cursor(void)
// {
// 	SDL_Cursor *curs;

// 	curs =  SDL_CreateColorCursor(doom->sdl.textures[texture_curs], 1, 1);
// 	SDL_SetCursor(curs);
// }

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
			// fps_counter(&time);
			editor_map(doom);
			event_list(doom);
			SDL_UpdateWindowSurface(doom->sdl.window);
			clear_surface(doom->sdl.surface, 0);
		}
		doom_exit(doom);
		(void)av;
	}
	else
		ft_putendl(USAGE_DOOM);
	return (0);
}
