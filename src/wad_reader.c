/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wad_reader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 20:39:05 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/09/24 21:27:17 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void		read_head_data(const uint8_t *data, int offset, t_wad *head)
{
	head->wad_type[0] = data[offset];
	head->wad_type[1] = data[offset + 1];
	head->wad_type[2] = data[offset + 2];
	head->wad_type[3] = data[offset + 3];
	head->wad_type[4] = '\0';
	head->dir_count = bytes_to_int(data, offset + 4);
	head->dir_offset = bytes_to_int(data, offset + 8);
	ft_putendl(head->wad_type);
	ft_putnbr(head->dir_count);
	ft_putchar('\n');
	ft_putnbr(head->dir_offset);
	ft_putchar('\n');
	ft_putchar('\n');

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
	ft_putnbr(dir->lump_offset);
	ft_putchar('\n');
	ft_putnbr(dir->lump_size);
	ft_putchar('\n');
	ft_putendl(dir->lump_name);
	ft_putchar('\n');

}

bool		wad_reader(t_doom_nukem *doom)
{
	t_wad	head;
	t_dir	directory;
	size_t	i;

	i = -1;
	read_head_data(doom->map, 0, &head);
	while (++i < head.dir_count)
		read_dir_data(doom->map, head.dir_offset + i * 16, &directory);
	// ft_putendl(head.wad_type);
	// ft_putnbr(head.dir_count);
	// ft_putchar('\n');
	// ft_putnbr(head.dir_offset);
	// ft_putchar('\n');
	return (true);
}