/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_nukem.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/15 06:50:34 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/08/24 19:12:52 by bdrinkin         ###   ########.fr       */
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
# include "define_resource.h"
# include "libft.h"
# include "SDL.h"
# include "SDL_image.h"
# include "SDL_mixer.h"
# include "SDL_ttf.h"
# include "SDL_net.h"
# include <mlx.h>

typedef struct		s_block
{
	SDL_Surface		*block_pic;
	SDL_Rect		rect_block;
	bool			is_push;
	struct s_block	*next;
}					t_block;

typedef struct		s_frames
{
	SDL_Rect		main_frame;
	Uint32			color;
	int				count_blocks;
	struct s_block	*blocks;
	struct s_frames	*next;
}					t_frames;

typedef struct			s_timer
{
	Uint32				start_ticks;
	Uint32				paused_ticks;
	bool				paused;
	bool				started;
	int					counted_frames;
}						t_timer;

typedef struct			s_mouse
{
	bool				is_presed;
	int					prew_x;
	int					prew_y;
	int					x;
	int					y;
}						t_mouse;

typedef struct			s_color
{
	Uint8				red;
	Uint8				green;
	Uint8				blue;
}						t_color;

typedef struct			s_sdl_sys
{
	SDL_Window			*window;
	SDL_Renderer		*render;
	SDL_Surface			*surface;
	SDL_Window			*map_window;
	SDL_Renderer		*map_render;
	SDL_Event			event;
	const Uint8			*state;
	const Uint32		*state_mouse;
	int					width;
	int					height;
	int					map_width;
	int					map_heigth;
	SDL_Surface			*textures[texture_total];
}						t_sdl_sys;

typedef struct			s_doom_nukem
{
	struct s_sdl_sys	sdl;
	struct s_mouse		mouse;
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
/*
** load_res/load_res.c
*/
bool					load_res(t_doom_nukem *doom);
SDL_Surface				*load_surface(char *path, SDL_Surface *screen_surface);
/*
** tools_for_editor/tools.c
*/
void					drag_and_drop(SDL_Surface *src, SDL_Surface *dst);
void					scale_frame(SDL_Surface *dst, t_mouse mouse,
							Uint32 color, void draw(SDL_Surface *,
							SDL_Rect *, Uint32, int));
void					draw_rect(SDL_Surface *dst,
							SDL_Rect *rect, Uint32 color, int step);
void					scale_surface(SDL_Surface *src, SDL_Rect *rscr,
							SDL_Surface *dst, SDL_Rect *drect);
void					draw_feel_rect(SDL_Surface *dst,
							SDL_Rect *rect, Uint32 color, int step);
/*
** accses_pixel.c
*/
Uint32					get_pixel(SDL_Surface *surface, int x, int y);
void					putpixel(SDL_Surface *surface,
							int x, int y, Uint32 pixel);
void					clear_surface(SDL_Surface *surface, Uint32 color);
Uint32					color8_to_32(t_color color);
t_color					color32_to_8(Uint32 color);
/*
** frame.c
*/
void					free_editor(t_doom_nukem *doom, t_frames *frame_table);
t_frames				*new_frame(SDL_Rect *rect, Uint32 color,
							struct s_block *blocks);
void					frame_tamer(t_doom_nukem *doom, t_frames *frame_table);
t_frames				*init_editor(t_doom_nukem *doom);
void					scale_frame_01(SDL_Surface *dst, t_mouse mouse, SDL_Surface *src);
void					blit_surface(SDL_Surface *src, SDL_Rect *rsrc, SDL_Surface *dst, SDL_Rect *rdst);

#endif
