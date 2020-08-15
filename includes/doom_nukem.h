/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_nukem.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/15 06:50:34 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/08/15 07:31:26 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_NUKEM_H
# define DOOM_NUKEM_H

# define NAME_WIN "Doom-Nukem (by Bdrinkin & Mcarc & Jthuy)"
# define WIDTH_WIN 1500
# define HEIGHT_WIN 1000

# include <math.h>
# include <stdbool.h>
# include "libft.h"
# include "SDL.h"
# include "SDL_image.h"
# include "SDL_mixer.h"
# include "SDL_ttf.h"
# include "SDL_net.h"

typedef struct			s_sdl_sys
{
	SDL_Window			*window;
	SDL_Renderer		*render;
	SDL_Window			*map_window;
	SDL_Renderer		*map_render;
	SDL_Texture			*textures;
	SDL_Event			event;
	int					width;
	int					height;
	int					map_width;
	int					map_heigth;

}						t_sdl_sys;


typedef struct			s_doom_nukem
{
	struct s_sdl_sys	sdl;
}						t_doom_nukem;

int						main(int ac, char **av);

#endif
