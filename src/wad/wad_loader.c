/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wad_loader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 17:28:31 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/11/17 21:01:24 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static size_t	wad_len(char *path)
{
	size_t		len;
	size_t		temp_len;
	int			fd;
	uint8_t		*wad_file;

	len = 0;
	fd = open(path, O_RDONLY);
	if (fd == -1)
		exit(put_error_sys("file_no_open") - 1);
	else
	{
		wad_file = (uint8_t *)ft_memalloc(50 * sizeof(uint8_t));
		temp_len = read(fd, wad_file, 50);
		if (temp_len > 5 && (ft_strnequ((char*)wad_file, "IWAD", 4)))
		{
			while (temp_len > 0)
			{
				len += temp_len;
				temp_len = read(fd, wad_file, 50);
			}
			free(wad_file);
		}
		else
			exit(put_error_sys("file_no_WAD") - 1);
	}
	close(fd);
	return (len);
}

static uint8_t	*wad_load(size_t size, char *path)
{
	uint8_t		*data;
	int			fd;

	data = NULL;
	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr("file_no_open\n");
		return (data);
	}
	data = (uint8_t *)malloc((size + 1) * sizeof(uint8_t));
	read(fd, data, size);
	close(fd);
	return (data);
}

bool			wad_loader(t_doom *doom, char *path)
{
	size_t		len_wad;

	len_wad = wad_len(path);
	doom->wad.map = wad_load(len_wad, path);
	if (doom->wad.map == NULL)
		return (false);
	return (true);
}
