/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_res.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 15:00:44 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/11/17 21:01:24 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

SDL_Surface		*load_surface(char *path, SDL_Surface *screen_surface)
{
	SDL_Surface	*optimized_surface;
	SDL_Surface	*loaded_surface;

	loaded_surface = SDL_LoadBMP(path);
	if (loaded_surface == NULL)
		return (NULL);
	else
	{
		optimized_surface = SDL_ConvertSurface(loaded_surface,
			screen_surface->format, 0);
		if (optimized_surface == NULL)
			return (NULL);
		SDL_FreeSurface(loaded_surface);
	}
	return (optimized_surface);
}

static bool		load_font(TTF_Font *font[font_total])
{
	int			i;

	i = 0;
	font[font_button] = TTF_OpenFont(FONT_BUTTON, 16);
	font[font_text] = TTF_OpenFont(FONT_TEXT, 14);
	while (i != font_total)
	{
		if (font[i] == NULL)
			return (false);
		else
			i++;
	}
	return (true);
}

static bool		load_texture(SDL_Surface *textures[texture_total],
				SDL_Surface *surface)
{
	int			i;

	textures[texture_test] = load_surface(IMG_TEST, surface);
	textures[texture_cursor0] = load_surface(IMG_CURS0, surface);
	textures[texture_iron] = load_surface(IMG_IRON, surface);
	textures[texture_test2] = load_surface(IMG_TEST2, surface);
	textures[texture_editor_back] = load_surface(IMG_EDITHOR_BACK, surface);
	textures[texture_icon] = load_surface(IMG_ICON, surface);
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

bool			load_res(t_doom *doom)
{
	if (load_texture(doom->sdl.textures, doom->sdl.surface) == false)
		return (put_error_sdl(ERR_LOAD_IMG, IMG_GetError()));
	if (load_font(doom->sdl.fonts) == false)
		return (put_error_sdl(ERR_LOAD_FONT, TTF_GetError()));
	return (true);
}
