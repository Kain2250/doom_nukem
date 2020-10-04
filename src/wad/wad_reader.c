/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wad_reader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 20:39:05 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/10/04 19:34:21 by bdrinkin         ###   ########.fr       */
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
		while (temp != NULL && ft_strcmp(name_map, temp->lump_name) != 0)
			temp = temp->next;
	while (temp != NULL && ft_strcmp(lable, temp->lump_name) != 0)
		temp = temp->next;
	if (temp == NULL)
	{
		put_error_sys("Error wadfile - could not find lumpname");
		exit (-1);
	}
	return (temp->lump_offset);
}

uint32_t		find_size_lump(t_dir *dir, char *lable, char *name_map)
{
	t_dir	*temp;

	temp = dir;
	if (name_map != NULL)
		while (temp != NULL && ft_strcmp(name_map, temp->lump_name) != 0)
			temp = temp->next;
	while (temp != NULL && ft_strcmp(lable, temp->lump_name) != 0)
		temp = temp->next;
	if (temp == NULL)
	{
		put_error_sys("Error wadfile - could not find lumpname");
		exit (-1);
	}
	return (temp->lump_size);
}

uint32_t		wad_find_texture(t_dir *dir, char *name)
{
	t_dir		*temp;

	temp = dir;
	while (temp != NULL && ft_strcmp(name, temp->lump_name) != 0)
		temp = temp->next;
	if (temp == NULL)
	{
		put_error_sys("Error wadfile - could not find texture");
		exit (-1);
	}
	return (temp->lump_offset);
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
	wad_get_vertex(doom, "E1M1");
	wad_get_linedefs(doom, "E1M1");
	wad_get_playpal(doom);
	wad_get_colormap(doom);
	wad_get_textures(doom->wad.map, find_offset_lump(doom->wad.dir, "TEXTURE1", NULL), &doom->wad.textures1);
	wad_get_pnames(doom->wad.map, doom->wad.dir, &doom->wad.pname);
	return (true);
}
