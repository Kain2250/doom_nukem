/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wad.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kain2250 <kain2250@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 19:43:10 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/11/16 20:39:16 by kain2250         ###   ########.fr       */
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

void			wad_draw_patch(t_doom_nukem *doom, char *texture, t_patches pth, t_point start)
{
	uint32_t	offset;
	uint32_t	size;
	uint32_t	temp_offset;
	t_point		iter;
	t_patch		patch;
	

	offset = find_offset_lump(doom->wad.dir, texture, NULL);
	size = find_size_lump(doom->wad.dir, texture, NULL);
	patch = wad_get_patch_info(doom->wad.map, offset);

	iter.x = start.x + pth.origin_x;
	while (iter.x < patch.width + start.x)
	{
		iter.y = start.y + pth.origin_y;
		temp_offset = offset + patch.columnoffset[iter.x - (start.x + pth.origin_x)];
		while (iter.y < patch.height + start.y)
		{
			if (temp_offset > size + offset)
				break ;
			putpixel(doom->sdl.surface, iter.x, iter.y,
				doom->wad.color[doom->wad.baff]
				[doom->wad.colormap[doom->wad.bright]
				[doom->wad.map[temp_offset]]]);
			iter.y++;
			temp_offset += 1;
		}
		iter.x++;
	}
}

uint32_t		rec_column(t_doom_nukem *doom, uint32_t offset, int x, int *y)
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
	while (doom->wad.map[offset + 1] != 255)
	{
		putpixel(doom->sdl.surface, x, *y + y_step,
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
	(*y) += doom->wad.temp_step;
	return (offset + 2);
}

void			wad_compose_texture(t_doom_nukem *doom,
					t_map_texture pth, t_point start)
{
	int32_t		x, y;
	uint32_t	offset;
	uint32_t	temp_offset;
	uint32_t	i;
	t_patch		patch;
	uint16_t	x_temp, y_temp;

	i = 0;
	while (i < pth.patchcount)
	{
		offset = find_offset_lump(doom->wad.dir,
			doom->wad.pname.name[pth.patches[i].patch], NULL);
		patch = wad_get_patch_info(doom->wad.map, offset);
		doom->wad.temp_step = patch.height;
		x = (pth.patches[i].origin_x <= 0) ? start.x
			: start.x + pth.patches[i].origin_x;
		x_temp = x;
		while (x < patch.width + x_temp && x < pth.width + start.x)
		{
			temp_offset = offset + patch.columnoffset[x - x_temp];
			y = (pth.patches[i].origin_y <= 0) ? start.y
				: start.y + pth.patches[i].origin_y;
			y_temp = y;
			while (y < patch.height + y_temp && y < pth.height + start.y)
				temp_offset = rec_column(doom, temp_offset, x, &y);
			x++;
		}
		i++;
	}
}

void			wad_draw_texture(t_doom_nukem *doom,
					t_point start, char *texture)
{
	uint32_t	i;

	i = 0;
	if (texture == NULL)
		exit(put_error_sys("Enter texture name") - 1);
	while (i < doom->wad.textures1.num_texture &&
		ft_strcmp(doom->wad.textures1.mtexture[i].name, texture) != 0)
		i++;
	if (i >= doom->wad.textures1.num_texture)
	{
		i = 0;
		while (i < doom->wad.textures2.num_texture &&
			ft_strcmp(doom->wad.textures2.mtexture[i].name, texture) != 0)
			i++;
		if (i >= doom->wad.textures2.num_texture)
			exit (put_error_sys("Error WAD - could not find texture") * -1);
		wad_compose_texture(doom, doom->wad.textures2.mtexture[i], start);
	}
	else
		wad_compose_texture(doom, doom->wad.textures1.mtexture[i], start);	
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
			fill_point((vertex[doom->wad.linedef[i].start].x - doom->buf1) / 10,
					abs(vertex[doom->wad.linedef[i].start].y - doom->buf2) / 10),
			fill_point((vertex[doom->wad.linedef[i].finish].x - doom->buf1) / 10,
					abs(vertex[doom->wad.linedef[i].finish].y - doom->buf2) / 10), color);
		i++;
	}
}

