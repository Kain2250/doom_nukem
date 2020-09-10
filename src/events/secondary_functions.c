/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   secondary_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 14:45:24 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/09/10 14:57:43 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

bool		is_slidebar_area(t_rect *area, t_mouse mouse)
{
	SDL_GetMouseState(&mouse.x, &mouse.y);
	if ((mouse.x > area->x && mouse.x < area->w + area->x) &&
		(mouse.y > area->y - 5 && mouse.y < area->h + area->y + 5))
		return (true);
	return (false);
}

bool		is_button_area(t_rect *area, t_mouse mouse)
{
	SDL_GetMouseState(&mouse.x, &mouse.y);
	if ((mouse.x > area->x && mouse.x < area->w + area->x) &&
		(mouse.y > area->y && mouse.y < area->h + area->y))
		return (true);
	return (false);
}

void		is_mouse_presed(t_mouse *mouse)
{
	if (mouse->is_presed == false)
		SDL_GetMouseState(&mouse->prew_x, &mouse->prew_y);
	else
		SDL_GetMouseState(&mouse->x, &mouse->y);
}
