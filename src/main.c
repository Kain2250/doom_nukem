/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/15 06:55:31 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/09/26 15:00:38 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void				user_cursor(t_doom_nukem *doom)
{
	SDL_Cursor		*curs;

	curs = SDL_CreateColorCursor(doom->sdl.textures[texture_cursor0], 5, 1);
	SDL_SetCursor(curs);
}

int			**filemap(void)
{
	int		**arr;
	int		i;
	int		j;

	i = 0;
	arr = ft_memalloc(sizeof(int *) * 7);
	while (i != 7)
	{
		j = 0;
		arr[i] = ft_memalloc(sizeof(int) * 10);
		while (j != 10)
		{
			if ((i == 1 && j == 1) || (i == 1 && j == 3) || (i == 1 && j == 5) || (i == 1 && j == 8) ||
				(i == 2 && j == 3) || (i == 2 && j == 5) ||
				(i == 4 && j == 1) || (i == 4 && j == 4) || (i == 4 && j == 7) || (i == 4 && j == 8) ||
				(i == 5 && j == 4) || (i == 5 && j == 7))
				arr[i][j] = 1;
			else
				arr[i][j] = 0;
			j++;
		}
		i++;
	}
	return (arr);
}

// void				draw_map(t_doom_nukem *doom, int **arr)
// {
// 	int				i;
// 	int				j;

// 	i = -1;
// 	while (++i != 7)
// 	{
// 		j = -1;
// 		while (++j != 10)
// 		{
// 			if (arr[i][j] == 1)

// 		}
// 	}
// }

int					main(int ac, char **av)
{
	t_doom_nukem	*doom;
	t_timer			time;
	int				**map;

	if (ac == 1)
	{
		doom = ft_memalloc(sizeof(t_doom_nukem));
		init_lib_sdl(doom);
		if (load_res(doom) == false || wad_loader(doom, "map.wad") == false)
		{
			doom_exit(doom);
			return (0);
		}
		wad_reader(doom);
		SDL_GetWindowSize(doom->sdl.window, &doom->sdl.width, &doom->sdl.height);
		user_cursor(doom);
		SDL_SetWindowIcon(doom->sdl.window, doom->sdl.textures[texture_icon]);
		doom->screen = init_editor(doom);
		fill_limit(&doom->player.heals, 0, 190, 200);
		map = filemap();
		timer_start(&time);
		while (doom->quit == false)
		{
			// fps_counter(&time);
			// draw_map(doom, map);
			// frame_tamer(doom, doom->screen);
			event_list(doom);
			SDL_UpdateWindowSurface(doom->sdl.window);
			// clear_surface(doom->sdl.surface, 0);
		}
		doom_exit(doom);
	}
	else if (!av[1])
		ft_putendl(USAGE_DOOM);
	return (0);
}
