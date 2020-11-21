/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wad.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 19:43:10 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/11/21 16:34:20 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void			wad_put(char *name, int offset, int size)
{
	ft_putstr("Offset - ");
	ft_putnbr(offset);
	ft_putchar('\n');
	ft_putstr("Size - ");
	ft_putnbr(size);
	ft_putchar('\n');
	ft_putendl(name);
	ft_putchar('\n');
}

// void			wad_put_patch(t_doom *doom, char *texture, t_patches pth, t_point start)
// {
// 	uint32_t	offset;
// 	uint32_t	size;
// 	uint32_t	temp_offset;
// 	t_point		iter;
// 	t_patch		patch;
//
//
// 	offset = find_offset_lump(doom->wad.dir, texture, NULL);
// 	size = find_size_lump(doom->wad.dir, texture, NULL);
// 	patch = wad_get_patch_info(doom->wad.map, offset);
//
// 	iter.x = start.x + pth.origin_x;
// 	while (iter.x < patch.width + start.x)
// 	{
// 		iter.y = start.y + pth.origin_y;
// 		temp_offset = offset + patch.columnoffset[iter.x - (start.x + pth.origin_x)];
// 		while (iter.y < patch.height + start.y)
// 		{
// 			if (temp_offset > size + offset)
// 				break ;
// 			putpixel(doom->sdl.surface, iter.x, iter.y,
// 				doom->wad.color[doom->wad.baff]
// 				[doom->wad.colormap[doom->wad.bright]
// 				[doom->wad.map[temp_offset]]]);
// 			iter.y++;
// 			temp_offset += 1;
// 		}
// 		iter.x++;
// 	}
// }

uint32_t		rec_column(t_doom *doom, uint32_t offset, t_crd crd, SDL_Surface *surface)
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
	while (y_miss - 1 < doom->wad.temp_step && doom->wad.map[offset + 1] != 255)
	{
		putpixel(surface, crd.x, *crd.y + y_step,
			doom->wad.color[doom->wad.baff]
			[doom->wad.colormap[doom->wad.bright]
			[doom->wad.map[offset]]]);
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
	(*crd.y) += doom->wad.temp_step;
	return (offset + 2);
}

SDL_Surface		*wad_draw_patch(t_doom *doom, char *pnames, t_sprite *sprite)
{
	uint32_t	offset;
	t_patch		patch;
	int			i;
	t_point		start;
	SDL_Surface	*ret;

	i = 0;
	offset = find_offset_lump(doom->wad.dir, pnames, NULL);
	patch = wad_get_patch_info(doom->wad.map, offset);
	sprite->left_offset = patch.left_offset;
	sprite->top_offset = patch.top_offset;
	ret = SDL_CreateRGBSurfaceWithFormat(0, patch.width, patch.height,
		32, SDL_PIXELFORMAT_BGRA32);
	doom->wad.temp_step = patch.height;
	start.x = 0;
	while (i < patch.width)
	{
		start.y = 0;
		rec_column(doom, offset + patch.columnoffset[i++],
			(t_crd){start.x, &start.y}, ret);
		start.x++;
	}
	return (ret);
}



void			wad_draw_linedefs(t_doom *doom,
					t_vertex *vertex, char *name_map)
{
	uint16_t	i;
	uint32_t	color;
	uint32_t	size;

	size = find_size_lump(doom->wad.dir, "LINEDEFS", name_map);
	size /= 14;
	i = 0;
	while (i < size)
	{
		if (doom->wad.linedef[i].rear == 65535)
			color = 0x0000ff;
		else
			color = 0xffffff;
		if (doom->wad.linedef[i].type == 1)
			color = 0xff0000;
		draw_line(doom->sdl.surface,
			fill_point((vertex[doom->wad.linedef[i].start].x - doom->buf1) / 10,
					abs(vertex[doom->wad.linedef[i].start].y - doom->buf2) / 10),
			fill_point((vertex[doom->wad.linedef[i].finish].x - doom->buf1) / 10,
					abs(vertex[doom->wad.linedef[i].finish].y - doom->buf2) / 10), color);
		i++;
	}
}

