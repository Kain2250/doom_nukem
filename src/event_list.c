/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/15 09:15:51 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/08/27 22:03:54 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

bool			event_exit(t_doom_nukem *doom)
{
	if (doom->sdl.event.type == SDL_QUIT ||
		doom->sdl.state[SDL_SCANCODE_ESCAPE])
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

void			drow_color_point(SDL_Surface *dst, Uint32 color)
{
	SDL_Point	mouse;

	SDL_GetMouseState(&mouse.x, &mouse.y);
	putpixel(dst, mouse.x, mouse.y, color);
}


int				which_button(bool *mouse)
{
	*mouse = true;
	if (SDL_BUTTON(SDL_BUTTON_RIGHT) & SDL_GetMouseState(NULL, NULL))
		return (SDL_BUTTON_RIGHT);
	else if (SDL_BUTTON(SDL_BUTTON_LEFT) & SDL_GetMouseState(NULL, NULL))
		return (SDL_BUTTON_LEFT);
	else if (SDL_BUTTON(SDL_BUTTON_MIDDLE) & SDL_GetMouseState(NULL, NULL))
		return (SDL_BUTTON_MIDDLE);
	else if (SDL_BUTTON(SDL_BUTTON_X1) & SDL_GetMouseState(NULL, NULL))
		return (SDL_BUTTON_X1);
	else if (SDL_BUTTON(SDL_BUTTON_X2) & SDL_GetMouseState(NULL, NULL))
		return (SDL_BUTTON_X2);
	*mouse = false;
	return (0);
}



void			mouse_events(t_doom_nukem *doom)
{
	int			button;

	if (doom->mouse.is_presed == false)
		SDL_GetMouseState(&doom->mouse.prew_x, &doom->mouse.prew_y);
	button = which_button(&doom->mouse.is_presed);
	if (SDL_BUTTON_RIGHT == button)
		scale_frame(doom->sdl.surface, doom->mouse, 0x00ff00, draw_rect);
	else if (SDL_BUTTON_LEFT == button)
		// drow_color_point(doom->sdl.surface, 0xffffff);
		scale_frame_01(doom->sdl.surface, doom->mouse, doom->sdl.textures[texture_test2]);
	else if (SDL_BUTTON_MIDDLE == button)
		drag_and_drop(doom->sdl.textures[texture_test], doom->sdl.surface);


}

void			event_list(t_doom_nukem *doom)
{
	SDL_PumpEvents();
	doom->sdl.state = SDL_GetKeyboardState(NULL);
	SDL_GetWindowSize(doom->sdl.window, &doom->sdl.width, &doom->sdl.height);
	if (event_exit(doom) == true)
		doom->quit = true;
	mouse_events(doom);
}
	