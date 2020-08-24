/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_res.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 15:00:44 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/08/23 18:20:13 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

SDL_Surface			*load_surface(char *path, SDL_Surface *screen_surface)
{
	SDL_Surface		*optimizedSurface;
	SDL_Surface		*loadedSurface;

	loadedSurface = SDL_LoadBMP(path);
	if (loadedSurface == NULL)
		return (NULL);
	else
	{
		optimizedSurface = SDL_ConvertSurface(loadedSurface,
			screen_surface->format, 0);
		if (optimizedSurface == NULL)
			return (NULL);
		SDL_FreeSurface(loadedSurface);
	}
	return (optimizedSurface);
}

static bool			load_texture(SDL_Surface *textures[texture_total],
					SDL_Surface *surface)
{
	int				i;

	textures[texture_test] = load_surface(IMG_TEST, surface);
	textures[texture_iron] = load_surface(IMG_IRON, surface);
	textures[texture_test2] = load_surface("resource/textures/sw2cmt.bmp", surface);
	textures[texture_editor_back] = load_surface("resource/textures/editor_back.bmp", surface);
	i = 0;
	while (i != texture_total)
	{
		if (textures[i] == NULL)
			return (false);
		else
			i++;
	}
	return (true);
}

bool				load_res(t_doom_nukem *doom)
{
	if (load_texture(doom->sdl.textures, doom->sdl.surface) == false)
		return (put_error_sdl(ERR_LOAD_IMG, IMG_GetError()));
	return (true);
}
