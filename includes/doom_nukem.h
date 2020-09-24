/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_nukem.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/15 06:50:34 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/09/24 21:09:08 by bdrinkin         ###   ########.fr       */
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
# include "tree_struct.h"
# include "libft.h"
# include "SDL.h"
# include "SDL_image.h"
# include "SDL_mixer.h"
# include "SDL_ttf.h"
# include "SDL_net.h"

typedef struct		s_point
{
	int				x;
	int				y;
}					t_point;

typedef struct		s_pointf
{
	double			x;
	double			y;
}					t_pointf;

typedef struct		s_rect
{
	int				x;
	int				y;
	int				w;
	int				h;
	bool			free;
}					t_rect;

typedef struct		s_rectf
{
	double			x;
	double			y;
	double			w;
	double			h;
	bool			free;
}					t_rectf;

typedef struct			s_limit
{
	int					cur;
	int					max;
	int					min;
}						t_limit;

typedef struct			s_limit_f
{
	float				cur;
	float				max;
	float				min;
}						t_limit_f;

typedef struct		s_block
{
	int				type_block;
	SDL_Surface		*block_pic;
	t_rect			*rect_block;
	bool			is_push;
	struct s_block	*next;
}					t_block;

typedef struct		s_frames
{
	t_rect			*main_frame;
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

typedef struct			s_player
{
	t_limit				heals;
}						t_player;

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
	TTF_Font			*fonts[font_total];
}						t_sdl_sys;

typedef struct			s_new_win
{
	SDL_Window			*win;
	SDL_Surface			*screen;
	SDL_Event			event;
	struct s_frames		*frames;
	bool				quit;
}						t_new_win;

typedef struct	s_wad
{
	char		wad_type[5];
	uint32_t	dir_count;
	uint32_t	dir_offset;
}				t_wad;

typedef struct	s_dir
{
	char		lump_name[9];
	uint32_t	lump_offset;
	uint32_t	lump_size;
}				t_dir;

typedef struct			s_doom_nukem
{
	struct s_sdl_sys	sdl;
	struct s_mouse		mouse;
	struct s_new_win	frame;
	struct s_frames		*screen;
	struct s_player		player;
	uint8_t				*map;
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
							t_rect *, Uint32, int));
void					draw_rect(SDL_Surface *dst,
							t_rect *rect, Uint32 color, int step);
void					draw_feel_rect(SDL_Surface *dst,
							t_rect *rect, Uint32 color, int step);
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
void					free_editor(t_frames *frame_table);
t_frames				*new_frame(t_rect rect, Uint32 color,
							struct s_block *blocks);
t_block					*new_block(int type, t_rect rect, SDL_Surface *pic);
void					frame_tamer(t_doom_nukem *doom, t_frames *frame_table);
t_frames				*init_editor(t_doom_nukem *doom);
void					scale_rect_texture(SDL_Surface *dst, t_mouse mouse, SDL_Surface *src);

void					if_rect(SDL_Surface *src, t_rect *rsrc,
							SDL_Surface *dst, t_rect *rdst);

void					blit_surf_scaled(SDL_Surface *src, t_rect *rsrc,
							SDL_Surface *dst, t_rect *rdst);
void					blit_surface(SDL_Surface *src, t_rect *rsrc,
							SDL_Surface *dst, t_rect *rdst);

t_rect					*rect_fill(int x, int y, int w, int h);
t_rect					rect_fill_no_malloc(int x, int y, int w, int h);
void					draw_line(SDL_Surface *dst, t_point start, t_point end, Uint32 color);
void					draw_circl(SDL_Surface *dst, int radius,
							t_point center, Uint32 color);
void					draw_fill_circl(SDL_Surface *dst, int radius,
							t_point center, Uint32 color);
void					draw_smooth_rect(SDL_Surface *dst, t_rect *rect,
							Uint32 color, int thickness);
void					draw_smooth_fill_rect(SDL_Surface *dst, t_rect *rect,
							Uint32 color);
void					put_button(SDL_Surface *dst, t_rect *rect,
							Uint32 color_fill, Uint32 color_frame);

void					put_slide_bar(SDL_Surface *dst, t_rect *rect, t_limit *data, Uint32 color);
float					interpolate(t_limit_f x, t_limit_f c);
void					fill_limit(t_limit *data, int min, int cur, int max);
void					fill_limit_f(t_limit_f *data, float min, float cur, float max);

void					mouse_events(t_doom_nukem *doom);
bool					is_button_area(t_rect *area, t_mouse mouse);
void					is_mouse_presed(t_mouse *mouse);
bool					is_slidebar_area(t_rect *area, t_mouse mouse);
int						which_button(bool *mouse);


t_point					fill_point(int x, int y);

bool					wad_loader(t_doom_nukem *doom, char *path);
bool					wad_reader(t_doom_nukem *doom);
uint16_t				bytes_to_short(const uint8_t *data, int offset);
uint32_t				bytes_to_int(const uint8_t *data, int offset);

#endif
