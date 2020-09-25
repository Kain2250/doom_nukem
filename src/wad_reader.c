/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wad_reader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 20:39:05 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/09/25 21:08:54 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void		read_head_data(const uint8_t *data, int offset, t_wad_head *head)
{
	head->wad_type[0] = data[offset];
	head->wad_type[1] = data[offset + 1];
	head->wad_type[2] = data[offset + 2];
	head->wad_type[3] = data[offset + 3];
	head->wad_type[4] = '\0';
	head->dir_count = bytes_to_int(data, offset + 4);
	head->dir_offset = bytes_to_int(data, offset + 8);
}

void		read_dir_data(const uint8_t *data, int offset, t_dir *dir)
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

void		wad_put(char *name, int offset, int size)
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

void		read_linedef(const uint8_t *data, int offset, t_linedef *linedef)
{
	linedef->start = bytes_to_short(data, offset);
	linedef->finish = bytes_to_short(data, offset + 2);
	linedef->flags = bytes_to_short(data, offset + 4);
	linedef->type = bytes_to_short(data, offset + 6);
	linedef->mark_sector = bytes_to_short(data, offset + 8);
	linedef->front = bytes_to_short(data, offset + 10);
	linedef->rear = bytes_to_short(data, offset + 12);
}

void	read_vertex(const uint8_t *data, int offset, t_vertex *vertex)
{
	vertex->x = bytes_to_short(data, offset);
	vertex->y = bytes_to_short(data, offset + 2);
}		

uint32_t	find_offset_lump(t_dir *dir, char *lable, char *name_map)
{
	t_dir	*temp;

	temp = dir;
	while (ft_strcmp(name_map, temp->lump_name) != 0)
		temp = temp->next;
	while (ft_strcmp(lable, temp->lump_name) != 0)
		temp = temp->next;
	return (temp->lump_offset);
}

uint32_t	find_size_lump(t_dir *dir, char *lable, char *name_map)
{
	t_dir	*temp;

	temp = dir;
	while (ft_strcmp(name_map, temp->lump_name) != 0)
		temp = temp->next;
	while (ft_strcmp(lable, temp->lump_name) != 0)
		temp = temp->next;
	return (temp->lump_size);
}

bool		wad_reader(t_doom_nukem *doom)
{
	t_dir	*temp;
	size_t	i;
	t_vertex *vertex;

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
	temp = doom->wad.dir;
	uint32_t 	offset = find_offset_lump(doom->wad.dir, "VERTEXES", "E1M1");
	uint32_t	size = find_size_lump(doom->wad.dir, "VERTEXES", "E1M1");
	vertex = (t_vertex *)ft_memalloc(size / 4 * sizeof(t_vertex));
	i = 0;
	uint32_t	temp_offset = offset + size;
	while (offset <= temp_offset)
	{
		read_vertex(doom->wad.map, offset, &vertex[i]);
		printf("x = %d y = %d\n", vertex[i].x, vertex[i].y);
		offset += 4;
		i++;
	}
	free(vertex);
	// while (temp != NULL)
	// {
	// 	wad_put(temp->lump_name, temp->lump_offset, temp->lump_size);
	// 	temp = temp->next;
	// }
	return (true);
}
