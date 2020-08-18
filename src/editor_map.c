/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarc <mcarc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 19:38:55 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/08/18 18:57:58 by mcarc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor_map.h"

bool			editor_map(t_doom_nukem *doom)
{
	SDL_Rect	q;
	t_map_editor *map_editor;

	q.h = 100;
	q.w = 400;
	q.x = 0;
	q.y = 0;
	if (!(map_editor = ft_memalloc(sizeof(t_map_editor))))
		return(false);
	map_editor->sdl = doom->sdl;
	(void)doom;
	draw_map_field(map_editor);
	return (true);
}

void			draw_map_grid(SDL_Surface *map)
{
	int x;
	int y;
	int grid_distance_x;
	int grid_distance_y;

	grid_distance_x = (int)(WIDTH_WIN * 0.6 / MAP_WIDTH);
	grid_distance_y = (int)(HEIGHT_WIN * 0.6 / MAP_HEIGHT);
	y = 0;
	SDL_LockSurface(map);
	while (y <= map->h)
	{
		x = 0;
		while (x <= map->w)
		{
			map->pixels[x + (y * map->pitch)] = (void)0;
            map->pixels[x + (y * map->pitch) + 1] = (void)0;
            map->pixels[x + (y * map->pitch) + 2] = (void)0;
			x += grid_distance_x + 3;
		}
		y += grid_distance_y;
	}
	SDL_UnlockSurface(map);
}

void			draw_map_field(t_map_editor *map_editor)
{
	SDL_Rect	rect;
	SDL_Rect	surf_rect;
	SDL_Surface *surface;

	surface = map_editor->field.surface;
	rect.h = (int)(HEIGHT_WIN * 0.6);
	rect.w = (int)(WIDTH_WIN * 0.6);
	rect.x = (int)(WIDTH_WIN * 0.2);
	rect.y = (int)(HEIGHT_WIN * 0.1);

	surf_rect.h = (int)(HEIGHT_WIN * 0.6);
	surf_rect.w = (int)(WIDTH_WIN * 0.6);
	surf_rect.x = 0;
	surf_rect.y = 0;

	surface = SDL_CreateRGBSurface(0, (int)(WIDTH_WIN * 0.6), (int)(HEIGHT_WIN * 0.6), 32, 0, 0, 0, 0);
	SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 255, 0, 0));
	draw_map_grid(surface);
	SDL_BlitScaled(surface, &surf_rect, map_editor->sdl.surface, &rect);
	SDL_UpdateWindowSurface(map_editor->sdl.window);
}
