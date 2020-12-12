/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_wad.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 14:29:58 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/12/12 20:51:52 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wad.h"

void	wad_init_level(t_wad *wad, char *name_map)
{
	wad_get_things(wad, name_map);
	wad_get_linedefs(wad, name_map);
	wad_get_sidedefs(wad, name_map);
	wad_get_vertex(wad, name_map);
	wad_get_segs(wad, name_map);
	wad_get_ssectors(wad, name_map);
	wad_get_nodes(wad, name_map);
	wad_get_sectors(wad, name_map);
}

void	def_name(char **name_lisl)
{
	name_lisl[0] = ft_strdup("POSSA1");
	name_lisl[1] = ft_strdup("POSSA2A8");
	name_lisl[2] = ft_strdup("POSSA3A7");
	name_lisl[3] = ft_strdup("POSSA4A6");
	name_lisl[4] = ft_strdup("POSSA5");
	name_lisl[5] = ft_strdup("POSSB1");
	name_lisl[6] = ft_strdup("POSSB2B8");
	name_lisl[7] = ft_strdup("POSSB3B7");
	name_lisl[8] = ft_strdup("POSSB4B6");
	name_lisl[9] = ft_strdup("POSSB5");
	name_lisl[10] = ft_strdup("POSSC1");
	name_lisl[11] = ft_strdup("POSSC2C8");
	name_lisl[12] = ft_strdup("POSSC3C7");
	name_lisl[13] = ft_strdup("POSSC4C6");
	name_lisl[14] = ft_strdup("POSSC5");
	name_lisl[15] = ft_strdup("POSSD1");
	name_lisl[16] = ft_strdup("POSSD2D8");
	name_lisl[17] = ft_strdup("POSSD3D7");
	name_lisl[18] = ft_strdup("POSSD4D6");
	name_lisl[19] = ft_strdup("POSSD5");
	name_lisl[20] = ft_strdup("POSSE1");
	name_lisl[21] = ft_strdup("POSSE2E8");
	name_lisl[22] = ft_strdup("POSSE3E7");
	name_lisl[23] = ft_strdup("POSSE4E6");
	name_lisl[24] = ft_strdup("POSSE5");
	name_lisl[25] = ft_strdup("POSSF1");
	name_lisl[26] = ft_strdup("POSSF2F8");
	name_lisl[27] = ft_strdup("POSSF3F7");
	name_lisl[28] = ft_strdup("POSSF4F6");
	name_lisl[29] = ft_strdup("POSSF5");
	name_lisl[30] = ft_strdup("POSSG1");
	name_lisl[31] = ft_strdup("POSSG2G8");
	name_lisl[32] = ft_strdup("POSSG3G7");
	name_lisl[33] = ft_strdup("POSSG4G6");
	name_lisl[34] = ft_strdup("POSSG5");
	name_lisl[35] = ft_strdup("POSSH0");
	name_lisl[36] = ft_strdup("POSSI0");
	name_lisl[37] = ft_strdup("POSSJ0");
	name_lisl[38] = ft_strdup("POSSK0");
	name_lisl[39] = ft_strdup("POSSL0");
}

void	init_name_list(t_wad *wad)
{
	int	i;

	i = -1;
	wad->name = (char **)ft_xmemalloc(sizeof(char *) * peh_total);
	def_name(wad->name);
	while (++i < peh_total)
	{
		if (wad->name[i] == NULL)
			exit(put_error_sys(ERR_MALLOC));
	}
}

t_wad_sprite	**fill_sprites(int def_sprt, char **name, t_wad *wad)
{
	int				i;
	t_wad_sprite	**sprites;

	i = -1;
	sprites = ft_xmemalloc(sizeof(t_wad_sprite *) * (def_sprt + 1));
	while (++i <= def_sprt)
		sprites[i] = (t_wad_sprite *)ft_xmemalloc(sizeof(t_wad_sprite));
	i = -1;
	while (++i < def_sprt)
		sprites[i] = sprite_create(wad, name[i]);
	sprites[i] = NULL;
	return (sprites);
}

t_wad	*init_wad(char *av)
{
	t_wad	*wad;

	wad = (t_wad *)ft_xmemalloc(sizeof(t_wad));
	wad_loader(wad, av);
	wad_reader(wad);
	wad_init_level(wad, "E1M1");
	wad_init_menu(wad);
	init_name_list(wad);
	wad->hud = init_hud(wad);
	wad->sprites = fill_sprites(peh_total, wad->name, wad);
	return (wad);
}
