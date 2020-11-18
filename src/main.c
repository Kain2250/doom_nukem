/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/15 06:55:31 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/11/18 21:20:25 by bdrinkin         ###   ########.fr       */
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

int					main(int ac, char **av)
{
	t_doom	*doom;
	t_timer			time;
	t_timer			fps;

	char			*name_map = {"E1M6"};
	SDL_Surface		*sprite[8];
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
		wad_init_level(doom, name_map);
		SDL_GetWindowSize(doom->sdl.window, &doom->sdl.width, &doom->sdl.height);
		user_cursor(doom);
		SDL_SetWindowIcon(doom->sdl.window, doom->sdl.textures[texture_icon]);
		doom->screen = init_editor(doom);
		fill_limit(&doom->player.heals, 0, 190, 200);
		timer_start(&time);
		// texture = wad_draw_texture(doom, fill_point(0, 0), av[2]);
		sprite[0] = wad_draw_patch(doom, fill_point(0, 0), "CYBRG1");
		sprite[1] = wad_draw_patch(doom, fill_point(0, 0), "CYBRG2");
		sprite[2] = wad_draw_patch(doom, fill_point(0, 0), "CYBRG3");
		sprite[3] = wad_draw_patch(doom, fill_point(0, 0), "CYBRG4");
		sprite[4] = wad_draw_patch(doom, fill_point(0, 0), "CYBRG5");
		sprite[5] = wad_draw_patch(doom, fill_point(0, 0), "CYBRG6");
		sprite[6] = wad_draw_patch(doom, fill_point(0, 0), "CYBRG7");
		sprite[7] = wad_draw_patch(doom, fill_point(0, 0), "CYBRG8");
		int	i = 0;
		timer_start(&fps);
		while (doom->quit == false)
		{
			fps_counter(&time);
			frame_tamer(doom, doom->screen);
			// wad_draw_linedefs(doom, doom->wad.vert, name_map);
			blit_surf_scaled(sprite[i], NULL, doom->sdl.surface, &((t_rect){500 - sprite[i]->w * 2 / 2 , 500 - sprite[i]->h * 2 / 2, sprite[i]->w * 2, sprite[i]->h * 2, false}));
			if (get_ticks(&fps) >= 100)
			{
				++i;
				timer_stop(&fps);
				timer_start(&fps);
				if (i >= 8)
					i = 0;
			}
			event_list(doom);
			SDL_UpdateWindowSurface(doom->sdl.window);
			clear_surface(doom->sdl.surface, 0);
		}
		doom_exit(doom);
	}
	else if (!av[1])
		ft_putendl(USAGE_DOOM);
	return (0);
}
