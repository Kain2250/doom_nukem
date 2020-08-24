/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/15 06:55:31 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/08/24 22:01:10 by bdrinkin         ###   ########.fr       */
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
	t_frames		*editor;

	if (ac == 1)
	{
		editor = NULL;
		doom = ft_memalloc(sizeof(t_doom_nukem));
		init_lib_sdl(doom);
		load_res(doom);
		editor = init_editor(doom);
		timer_start(&time);
		while (doom->quit == false)
		{
			fps_counter(&time);
			frame_tamer(doom, editor);
			// editor_map(doom);
			event_list(doom);
			// blit_surface(doom->sdl.textures[texture_test2], NULL, doom->sdl.surface, NULL);
			SDL_UpdateWindowSurface(doom->sdl.window);
			// clear_surface(doom->sdl.surface, 0);
		}
		doom_exit(doom);
		free_editor(doom, editor);
		(void)av;
	}
	else
		ft_putendl(USAGE_DOOM);
	return (0);
}
