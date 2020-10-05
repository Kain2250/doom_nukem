/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wad.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 19:43:10 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/10/05 16:27:26 by bdrinkin         ###   ########.fr       */
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

void			wad_draw_patch(t_doom_nukem *doom, char *texture, t_point start)
{
	uint32_t	offset;
	uint32_t	size;
	uint32_t	temp_offset;
	t_point		iter;
	t_patch		patch;

	offset = find_offset_lump(doom->wad.dir, texture, NULL);
	size = find_size_lump(doom->wad.dir, texture, NULL);
	patch = wad_get_patch_info(doom->wad.map, offset);
	iter.x = start.x;
	while (iter.x < patch.width + start.x)
	{
		iter.y = start.y;
		temp_offset = offset + patch.columnoffset[iter.x];
		while (iter.y < patch.height + start.y)
		{
			if (temp_offset > size + offset)
				break ;
			putpixel(doom->sdl.surface, iter.x, iter.y, doom->wad.color[doom->wad.baff][doom->wad.colormap[doom->wad.bright][doom->wad.map[temp_offset]]]);
			iter.y++;
			temp_offset += 1;
		}
		iter.x++;
	}
}

void			wad_draw_texture(t_doom_nukem *doom, t_point start, char *texture)
{
	uint32_t	i;
	uint32_t	j;

	i = 0;
	while (i < doom->wad.textures1.num_texture &&
		ft_strcmp(doom->wad.textures1.mtexture[i].name, texture) != 0)
		i++;
	if (i - 1 > doom->wad.textures1.num_texture)
	{
		put_error_sys("Error WAD - could not find texture");
		exit (-1);
	}
	j = i; 
	while (i < doom->wad.textures1.mtexture[j].patchcount)
		wad_draw_patch(doom, doom->wad.pname.name[doom->wad.textures1.mtexture[j].patches[i++].patch], start);
}

void			wad_draw_linedefs(t_doom_nukem *doom,
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
			fill_point((vertex[doom->wad.linedef[i].start].x) / 5 + 200,
					abs(vertex[doom->wad.linedef[i].start].y) / 5),
			fill_point((vertex[doom->wad.linedef[i].finish].x) / 5 + 200,
					abs(vertex[doom->wad.linedef[i].finish].y) / 5), color);
		i++;
	}
}

