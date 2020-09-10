/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/15 06:55:31 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/09/10 14:52:02 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void				user_cursor(t_doom_nukem *doom)
{
	SDL_Cursor		*curs;

	curs = SDL_CreateColorCursor(doom->sdl.textures[texture_iron], 1, 1);
	SDL_SetCursor(curs);
}

int					main(int ac, char **av)
{
	t_doom_nukem	*doom;
	t_timer			time;
	t_frames		*editor;
	t_rect			q;

	if (ac == 1)
	{
		editor = NULL;
		doom = ft_memalloc(sizeof(t_doom_nukem));
		init_lib_sdl(doom);
		if (load_res(doom) == false)
		{
			doom_exit(doom);
			return (0);
		}
		SDL_SetWindowIcon(doom->sdl.window, doom->sdl.textures[texture_icon]);
		SDL_GetWindowSize(doom->sdl.window, &doom->sdl.width, &doom->sdl.height);
		doom->screen = init_editor(doom);
		timer_start(&time);
		q.x = 500;
		q.y = 500;
		q.w = 200;
		q.h = 5;
		fill_limit(&doom->player.heals, 0, 190, 200);
		while (doom->quit == false)
		{
			// fps_counter(&time);
			frame_tamer(doom, doom->screen);
			event_list(doom);
			SDL_UpdateWindowSurface(doom->sdl.window);
			clear_surface(doom->sdl.surface, 0);
		}
		doom_exit(doom);
		free_editor(doom, editor);
	}
	else if (!av[1])
		ft_putendl(USAGE_DOOM);
	return (0);
}
