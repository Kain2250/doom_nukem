/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_nukem.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/15 06:50:34 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/08/17 20:01:58 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_NUKEM_H
# define DOOM_NUKEM_H

# define NAME_WIN "Doom-Nukem (by Bdrinkin & Mcarc & Jthuy)"
# define WIDTH_WIN 1500
# define HEIGHT_WIN 1000

# include <math.h>
# include <stdbool.h>
# include "errorout.h"
# include "libft.h"
# include "SDL.h"
# include "SDL_image.h"
# include "SDL_mixer.h"
# include "SDL_ttf.h"
# include "SDL_net.h"

typedef struct			s_timer
{
	Uint32				start_ticks;
	Uint32				paused_ticks;
	bool				paused;
	bool				started;
	int					counted_frames;
}						t_timer;

typedef struct			s_sdl_sys
{
	SDL_Window			*window;
	SDL_Renderer		*render;
	SDL_Surface			*surface;
	SDL_Window			*map_window;
	SDL_Renderer		*map_render;
	// SDL_Texture			*textures;
	SDL_Event			event;
	const Uint8			*state;
	int					width;
	int					height;
	int					map_width;
	int					map_heigth;
	SDL_Surface			*textures;

}						t_sdl_sys;


typedef struct			s_doom_nukem
{
	struct s_sdl_sys	sdl;
	bool				quit;
}						t_doom_nukem;
/*
** main.c
*/
int						main(int ac, char **av);
/*
** debug_file.c
*/
void					doom_exit(t_doom_nukem *doom);
int						put_error_sys(char *error);
bool					put_error_sdl(char *error, const char *error_sdl);
/*
** event_list.c
*/
void					event_list(t_doom_nukem *doom);
/*
** init_sdl.c
*/
bool					init_lib_sdl(t_doom_nukem *doom);
/*
** struct_timer.c
*/
void					timer_init(t_timer *time);
void					timer_start(t_timer *time);
void					timer_stop(t_timer *time);
void					timer_pause(t_timer *time);
void					timer_unpause(t_timer *time);
/*
** timer.c
*/
Uint32					get_ticks(t_timer *time);
bool					time_is_started(t_timer *time);
bool					time_is_paused(t_timer *time);
void					fps_counter(t_timer *time);
/*
** editor_map.c
*/
bool					editor_map(t_doom_nukem *doom);

#endif
