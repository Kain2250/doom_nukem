/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_res.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 15:00:44 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/08/18 15:56:44 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

bool				load_texture(SDL_Surface *textures[texture_total])
{
	int				i;

	textures[texture_test] = SDL_LoadBMP(IMG_TEST);
	textures[texture_iron] = SDL_LoadBMP(IMG_IRON);
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
	if (load_texture(doom->sdl.textures) == false)
		return (put_error_sdl(ERR_LOAD_IMG, IMG_GetError()));
	return (true);
}
