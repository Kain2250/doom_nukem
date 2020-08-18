/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 19:38:55 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/08/18 16:06:29 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

bool			editor_map(t_doom_nukem *doom)
{
	SDL_Rect	q;

	q.h = 100;
	q.w = 400;
	q.x = 0;
	q.y = 0;
	SDL_BlitScaled(doom->sdl.textures[texture_test], &q, doom->sdl.surface, NULL);
	SDL_UpdateWindowSurface(doom->sdl.window);
	(void)doom;
	return (true);
}
