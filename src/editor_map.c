/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 19:38:55 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/08/17 20:08:44 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

bool			editor_map(t_doom_nukem *doom)
{
	SDL_Rect	q;

	q.h = 100;
	q.w = 200;
	q.x = 0;
	q.y = 0;
	SDL_BlitScaled(doom->sdl.textures, &q, doom->sdl.surface, &q);
	SDL_UpdateWindowSurface(doom->sdl.window);
	(void)doom;
	return (true);
}