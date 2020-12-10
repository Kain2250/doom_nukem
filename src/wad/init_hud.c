/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_hud.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 15:54:08 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/12/10 20:32:07 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wad.h"

void			destroy_hud(t_wad_hud *hud)
{
	int			i;

	if (hud)
	{
		if (hud->big_digit)
		{
			i = -1;
			while (hud->big_digit[++i])
				free(hud->big_digit[i]);
		}
		if (hud->digit)
		{
			i = -1;
			while (hud->digit[++i])
				free(hud->digit[i]);
		}
		if (hud->stbar->name)
			free(hud->stbar->name);
		if (hud->stbar->pixel)
			free(hud->stbar->pixel);
		free(hud);
		hud = NULL;
	}
}

void			destroi_name(char **name)
{
	int			i;

	if (name)
	{
		i = 0;
		while (i < 10)
		{
			free(name[i]);
			name[i++] = NULL;
		}
		free(name);
		name = NULL;
	}
}

char			**name_digit(int count)
{
	int			i;
	char		**name;

	name = ft_memalloc(sizeof(char *) * count);
	i = -1;
	while (++i < count)
		name[i] = (char *)ft_memalloc(sizeof(char) * 9);
	name[0] = ft_strcpy(name[0], "STTNUM0");
	name[1] = ft_strcpy(name[1], "STTNUM1");
	name[2] = ft_strcpy(name[2], "STTNUM2");
	name[3] = ft_strcpy(name[3], "STTNUM3");
	name[4] = ft_strcpy(name[4], "STTNUM4");
	name[5] = ft_strcpy(name[5], "STTNUM5");
	name[6] = ft_strcpy(name[6], "STTNUM6");
	name[7] = ft_strcpy(name[7], "STTNUM7");
	name[8] = ft_strcpy(name[8], "STTNUM8");
	name[9] = ft_strcpy(name[9], "STTNUM9");
	name[10] = ft_strcpy(name[10], "STTPRCNT");
	return (name);
}

char			**name_big_digit(int count)
{
	int			i;
	char		**name;
	
	name = ft_memalloc(sizeof(char *) * count);
	i = -1;
	while (++i != count)
		name[i] = (char *)ft_memalloc(sizeof(char) * 9);
	name[0] = ft_strcpy(name[0], "STYSNUM0");
	name[1] = ft_strcpy(name[1], "STYSNUM1");
	name[2] = ft_strcpy(name[2], "STYSNUM2");
	name[3] = ft_strcpy(name[3], "STYSNUM3");
	name[4] = ft_strcpy(name[4], "STYSNUM4");
	name[5] = ft_strcpy(name[5], "STYSNUM5");
	name[6] = ft_strcpy(name[6], "STYSNUM6");
	name[7] = ft_strcpy(name[7], "STYSNUM7");
	name[8] = ft_strcpy(name[8], "STYSNUM8");
	name[9] = ft_strcpy(name[9], "STYSNUM9");
	return (name);
}

void			digit_get(t_wad *wad, char *name, t_wad_sprite *digit)
{
	uint32_t	offset;
	t_patch		patch;
	int			x;

	offset = find_offset_lump(wad->dir, name, NULL);
	patch = wad_get_patch_info(wad->map, offset);
	digit->name = (char *)name;
	digit->h = patch.height;
	digit->w = patch.width;
	digit->left_offset = patch.left_offset;
	digit->top_offset = patch.top_offset;
	digit->pixel = (uint32_t *)malloc(sizeof(uint32_t) *
		(digit->w * digit->h));
	digit->pixel = ft_memset(digit->pixel, 0xFFFFFFFF,
		sizeof(uint32_t) * digit->w * digit->h);
	x = -1;
	while (++x < patch.width)
		put_column(wad, offset + patch.columnoffset[x], x, digit);
	wad_destroy_patch(patch);
}

t_wad_hud		*init_hud(t_wad *wad)
{
	t_wad_hud	*hud;
	char		**name_b;
	char		**name;
	int			i;
	
	hud = (t_wad_hud *)ft_memalloc(sizeof(t_wad_hud));
	hud->stbar = sprite_create(wad, "STBAR");
	hud->big_digit = (t_wad_sprite **)ft_memalloc(sizeof(t_wad_sprite) * 10);
	i = -1;
	while (++i < 10)
		hud->big_digit[i] = (t_wad_sprite *)ft_memalloc(sizeof(t_wad_sprite));
	name_b = name_big_digit(10);
	i = -1;
	while (++i < 10)
		digit_get(wad, name_b[i], hud->big_digit[i]);
	i = -1;
	hud->digit = (t_wad_sprite **)ft_memalloc(sizeof(t_wad_sprite) * 11);
	while (++i < 11)
		hud->digit[i] = (t_wad_sprite *)ft_memalloc(sizeof(t_wad_sprite));
	name = name_digit(11);
	i = -1;
	while (++i < 11)
		digit_get(wad, name[i], hud->digit[i]);
	return (hud);
}
