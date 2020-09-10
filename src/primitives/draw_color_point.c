/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_color_point.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 14:46:47 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/09/10 14:47:01 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void			drow_color_point(SDL_Surface *dst, Uint32 color)
{
	SDL_Point	mouse;

	SDL_GetMouseState(&mouse.x, &mouse.y);
	putpixel(dst, mouse.x, mouse.y, color);
}
