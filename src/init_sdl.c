/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sdl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/15 08:30:01 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/08/15 09:58:14 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"
bool			init_sdl(t_doom_nukem *doom)
{
	if (SDL_Init(SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_VIDEO |
		SDL_INIT_EVENTS) == -1)
		return (false);
	if ((doom->sdl.window = SDL_CreateWindow(NAME_WIN, 0,
		0, WIDTH_WIN,
		HEIGHT_WIN, SDL_WINDOW_RESIZABLE)) == NULL)
		return (false);
	if ((doom->sdl.render = SDL_CreateRenderer(doom->sdl.window,
		-1, SDL_RENDERER_SOFTWARE)) == NULL)
		return (false);
	SDL_EventState(SDL_MOUSEMOTION, SDL_DISABLE);
	SDL_EventState(SDL_KEYDOWN, SDL_DISABLE);
	SDL_EventState(SDL_KEYUP, SDL_DISABLE);
	return (true);
}

bool			init_sdl_image(t_doom_nukem *doom)
{
	if (!(IMG_Init(IMG_INIT_JPG) & IMG_INIT_JPG))
		return (false);
	(void)doom;
	return (true);
}

bool			init_sdl_mixer(t_doom_nukem *doom)
{
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		return (false);
	(void)doom;
	return (true);
}

bool			init_sdl_ttf(t_doom_nukem *doom)
{
	if (TTF_Init() == -1)
		return (false);
	(void)doom;
	return (true);
}

bool			init_sdl_net(t_doom_nukem *doom)
{
	if (SDLNet_Init() == -1)
		return (false);
	(void)doom;
	return (true);
}

bool			init_lib_sdl(t_doom_nukem *doom)
{
	if (init_sdl(doom) == false)
		return (put_error_sdl(ERR_INIT_SDL, SDL_GetError()));
	if (init_sdl_image(doom) == false)
		return (put_error_sdl(ERR_INIT_IMG, SDL_GetError()));
	if (init_sdl_mixer(doom) == false)
		return (put_error_sdl(ERR_INIT_MIX, SDL_GetError()));
	if (init_sdl_ttf(doom) == false)
		return (put_error_sdl(ERR_INIT_TTF, SDL_GetError()));
	if (init_sdl_net(doom) == false)
		return (put_error_sdl(ERR_INIT_NET, SDL_GetError()));
	return (true);
}