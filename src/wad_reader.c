/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wad_reader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 20:39:05 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/10/02 18:32:54 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void			read_head_data(const uint8_t *data, int offset, t_wad_head *head)
{
	head->wad_type[0] = data[offset];
	head->wad_type[1] = data[offset + 1];
	head->wad_type[2] = data[offset + 2];
	head->wad_type[3] = data[offset + 3];
	head->wad_type[4] = '\0';
	head->dir_count = bytes_to_int(data, offset + 4);
	head->dir_offset = bytes_to_int(data, offset + 8);
}

void			read_dir_data(const uint8_t *data, int offset, t_dir *dir)
{
	dir->lump_offset = bytes_to_int(data, offset);
	dir->lump_size = bytes_to_int(data, offset + 4);
	dir->lump_name[0] = data[offset + 8];
	dir->lump_name[1] = data[offset + 9];
	dir->lump_name[2] = data[offset + 10];
	dir->lump_name[3] = data[offset + 11];
	dir->lump_name[4] = data[offset + 12];
	dir->lump_name[5] = data[offset + 13];
	dir->lump_name[6] = data[offset + 14];
	dir->lump_name[7] = data[offset + 15];
	dir->lump_name[8] = '\0';
}

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

void			read_linedef(const uint8_t *data, int offset, t_linedef *linedef)
{
	linedef->start = bytes_to_short(data, offset);
	linedef->finish = bytes_to_short(data, offset + 2);
	linedef->flags = bytes_to_short(data, offset + 4);
	linedef->type = bytes_to_short(data, offset + 6);
	linedef->mark_sector = bytes_to_short(data, offset + 8);
	linedef->front = bytes_to_short(data, offset + 10);
	linedef->rear = bytes_to_short(data, offset + 12);
}

void			read_vertex(const uint8_t *data, int offset, t_vertex *vertex)
{
	vertex->x = bytes_to_short(data, offset);
	vertex->y = bytes_to_short(data, offset + 2);
}		

uint32_t		find_offset_lump(t_dir *dir, char *lable, char *name_map)
{
	t_dir	*temp;

	temp = dir;
	if (name_map != NULL)
		while (ft_strcmp(name_map, temp->lump_name) != 0)
			temp = temp->next;
	while (ft_strcmp(lable, temp->lump_name) != 0)
		temp = temp->next;
	return (temp->lump_offset);
}

uint32_t		find_size_lump(t_dir *dir, char *lable, char *name_map)
{
	t_dir	*temp;

	temp = dir;
	if (name_map != NULL)
		while (ft_strcmp(name_map, temp->lump_name) != 0)
			temp = temp->next;
	while (ft_strcmp(lable, temp->lump_name) != 0)
		temp = temp->next;
	return (temp->lump_size);
}

void			wad_draw_linedefs(t_doom_nukem *doom,
					t_vertex *vertex, char *name_map)
{
	uint32_t 	offset;
	uint32_t	size;
	uint32_t	temp_offset;
	uint32_t	color;
	int			i;

	offset = find_offset_lump(doom->wad.dir, "LINEDEFS", name_map);
	size = find_size_lump(doom->wad.dir, "LINEDEFS", name_map);
	doom->wad.linedef = (t_linedef *)ft_memalloc(size / 14 * sizeof(t_linedef));
	temp_offset = offset + size;
	i = 0;
	while (offset < temp_offset)
	{
		read_linedef(doom->wad.map, offset, &doom->wad.linedef[i]);
		offset += 14;
		i++;
	}
	i = 0;
	while (i != size / 14)
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

void			wad_draw_vertex(t_doom_nukem *doom, char *name_map)
{
	uint32_t 	offset;
	uint32_t	size;
	uint32_t	temp_offset;
	int			i;

	i = 0;
	offset = find_offset_lump(doom->wad.dir, "VERTEXES", "E1M1");
	size = find_size_lump(doom->wad.dir, "VERTEXES", "E1M1");
	doom->wad.vert = (t_vertex *)ft_memalloc(size / 4 * sizeof(t_vertex));
	temp_offset = offset + size;
	while (offset < temp_offset)
	{
		read_vertex(doom->wad.map, offset, &doom->wad.vert[i]);
		offset += 4;
		i++;
	}
	// i = 0;
	// while (i != size / 4)
	// {
	// 	draw_fill_circl(doom->sdl.surface, 1, fill_point((vertex[i].x + 4000) / 5 - 400,
	// 								(vertex[i].y + 4000) / 5 + 300), 0xffffff);
	// 	i++;
	// }
	wad_draw_linedefs(doom, doom->wad.vert, name_map);
}

uint32_t		wad_find_texture(t_dir *dir, char *name)
{
	t_dir		*temp;

	temp = dir;
	while (ft_strcmp(name, temp->lump_name) != 0)
		temp = temp->next;
	return (temp->lump_offset);
}

void			wad_draw_texture(t_doom_nukem *doom, char *texture)
{
	uint32_t	offset;
	uint32_t	size;
	uint32_t	temp_offset;
	int			i, j;
	t_patch		patch;


	offset = find_offset_lump(doom->wad.dir, texture, NULL);
	size = find_size_lump(doom->wad.dir, texture, NULL);
	patch.width = bytes_to_short(doom->wad.map, offset);
	// printf("%d\n", patch.width);
	patch.height = bytes_to_short(doom->wad.map, offset + 2);
	// printf("%d\n", patch.height);
	patch.left_offset = bytes_to_short(doom->wad.map, offset + 4);
	// printf("%d\n", patch.left_offset);
	patch.top_offset = bytes_to_short(doom->wad.map, offset + 6);
	// printf("%d\n", patch.top_offset);
	patch.columnoffset = (uint32_t *)ft_memalloc(sizeof(uint32_t) + patch.width);
	i = 0;
	temp_offset = offset + 8;
	while (i < patch.width)
	{
		patch.columnoffset[i] = bytes_to_int(doom->wad.map, temp_offset);
		temp_offset += 4;
		i++;
	}
	i = 0;
	while (i < patch.width)
	{
		j = 0;
		temp_offset = offset + patch.columnoffset[i];
		while (j < patch.height)
		{
			printf("%d ", doom->wad.map[temp_offset]);
			putpixel(doom->sdl.surface, i, j, bytes_to_int(doom->wad.map, temp_offset));
			j++;
			temp_offset += 1;
		}
		printf("\n");
		i++;
	}
	// free(patch.columnoffset);
}

void			wad_draw_colormap(t_doom_nukem *doom)
{
	uint32_t	offset;
	uint32_t	size;
	uint32_t	temp_offset;
	uint32_t	i = 0;
	// t_color		playpal;
	// int			j = 10;

	offset = find_offset_lump(doom->wad.dir, "PLAYPAL", NULL);
	size = find_size_lump(doom->wad.dir, "PLAYPAL", NULL);
	temp_offset = offset;
	// printf("%d\n", offset);//bytes_to_int(doom->wad.map, temp_offset));
	uint32_t	k = 0;
	uint32_t	step;
	while (i < 56)
	{
		step = 0;
		// temp_offset = offset;
		while (step < 256)
		{
			// printf("int %d\n", (doom->wad.map[temp_offset + 2] << 16) | (doom->wad.map[temp_offset + 1] << 8) | doom->wad.map[temp_offset]);
			if (i == 13 || i == 28 || i == 43 || i == 55 || step == 255 || step == 511)
			{
				k = (doom->wad.map[temp_offset + 2] << 16) | (doom->wad.map[temp_offset + 1] << 8) | doom->wad.map[temp_offset];
				temp_offset += 3;
			}
			putpixel(doom->sdl.surface, step, i, k);
			// printf("%d ", doom->wad.color[i][step]);
			// k++;
			
			step++;
		}
		// printf("\n");
		// k += 1;
		i++;
	}
}

bool			wad_reader(t_doom_nukem *doom)
{
	t_dir		*temp;
	size_t		i;

	i = -1;
	read_head_data(doom->wad.map, 0, &doom->wad.head);
	doom->wad.dir = (t_dir *)ft_memalloc(sizeof(t_dir));
	temp = doom->wad.dir;
	while (++i < doom->wad.head.dir_count)
	{
		read_dir_data(doom->wad.map, doom->wad.head.dir_offset + i * 16, temp);
		if (i + 1 != doom->wad.head.dir_count)
		{
			temp->next = (t_dir *)ft_memalloc(sizeof(t_dir));
			temp = temp->next;
		}
	}
	wad_draw_vertex(doom, "E1M1");
	// wad_draw_texture(doom, "TITLEPIC");
	// wad_draw_texture(doom, "PLAYPAL");
	wad_draw_colormap(doom);
	return (true);
}
