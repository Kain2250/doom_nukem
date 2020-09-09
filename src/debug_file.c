/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/15 08:33:00 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/09/09 13:11:52 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	doom_exit(t_doom_nukem *doom)
{
	int	i;

	i = 0;
	while (i < texture_total)
	{
		if (doom->sdl.textures[i] != NULL)
			SDL_FreeSurface(doom->sdl.textures[i]);
		i++;
	}
	if (doom->sdl.surface != NULL)
		SDL_FreeSurface(doom->sdl.surface);
	if (doom->sdl.window != NULL)
		SDL_DestroyWindow(doom->sdl.window);
	while (i < font_total)
	{
		if (doom->sdl.fonts[i] != NULL)
			TTF_CloseFont(doom->sdl.fonts[i]);
		i++;
	}
	IMG_Quit();
	TTF_Quit();
	SDLNet_Quit();
	Mix_Quit();
	SDL_Quit();
	if (doom != NULL)
		free(doom);
}

int		put_error_sys(char *error)
{
	ft_putendl_fd(error, ERR_FD);
	return (1);
}

bool	put_error_sdl(char *error, const char *error_sdl)
{
	ft_putstr_fd(error, ERR_FD);
	ft_putchar_fd(' ', ERR_FD);
	ft_putendl_fd(error_sdl, ERR_FD);
	return (false);
}
