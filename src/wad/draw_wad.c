/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wad.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 19:43:10 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/10/03 20:53:46 by bdrinkin         ###   ########.fr       */
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

void			wad_draw_patch(t_doom_nukem *doom, char *texture)
{
	uint32_t	offset;
	uint32_t	temp_offset;
	t_point		iter;
	t_patch		patch;

	uint32_t	c;


	offset = find_offset_lump(doom->wad.dir, texture, NULL);
	patch = wad_get_patch_info(doom->wad.map, offset);
	iter.y = 0;
	while (iter.y < patch.width)
	{
		iter.x = 0;
		temp_offset = offset + patch.columnoffset[iter.y] + 2;
		while (iter.x < patch.height)
		{
			c = doom->wad.map[temp_offset];
			putpixel(doom->sdl.surface, iter.y, iter.x, doom->wad.color[0][c]);
			iter.x++;
			temp_offset += 1;
		}
		iter.y++;
	}
}

void			wad_draw_linedefs(t_doom_nukem *doom, t_vertex *vertex)
{
	uint16_t	i;
	uint32_t	color;

	i = 0;
	while (vertex[i] != NULL)
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

