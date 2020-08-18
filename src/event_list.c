/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/15 09:15:51 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/08/18 18:49:47 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

bool			event_exit(t_doom_nukem *doom)
{
	doom->sdl.state = SDL_GetKeyboardState(NULL);
	if (doom->sdl.event.type == SDL_QUIT || doom->sdl.state[SDL_SCANCODE_ESCAPE])
		return (true);
	else
		return (false);
}

void			assig_rect(SDL_Rect *rect, SDL_Point xy, int w, int h)
{
	rect->x = xy.x;
	rect->y = xy.y;
	rect->h = h;
	rect->w = w;
}

void			event_list(t_doom_nukem *doom)
{
	SDL_Point	mouse;
	SDL_Rect	rect;

	SDL_PollEvent(&doom->sdl.event);
	if (event_exit(doom) == true)
		doom->quit = true;
	if (SDL_GetMouseState(&mouse.x, &mouse.y) & SDL_BUTTON(SDL_BUTTON_LEFT))
	{
		clear_surface(doom->sdl.surface, 0x0);
		assig_rect(&rect, mouse, 100, 100);
		SDL_BlitScaled(doom->sdl.textures[texture_test], NULL, doom->sdl.surface, &rect);
		SDL_UpdateWindowSurface(doom->sdl.window);
	}
}
	