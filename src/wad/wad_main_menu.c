/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wad_main_menu.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 20:25:32 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/12/10 21:15:35 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wad.h"

t_wad_menu		*wad_init_menu(t_wad *wad)
{
	t_wad_menu	*menu;
	int			i;
	
	menu = (t_wad_menu *)ft_memalloc(sizeof(t_wad_menu));
	menu->background = sprite_create(wad, "TITLEPIC");
	i = -1;
	menu->buttons = (t_wad_sprite **)ft_memalloc(sizeof(t_wad_sprite *));
	menu->buttons[++i] = sprite_create(wad, "M_NGAME");
	menu->buttons[++i] = sprite_create(wad, "M_PAUSE");
	menu->buttons[++i] = sprite_create(wad, "M_ENDGAM");
	menu->buttons[++i] = sprite_create(wad, "M_QUITG");
	return (menu);
}

void			wad_draw_menu(SDL_Surface *screen, t_wad *wad, t_wad_menu *menu)
{
	t_rectf		rect;

	rect = (t_rectf){0, 0, 1, 1};
	blit_sprite_scale(menu->background, screen, rect);
	blit_sprite_scale(menu->buttons[3], screen, rect);
	(void)wad;
}