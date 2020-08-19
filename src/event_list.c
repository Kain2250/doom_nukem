/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/15 09:15:51 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/08/19 21:10:31 by bdrinkin         ###   ########.fr       */
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
	SDL_Rect	q;

	q.x = 100;
	q.y = 100;
	q.h = 100;
	q.w = 500;
	if (doom->mouse.is_presed == false)
		SDL_GetMouseState(&doom->mouse.prew_x, &doom->mouse.prew_y);
	if (SDL_BUTTON_RIGHT == which_button(&doom->mouse.is_presed))
	{
		scale_frame(doom->sdl.surface, doom->mouse, 0xfffff);
		// draw_rect(doom->sdl.surface, &q, 0xFFFF00);
		// drag_and_drop(doom->sdl.textures[texture_test], doom->sdl.surface);
	}
	// if (SDL_BUTTON(SDL_BUTTON_LEFT) & SDL_GetMouseState(NULL, NULL))
	// 	drow_color_point(doom->sdl.surface, 0xff98f8);
	// if (SDL_BUTTON(SDL_BUTTON_RIGHT) & SDL_GetMouseState(NULL, NULL))
	// 	scale_frame(doom->sdl.surface, NULL, doom->sdl.textures[texture_test2], NULL);

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
	