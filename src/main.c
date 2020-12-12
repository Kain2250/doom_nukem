/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/15 06:55:31 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/12/12 20:59:20 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void			user_cursor(t_doom *doom)
{
	SDL_Cursor		*curs;

	curs = SDL_CreateColorCursor(doom->sdl.textures[texture_cursor0], 5, 1);
	SDL_SetCursor(curs);
}

void			skin(t_doom *doom)
{
	SDL_GetWindowSize(doom->sdl.window, &doom->sdl.width, &doom->sdl.height);
	user_cursor(doom);
	SDL_SetWindowIcon(doom->sdl.window, doom->sdl.textures[texture_icon]);
	fill_limit(&doom->player.health, 0, 100, 100);
	fill_limit(&doom->player.shield, 0, 0, 200);
	fill_limit(&doom->player.ammo[0], 0, 60, 200);
	fill_limit(&doom->player.ammo[1], 0, 10, 100);
	fill_limit(&doom->player.ammo[2], 0, 15, 50);
	fill_limit(&doom->player.ammo[3], 0, 11, 35);
	doom->player.cur_gan = 0;
}

void			wad_destroy_patch(t_patch patch)
{
	if (patch.columnoffset)
		free(patch.columnoffset);
	ft_bzero(&patch, sizeof(patch));
}

int				main(int ac, char **av)
{
	t_doom			*doom;

	if (ac == 2 || ac == 3)
	{
		doom = ft_xmemalloc(sizeof(t_doom));
		init_lib_sdl(doom);
		load_res(doom);
		skin(doom);
																				// doom->screen = init_editor(doom);
		doom->wad = init_wad(av[1]);
		timer_start(&doom->time);
		while (doom->quit == false)
		{
			wad_draw_menu(doom->sdl.surface, doom->wad);
																				// fps_counter(&doom->fps);
																				// frame_tamer(doom, doom->screen);
																				// wad_draw_linedefs(doom->wad, doom->wad.vert, doom->sdl.surface, name_map);
																				// draw_line(doom->sdl.surface, (t_point){HALF_WIDTH, 0}, (t_point){HALF_WIDTH, HALF_R_HEIGHT * 2}, 0xffffff);
																				// draw_line(doom->sdl.surface, (t_point){0, HALF_R_HEIGHT}, (t_point){WIDTH_WIN, HALF_R_HEIGHT}, 0xffffff);
			draw_sprite_anim(doom, doom->wad->sprites, 125, (t_rectf){HALF_WIDTH, HALF_WIDTH, -1, 1});
			draw_hud(doom->sdl.surface, doom->wad->hud, doom->player);
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
