/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarc <mcarc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 19:38:55 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/08/20 18:48:02 by mcarc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor_map.h"

bool			editor_map(t_map_editor *map_editor)
{
	map_editor_event_list(map_editor);
	return (true);
}

void			draw_grid_lines_h(SDL_Surface *map, int grid_distance_x, Uint32 pixel)
{
	int x;
	int y;

	y = 0;
	while (y < map->h)
	{
		x = 0;
		while (x < map->w)
		{
			if (x != 0 && y != 0)
				putpixel(map, x, y, pixel);
			x += grid_distance_x * 2;
		}
		y++;
		pixel += 1.0;
	}
}

void			draw_grid_lines_v(SDL_Surface *map, int grid_distance_y, Uint32 pixel)
{
	int x;
	int y;

	y = grid_distance_y;
	y = 0;
	while (y < map->h)
	{
		x = 0;
		while (x < map->w)
		{
			if (x != 0 && y != 0)
				putpixel(map, x, y, pixel);
			x++;
			pixel += 1.1;
		}
		y += grid_distance_y * 2;
	}
}

void			zoom_map(t_map_editor *map_editor)
{
	SDL_Rect	rect;
	SDL_FRect	f_surf_rect;
	SDL_Rect	surf_rect;
	SDL_Surface *surface;
	SDL_FPoint	delta;
	static SDL_Point prev_mouse;

	surface = map_editor->field.surface;
	rect.h = (int)(HEIGHT_WIN * 0.6);
	rect.w = (int)(WIDTH_WIN * 0.6);
	rect.x = 0;//(int)(WIDTH_WIN * 0.2);
	rect.y = 0;//(int)(HEIGHT_WIN * 0.1);

	delta.x = (prev_mouse.x - map_editor->mouse.x) / map_editor->field.zoom;
		delta.y = (prev_mouse.y - map_editor->mouse.y) / map_editor->field.zoom;
		f_surf_rect.h = 1.0 * HEIGHT_WIN * 0.6 / map_editor->field.zoom;
		f_surf_rect.w = 1.0 * WIDTH_WIN * 0.6 / map_editor->field.zoom;
		surf_rect.h = (int)f_surf_rect.h;
		surf_rect.w = (int)f_surf_rect.w;
	// if (prev_mouse.x != map_editor->mouse.x || prev_mouse.y != map_editor->mouse.y)
	// {
	// 	delta.x = (prev_mouse.x - map_editor->mouse.x) / map_editor->field.zoom;
	// 	delta.y = (prev_mouse.y - map_editor->mouse.y) / map_editor->field.zoom;
	// 	prev_mouse.x = map_editor->mouse.x;
	// 	prev_mouse.y = map_editor->mouse.y;
	// }
	// else
	// {
	// 	delta.x = 0;
	// 	delta.y = 0;
	// }
	
		surf_rect.x = map_editor->mouse.x - ((map_editor->mouse.x) / map_editor->field.zoom);
		surf_rect.y = map_editor->mouse.y - ((map_editor->mouse.y) / map_editor->field.zoom);
	
	// else
	// {
	// 	surf_rect.x = 0;
	// 	surf_rect.y = 0;
	// 	f_surf_rect.h = 1.0 * HEIGHT_WIN * 0.6 / map_editor->field.zoom;
	// 	f_surf_rect.w = 1.0 * WIDTH_WIN * 0.6 / map_editor->field.zoom;
	// 	surf_rect.h = (int)f_surf_rect.h;
	// 	surf_rect.w = (int)f_surf_rect.w;
	// }
	clear_surface(map_editor->sdl.surface, 0);
	SDL_BlitScaled(surface, &surf_rect, map_editor->sdl.surface, &rect);
	
	SDL_UpdateWindowSurface(map_editor->sdl.window);
}

// void			zoom_map(t_map_editor *map_editor)
// {
// 	SDL_Rect	rect;
// 	SDL_FRect	f_surf_rect;
// 	SDL_Rect	surf_rect;
// 	SDL_Surface *surface;

// 	surface = map_editor->field.surface;
// 	rect.h = (int)(HEIGHT_WIN * 0.6);
// 	rect.w = (int)(WIDTH_WIN * 0.6);
// 	rect.x = 0;//(int)(WIDTH_WIN * 0.2);
// 	rect.y = 0;//(int)(HEIGHT_WIN * 0.1);

	
// 	if (map_editor->mouse.x >= (int)(WIDTH_WIN * 0.2) && map_editor->mouse.y >= (int)(HEIGHT_WIN * 0.1)
// 		&& map_editor->mouse.x <= (int)(WIDTH_WIN * 0.8) && map_editor->mouse.y <= (int)(HEIGHT_WIN * 0.7))
// 	{
// 		f_surf_rect.h = 1.0 * HEIGHT_WIN * 0.6 / map_editor->field.zoom;
// 		f_surf_rect.w = 1.0 * WIDTH_WIN * 0.6 / map_editor->field.zoom;
// 		surf_rect.h = (int)f_surf_rect.h;
// 		surf_rect.w = (int)f_surf_rect.w;
// 		surf_rect.x = (map_editor->mouse.x - (int)(WIDTH_WIN * 0.2)) - ((map_editor->mouse.x - (int)(WIDTH_WIN * 0.2)) / map_editor->field.zoom);
// 		surf_rect.y = (map_editor->mouse.y - (int)(HEIGHT_WIN * 0.1)) - ((map_editor->mouse.y - (int)(HEIGHT_WIN * 0.1)) / map_editor->field.zoom);
		
// 	}
// 	else
// 	{
// 		surf_rect.x = 0;
// 		surf_rect.y = 0;
// 		f_surf_rect.h = 1.0 * HEIGHT_WIN * 0.6 / map_editor->field.zoom;
// 		f_surf_rect.w = 1.0 * WIDTH_WIN * 0.6 / map_editor->field.zoom;
// 		surf_rect.h = (int)f_surf_rect.h;
// 		surf_rect.w = (int)f_surf_rect.w;
// 	}
// 	clear_surface(map_editor->sdl.surface, 0);
// 	SDL_BlitScaled(surface, &surf_rect, map_editor->sdl.surface, &rect);
	
// 	SDL_UpdateWindowSurface(map_editor->sdl.window);
// }

void			draw_grid_lines(SDL_Surface *map, int grid_distance_x, int grid_distance_y, Uint32 pixel)
{
	draw_grid_lines_h(map, grid_distance_x, pixel);
	draw_grid_lines_v(map, grid_distance_y, pixel);
}

void			draw_grid_dots(SDL_Surface *map, int grid_distance_x, int grid_distance_y, Uint32 pixel)
{
	int x;
	int y;

	y = 0;
	while (y < map->h)
	{
		x = 0;
		while (x < map->w)
		{
			if (x != 0 && y != 0)
			{
				putpixel(map, x, y, pixel);
				pixel += 1;
			}
			x += grid_distance_x * 2;
		}
		y += grid_distance_y * 2;
	}
}

void			draw_map_grid(SDL_Surface *map)
{
	int grid_distance_x;
	int grid_distance_y;
	Uint32 pixel;

	grid_distance_x = (int)(WIDTH_WIN * 0.6 / MAP_WIDTH);
	grid_distance_y = (int)(HEIGHT_WIN * 0.6 / MAP_HEIGHT);
	pixel = 0x010101;
	draw_grid_lines(map, grid_distance_x, grid_distance_y, pixel);
	// printf("map grid\n");
}

t_map_editor	*map_editor_init(t_doom_nukem *doom)
{
	t_map_editor *map_editor;
	
	if (!(map_editor = ft_memalloc(sizeof(t_map_editor))))
		return (NULL);
	if (!(map_editor->field.surface = SDL_CreateRGBSurface(0, (int)(WIDTH_WIN * 0.6), (int)(HEIGHT_WIN * 0.6), 32, 0, 0, 0, 0)))
		return (NULL);
	map_editor->sdl = doom->sdl;
	(void)doom;
	map_editor->field.zoom = 1;
	SDL_GetMouseState(&map_editor->mouse.x, &map_editor->mouse.y);
	draw_map_field(map_editor);
	return (map_editor);
}

void			draw_map_field(t_map_editor *map_editor)
{
	SDL_Rect	rect;
	SDL_Rect	surf_rect;
	SDL_Surface *surface;
	
	surface = map_editor->field.surface;
	rect.h = (int)(HEIGHT_WIN * 0.6);
	rect.w = (int)(WIDTH_WIN * 0.6);
	rect.x = 0;
	rect.y = 0;
	// rect.x = (int)(WIDTH_WIN * 0.2);
	// rect.y = (int)(HEIGHT_WIN * 0.1);
	

	surf_rect.h = (int)(HEIGHT_WIN * 0.6);
	surf_rect.w = (int)(WIDTH_WIN * 0.6);
	surf_rect.x = 0;
	surf_rect.y = 0;
//  printf("map field\n");
	SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 255, 255, 255));
	// printf("%d %d\n", surface->h, surface->w);
	draw_map_grid(surface);
	SDL_BlitScaled(surface, &surf_rect, map_editor->sdl.surface, &rect);
	SDL_UpdateWindowSurface(map_editor->sdl.window);

}

void			map_editor_event_list(t_map_editor *map_editor)
{
	SDL_Point	mouse;
	// SDL_Rect	rect;

	SDL_PumpEvents();
	
	const Uint8 *state = SDL_GetKeyboardState(NULL);
	SDL_GetMouseState(&mouse.x, &mouse.y);
	if (mouse.x != map_editor->mouse.x || mouse.y != map_editor->mouse.y)
	{
		map_editor->mouse.x = mouse.x;
		map_editor->mouse.y = mouse.y;
	}
	if (state[SDL_SCANCODE_UP] && map_editor->field.zoom <= 10)
	{
		map_editor->field.zoom += 0.01;
		zoom_map(map_editor);
	}
	if (state[SDL_SCANCODE_DOWN] && map_editor->field.zoom >= 1.01)
	{
		map_editor->field.zoom -= 0.01;
		zoom_map(map_editor);
	}
	
	// if (SDL_GetMouseState(&mouse.x, &mouse.y) /*& SDL_BUTTON(SDL_BUTTON_X1)*/)
	// {
	// 	map_editor->mouse.x = mouse.x;
	// 	map_editor->mouse.y = mouse.y;
	// 	printf("%d %d\n", map_editor->mouse.x, map_editor->mouse.y);
	// 	// clear_surface(doom->sdl.surface, 0x0);
	// 	// assig_rect(&rect, mouse, 100, 100);
	// 	// SDL_BlitScaled(doom->sdl.textures[texture_test], NULL, doom->sdl.surface, &rect);
	// 	// SDL_UpdateWindowSurface(doom->sdl.window);
	// }
	// if (event_exit(doom) == true)
	// 	doom->quit = true;
	// if (SDL_BUTTON(SDL_SCANCODE_UP))
	// 	map_editor->field.zoom++;
}