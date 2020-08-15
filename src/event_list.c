/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/15 09:15:51 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/08/15 09:59:09 by bdrinkin         ###   ########.fr       */
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

void			event_list(t_doom_nukem *doom)
{
	SDL_PollEvent(&doom->sdl.event);
	if (event_exit(doom) == true)
		doom->quit = true;
	}