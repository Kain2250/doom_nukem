/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wad_get.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 19:49:40 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/10/04 20:46:50 by bdrinkin         ###   ########.fr       */
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
	patch.columnoffset = (uint32_t *)ft_memalloc(sizeof(uint32_t) *
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

void			wad_get_textures(const uint8_t *data, uint32_t offset, t_texture_head *texture)
{
	uint32_t	i;
	uint32_t	j;
	uint32_t	temp_offset;

	temp_offset = offset;
	texture->num_texture = bytes_to_int(data, temp_offset);
	temp_offset += 4;
	texture->offsets = (uint32_t *)ft_memalloc(texture->num_texture * (sizeof(uint32_t)));
	i = 0;
	while (i < texture->num_texture)
	{
		texture->offsets[i] = bytes_to_int(data, temp_offset);
		temp_offset += 4;
		i++;
	}
	texture->mtexture = (t_map_texture *)ft_memalloc(sizeof(t_map_texture) * i);
	i = 0;
	while (i < texture->num_texture)
	{
		temp_offset = offset + texture->offsets[i];
		j = 0;
		while(j < 8)
			texture->mtexture[i].name[j++] = data[temp_offset++];
		texture->mtexture[i].name[j] = '\0';
		texture->mtexture[i].masked = bytes_to_short(data, temp_offset + 2);
		texture->mtexture[i].width = bytes_to_short(data, temp_offset + 4);
		texture->mtexture[i].height = bytes_to_short(data, temp_offset + 6);
		texture->mtexture[i].patchcount = bytes_to_short(data, temp_offset + 12);
		if (texture->mtexture[i].patchcount > 0)
			texture->mtexture[i].patches = (t_patches *)ft_memalloc(sizeof(t_patches) * texture->mtexture[i].patchcount);
		j = 0;
		temp_offset = temp_offset + 12;
		while (j < texture->mtexture[i].patchcount)
		{
			texture->mtexture[i].patches[j].origin_x = bytes_to_short(data, temp_offset + 2);
			texture->mtexture[i].patches[j].origin_y = bytes_to_short(data, temp_offset + 4);
			texture->mtexture[i].patches[j].patch = bytes_to_short(data, temp_offset + 6);
			texture->mtexture[i].patches[j].stepdir = bytes_to_short(data, temp_offset + 8);
			texture->mtexture[i].patches[j].colormap = bytes_to_short(data, temp_offset + 10);
			temp_offset = temp_offset + 10;
			j++;
		}
		i++;
	}
}

void			wad_get_pnames(const uint8_t *data, t_dir *dir ,t_pnames *pname)
{
	uint32_t	i;
	uint32_t	j;
	uint32_t	offset;
	uint32_t	temp_offset;
	
	offset = find_offset_lump(dir, "PNAMES", NULL);
	temp_offset = offset;
	i = 0;
	pname->num_map_patches = bytes_to_int(data, temp_offset);
	pname->name = (char **)ft_memalloc(sizeof(char *) * pname->num_map_patches);
	while (i < pname->num_map_patches)
		pname->name[i++] = (char *)ft_memalloc(sizeof(char) * 9);
	i = 0; 
	temp_offset += 4;
	while (i < pname->num_map_patches)
	{
		j = 0;
		while (j < 8)
			pname->name[i][j++] = data[temp_offset++];
		i++;
	}
}
