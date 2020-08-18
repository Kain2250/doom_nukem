/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 20:40:05 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/08/18 16:06:08 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

bool		frame_master(t_doom_nukem *doom, SDL_Rect *dst)
{
	
	SDL_BlitScaled(doom->sdl.textures[texture_iron], NULL, doom->sdl.surface, dst);
	SDL_UpdateWindowSurface(doom->sdl.window);
	return (true);
}
