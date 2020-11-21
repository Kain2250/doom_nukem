/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/15 06:55:31 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/11/21 21:35:03 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"


void				user_cursor(t_doom *doom)
{
	SDL_Cursor		*curs;

	curs = SDL_CreateColorCursor(doom->sdl.textures[texture_cursor0], 5, 1);
	SDL_SetCursor(curs);
}

void				wad_init_level(t_doom *doom, char *name_map)
{
	wad_get_things(doom, name_map);
	wad_get_linedefs(doom, name_map);
	wad_get_sidedefs(doom, name_map);
	wad_get_vertex(doom, name_map);
	wad_get_segs(doom, name_map);
	wad_get_ssectors(doom, name_map);
	wad_get_nodes(doom, name_map);
	wad_get_sectors(doom, name_map);
}

void				skin(t_doom *doom)
{
	SDL_GetWindowSize(doom->sdl.window, &doom->sdl.width, &doom->sdl.height);
	user_cursor(doom);
	SDL_SetWindowIcon(doom->sdl.window, doom->sdl.textures[texture_icon]);
	fill_limit(&doom->player.heals, 0, 190, 200);
}



int					main(int ac, char **av)
{
	t_doom	*doom;

	// char			*name_map = {"E1M6"};
	SDL_Surface		*sprite[9];
	// SDL_Surface		*texture;

	if (ac == 2 || ac == 3)
	{
		doom = ft_memalloc(sizeof(t_doom));
		init_lib_sdl(doom);
		if (load_res(doom) == false || wad_loader(doom, av[1]) == false)
		{
			doom_exit(doom);
			return (0);
		}
		wad_reader(doom);
		// wad_init_level(doom, name_map);
		skin(doom);
		doom->screen = init_editor(doom);
		doom->wad.baff = 0;
		doom->wad.bright = 0;
		t_sprite *sprites = (t_sprite *)ft_memalloc(sizeof(t_sprite));
		// texture = wad_draw_texture(doom, fill_point(0, 0), av[2]);

		int i = 0;
		while (i < (int)sizeof(array) / 8)
		{
			sprite[i] = wad_draw_patch(doom, array[i], &doom->test[i]);
			++i;
		}
		int k = 100;
		timer_start(&doom->time);
		while (doom->quit == false)
		{
			// fps_counter(&doom->time);
			frame_tamer(doom, doom->screen);
			// wad_draw_linedefs(doom, doom->wad.vert, name_map);
			draw_sprite(doom, sprite, (t_rect){600, 500, 1, 1, false}, 100);
			draw_sprite(doom, sprite, (t_rect){600 + k, 500, 1, 1, false}, 100);
			draw_sprite(doom, sprite, (t_rect){600 + k + k, 500, 1, 1, false}, 100);
			draw_sprite(doom, sprite, (t_rect){600 + k + k + k, 500, 1, 1, false}, 100);
			draw_sprite(doom, sprite, (t_rect){600 + k + k + k, 500 + k, 1, 1, false}, 100);
			draw_sprite(doom, sprite, (t_rect){600 + k + k + k, 500 + k + k, 1, 1, false}, 100);

			event_list(doom);
			// SDL_RenderPresent(doom->sdl.render);
			SDL_UpdateWindowSurface(doom->sdl.window);
			clear_surface(doom->sdl.surface, 0);
		}
		doom_exit(doom);
	}
	else if (!av[1])
		ft_putendl(USAGE_DOOM);
	return (0);
}
