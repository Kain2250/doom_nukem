/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/15 06:55:31 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/11/25 23:39:04 by bdrinkin         ###   ########.fr       */
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

void				wad_destroy_patch(t_patch patch)
{
	if (patch.columnoffset)
		free(patch.columnoffset);
	ft_bzero(&patch, sizeof(patch));
}

static void				put_column(t_doom *doom, uint32_t offset,
							int x, t_sprite *sprite)
{
	uint16_t			iter;
	uint16_t			col;
	int					y_step;
	int					y_miss;

	y_step = doom->wad.map[offset];
	y_miss = 0;
	col = doom->wad.map[offset + 1];
	iter = 0;
	offset += 3;
	while (y_miss - 1 < sprite->h && doom->wad.map[offset + 1] != 255)
	{
		sprite->pixel[x * sprite->h + y_step] = doom->wad.color[doom->wad.baff]
			[doom->wad.colormap[doom->wad.bright]
			[doom->wad.map[offset]]];
		// put_pixel_sprite(sprite, x, y_step,
		// 	doom->wad.color[doom->wad.baff]
		// 	[doom->wad.colormap[doom->wad.bright]
		// 	[doom->wad.map[offset]]]);
		++iter;
		++offset;
		++y_miss;
		if (iter == col && doom->wad.map[offset + 1] != 255)
		{
			col = doom->wad.map[offset + 2];
			y_step = doom->wad.map[offset + 1];
			offset += 4;
			iter = 0;
		}
		else
			y_step++;
	}
}

t_sprite			*sprite_create(t_doom *doom, char *name)
{
	t_sprite		*sprite;
	t_patch			patch;
	uint32_t		offset;
	int				x;

	if (!(sprite = (t_sprite *)ft_memalloc(sizeof(t_sprite))))
		return (NULL);
	offset = find_offset_lump(doom->wad.dir, name, NULL);
	patch = wad_get_patch_info(doom->wad.map, offset);
	// sprite->name = ft_strcpy(sprite->name, name);
	sprite->h = patch.height;
	sprite->w = patch.width;
	sprite->left_offset = patch.left_offset;
	sprite->top_offset = patch.top_offset;
	sprite->pixel = (uint32_t *)malloc(sizeof(uint32_t) *
		(sprite->w * sprite->h));
	// sprite->pixel = ft_memset(sprite->pixel, 0xFFFFFFFF, sprite->w * sprite->h);
	x = -1;
	while (++x < patch.width)
		put_column(doom, offset + patch.columnoffset[x], x, sprite);
	wad_destroy_patch(patch);
	return (sprite);
}

int					main(int ac, char **av)
{
	t_doom	*doom;

	// char			*name_map = {"E1M6"};
	// SDL_Surface		*sprite[9];
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
		// texture = wad_draw_texture(doom, fill_point(0, 0), av[2]);

		t_sprite *sprites = sprite_create(doom, "SAWGD0");
		// int i = 0;

		// while (i < sprites->h)
		// {
		// 	int x = 0;
		// 	while (x < sprites->w)
		// 	{
		// 		putpixel(doom->sdl.surface, 800 + x, 800 + i, sprites->pixel[i * x]);
		// 		x++;
		// 	}
		// 	i++;
		// }
		// i = 0;
		// while (i < (int)sizeof(array) / 8)
		// {
		// 	sprite[i] = wad_draw_patch(doom, array[i], &doom->test[i]);
		// 	++i;
		// }
		// int k = 100;
		timer_start(&doom->time);
		while (doom->quit == false)
		{
			// fps_counter(&doom->time);
			frame_tamer(doom, doom->screen);
			// wad_draw_linedefs(doom, doom->wad.vert, name_map);
			// draw_sprite(doom, sprite, (t_rect){600, 500, 1, 1, false}, 100);
			// draw_sprite(doom, sprite, (t_rect){600 + k, 500, 1, 1, false}, 100);
			// draw_sprite(doom, sprite, (t_rect){600 + k + k, 500, 1, 1, false}, 100);
			// draw_sprite(doom, sprite, (t_rect){600 + k + k + k, 500, 1, 1, false}, 100);
			// draw_sprite(doom, sprite, (t_rect){600 + k + k + k, 500 + k, 1, 1, false}, 100);
			// draw_sprite(doom, sprite, (t_rect){600 + k + k + k, 500 + k + k, 1, 1, false}, 100);
			int x = 0;
			while (x < sprites->w)
			{
				int y = 0;
				while (y < sprites->h)
				{
					// if (sprites->pixel[i * sprites->w + x] == 0xFFFFFFFF)
					// {
					// 	++x;
					// 	continue;
					// }
					putpixel(doom->sdl.surface, 500 + x, 500 + y, sprites->pixel[y * sprites->w + x]);
					++y;
				}
				++x;
			}

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
