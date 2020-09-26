/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wad_reader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 20:39:05 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/09/26 15:53:20 by bdrinkin         ###   ########.fr       */
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
	while (ft_strcmp(name_map, temp->lump_name) != 0)
		temp = temp->next;
	while (ft_strcmp(lable, temp->lump_name) != 0)
		temp = temp->next;
	return (temp->lump_size);
}

void			wad_draw_linedefs(t_doom_nukem *doom, t_vertex *vertex)
{
	t_linedef	*line;
	uint32_t 	offset;
	uint32_t	size;
	uint32_t	temp_offset;
	int			i = 0;

	offset = find_offset_lump(doom->wad.dir, "LINEDEFS", "E1M1");
	size = find_size_lump(doom->wad.dir, "LINEDEFS", "E1M1");
	line = (t_linedef *)ft_memalloc(size / 14 * sizeof(t_linedef));
	temp_offset = offset + size;
	while (offset < temp_offset)
	{
		read_linedef(doom->wad.map, offset, &line[i]);
		offset += 14;
		i++;
	}
	i = 0;
	while (i != size / 14)
	{
		draw_line(doom->sdl.surface, fill_point(abs(vertex[line[i].start].x) / 5 + 100 , abs(vertex[line[i].start].y)  / 5 - 100),
									fill_point(abs(vertex[line[i].finish].x)  / 5 + 100, abs(vertex[line[i].finish].y)  / 5 - 100),
									0xffffff);
		i++;
	}
	free(line);
}

void			wad_draw_vertex(t_doom_nukem *doom)
{
	t_vertex	*vertex;
	uint32_t 	offset;
	uint32_t	size;
	uint32_t	temp_offset;
	int			i;

	i = 0;
	offset = find_offset_lump(doom->wad.dir, "VERTEXES", "E1M1");
	size = find_size_lump(doom->wad.dir, "VERTEXES", "E1M1");
	vertex = (t_vertex *)ft_memalloc(size / 4 * sizeof(t_vertex));
	temp_offset = offset + size;
	while (offset < temp_offset)
	{
		read_vertex(doom->wad.map, offset, &vertex[i]);
		offset += 4;
		i++;
	}
	i = 0;
	while (i != size / 4)
	{
		putpixel(doom->sdl.surface, abs(vertex[i].x) / 5 + 100,
									abs(vertex[i].y) / 5 - 100, 0xffffff);
		i++;
	}
	wad_draw_linedefs(doom, vertex);
	// free(vertex);
}


bool			wad_reader(t_doom_nukem *doom)
{
	t_dir		*temp;
	size_t		i;

	i = -1;
	read_head_data(doom->wad.map, 0, &doom->wad.head);
	// wad_put(doom->wad.head.wad_type,
		// doom->wad.head.dir_offset, doom->wad.head.dir_count);
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
	wad_draw_vertex(doom);

	return (true);
}
