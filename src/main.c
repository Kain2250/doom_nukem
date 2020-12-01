/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/15 06:55:31 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/12/01 21:10:34 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"


void				user_cursor(t_doom *doom)
{
	SDL_Cursor		*curs;

	curs = SDL_CreateColorCursor(doom->sdl.textures[texture_cursor0], 5, 1);
	SDL_SetCursor(curs);
}

void				wad_init_level(t_wad *wad, char *name_map)
{
	wad_get_things(wad, name_map);
	wad_get_linedefs(wad, name_map);
	wad_get_sidedefs(wad, name_map);
	wad_get_vertex(wad, name_map);
	wad_get_segs(wad, name_map);
	wad_get_ssectors(wad, name_map);
	wad_get_nodes(wad, name_map);
	wad_get_sectors(wad, name_map);
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

void				put_column(t_wad *wad, uint32_t offset,
							int x, t_sprite *sprite)
{
	uint16_t			iter;
	uint16_t			col;
	int					y_step;
	int					y_miss;

	y_step = wad->map[offset];
	y_miss = 0;
	col = wad->map[offset + 1];
	iter = 0;
	offset += 3;
	while (y_miss - 1 < sprite->h && wad->map[offset + 1] != 255)
	{
		sprite->pixel[y_step * sprite->w + x] = wad->color[wad->baff]
			[wad->colormap[wad->bright][wad->map[offset]]];
		++iter && ++offset && ++y_miss;
		if (iter == col && wad->map[offset + 1] != 255)
		{
			col = wad->map[offset + 2];
			y_step = wad->map[offset + 1];
			offset += 4;
			iter = 0;
		}
		else
			y_step++;
	}
}

void				draw_sprite(t_sprite *sprite, SDL_Surface *screen,
						t_rect rect)
{
	int				x;
	int				y;
	uint32_t		color;

	x = 0;
	rect.x -= sprite->left_offset;
	rect.y -= sprite->top_offset;
	while (x < sprite->w)
	{
		y = 0;
		while (y < sprite->h)
		{
			color = get_pixel_sprite(sprite, x, y);
			if (color == 0xFFFFFFFF)
			{
				++y;
				continue ;
			}
			putpixel(screen, rect.x + x, rect.y + y, color);
			++y;
		}
		++x;
	}
}

t_sprite			*sprite_create(t_wad *wad, char *name)
{
	t_sprite		*sprite;
	t_patch			patch;
	uint32_t		offset;
	int				x;

	if (!(sprite = (t_sprite *)ft_memalloc(sizeof(t_sprite))))
		return (NULL);
	offset = find_offset_lump(wad->dir, name, NULL);
	patch = wad_get_patch_info(wad->map, offset);
	sprite->name = name;
	sprite->h = patch.height;
	sprite->w = patch.width;
	sprite->left_offset = patch.left_offset;
	sprite->top_offset = patch.top_offset;
	sprite->pixel = (uint32_t *)malloc(sizeof(uint32_t) *
		(sprite->w * sprite->h));
	sprite->pixel = ft_memset(sprite->pixel, 0xFFFFFFFF,
		sizeof(uint32_t) * sprite->w * sprite->h);
	x = -1;
	while (++x < patch.width)
		put_column(wad, offset + patch.columnoffset[x], x, sprite);
	wad_destroy_patch(patch);
	return (sprite);
}

int					main(int ac, char **av)
{
	t_doom	*doom;

	// char			*name_map = {"E1M1"};

	if (ac == 2 || ac == 3)
	{
		doom = ft_memalloc(sizeof(t_doom));
		init_lib_sdl(doom);
		if (load_res(doom) == false | wad_loader(&doom->wad, av[1]) == false)
		{
			doom_exit(doom);
			return (0);
		}
		wad_reader(&doom->wad);
		// wad_init_level(&doom->wad, name_map);
		skin(doom);
		// doom->screen = init_editor(doom);

		t_sprite	**sprites;
		char		**name;
		int			i = -1;

		name = (char **)ft_memalloc(sizeof(char *) * (PEH));
		while (++i < PEH)
			name[i] = ft_memalloc(sizeof(char) * 9);
		name[0] = S_PEH_D;
		i = -1;
		sprites = (t_sprite **)ft_memalloc(sizeof(t_sprite *) * (PEH + 1));
		while (++i <= PEH)
			sprites[i] = (t_sprite *)ft_memalloc(sizeof(t_sprite));
		i = -1;
		while (++i < PEH)
			sprites[i] = sprite_create(&doom->wad, name[i]);
		sprites[i] = NULL;

		t_wad_hud *hud = init_hud(&doom->wad);

		timer_start(&doom->time);
		while (doom->quit == false)
		{
			// fps_counter(&doom->time);
			// frame_tamer(doom, doom->screen);
			// wad_draw_linedefs(doom->wad, doom->wad.vert, doom->sdl.surface, name_map);
			draw_line(doom->sdl.surface, (t_point){HALF_WIDTH, 0}, (t_point){HALF_WIDTH, HEIGHT_WIN}, 0xffffff);
			draw_line(doom->sdl.surface, (t_point){0, HALF_HEIGHT}, (t_point){WIDTH_WIN, HALF_HEIGHT}, 0xffffff);
			
			// blit_sprite_scale(enemy, doom->sdl.surface, &((t_rect){HALF_WIDTH, HALF_HEIGHT, 20, 20, false}));
			draw_sprite_anim(doom, sprites, 125, (t_rectf){HALF_WIDTH, HALF_WIDTH, 1, 1, false});
			// blit_gan_scaled(sprites[i], doom->sdl.surface);
			blit_hud_scaled(hud->stbar, doom->sdl.surface, NULL);
			blit_sprite_scale()

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
