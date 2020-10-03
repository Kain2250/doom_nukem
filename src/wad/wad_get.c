/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wad_get.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 19:49:40 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/10/03 20:52:42 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void			wad_get_linedefs(t_doom_nukem *doom, char *name_map)
{
	uint32_t 	offset;
	uint32_t	size;
	uint32_t	temp_offset;
	uint16_t	i;

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
}

void			wad_get_vertex(t_doom_nukem *doom, char *name_map)
{
	uint32_t 	offset;
	uint32_t	size;
	uint32_t	temp_offset;
	int			i;

	i = 0;
	offset = find_offset_lump(doom->wad.dir, "VERTEXES", name_map);
	size = find_size_lump(doom->wad.dir, "VERTEXES", name_map);
	doom->wad.vert = (t_vertex *)ft_memalloc(size / 4 * sizeof(t_vertex));
	temp_offset = offset + size;
	while (offset < temp_offset)
	{
		read_vertex(doom->wad.map, offset, &doom->wad.vert[i]);
		offset += 4;
		i++;
	}
}

t_patch			wad_get_patch_info(const uint8_t *data,	uint32_t offset)
{
	t_patch		patch;
	uint32_t	temp_offset;
	int			i;

	patch.width = bytes_to_short(data, offset);
	patch.height = bytes_to_short(data, offset + 2);
	patch.left_offset = bytes_to_short(data, offset + 4);
	patch.top_offset = bytes_to_short(data, offset + 6);
	patch.columnoffset = (uint32_t *)ft_memalloc(sizeof(uint32_t) +
		patch.width);
	i = 0;
	temp_offset = offset + 8;
	while (i < patch.width)
	{
		patch.columnoffset[i] = bytes_to_int(data, temp_offset);
		temp_offset += 4;
		i++;
	}
	return (patch);
}

void			wad_get_playpal(t_doom_nukem *doom)
{
	uint32_t	offset;
	uint32_t	size;
	uint32_t	temp_offset;
	t_point		step;

	offset = find_offset_lump(doom->wad.dir, "PLAYPAL", NULL);
	size = find_size_lump(doom->wad.dir, "PLAYPAL", NULL);
	temp_offset = offset;
	step.y = 0;
	while (temp_offset < offset + size)
	{
		step.x = 0;
		while (step.x < 256)
		{
			doom->wad.color[step.y][step.x] = (doom->wad.map[temp_offset] << 16)
									| (doom->wad.map[temp_offset + 1] << 8)
									| doom->wad.map[temp_offset + 2];
			temp_offset += 3;
			step.x++;
		}
		step.y++;
	}
}

void			wad_get_colormap(t_doom_nukem *doom)
{
	uint32_t	offset;
	uint32_t	size;
	uint32_t	temp_offset;
	t_point		step;

	offset = find_offset_lump(doom->wad.dir, "COLORMAP", NULL);
	size = find_size_lump(doom->wad.dir, "COLORMAP", NULL);
	temp_offset = offset;
	step.y = 0;
	while (temp_offset < offset + size)
	{
		step.x = 0;
		while (step.x < 256)
		{
			doom->wad.colormap[step.y][step.x] = doom->wad.map[temp_offset];
			temp_offset += 1;
			step.x++;
		}
		step.y++;
	}
}
