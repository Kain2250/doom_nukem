/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_nukem.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/15 06:50:34 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/11/30 18:02:17 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_NUKEM_H
# define DOOM_NUKEM_H

# define NAME_WIN "Doom-Nukem (by Bdrinkin & Jthuy & Vneelix && Nsena)"
// # define WIDTH_WIN 320
// # define HEIGHT_WIN 200
# define WIDTH_WIN 1500
# define HEIGHT_WIN 1000
# define HALF_WIDTH WIDTH_WIN / 2
# define HALF_HEIGHT HEIGHT_WIN / 2

# include <math.h>
# include <stdbool.h>
# include "errorout.h"
# include "define_resource.h"
# include "tree_struct.h"
# include "sprite_kit.h"
# include "rect.h"
# include "wad.h"
# include "libft.h"
# ifdef __APPLE__
#  include "SDL.h"
#  include "SDL_image.h"
#  include "SDL_mixer.h"
#  include "SDL_ttf.h"
#  include "SDL_net.h"
# elif __linux__
#  include "SDL2/SDL.h"
#  include "SDL2/SDL_image.h"
#  include "SDL2/SDL_mixer.h"
#  include "SDL2/SDL_ttf.h"
#  include "SDL2/SDL_net.h"
# endif

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
	Uint8				alpha;
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



typedef struct			s_crd
{
	int					x;
	int					*y;
}						t_crd;

typedef struct			s_doom
{
	struct s_sdl_sys	sdl;
	struct s_mouse		mouse;
	struct s_new_win	frame;
	struct s_frames		*screen;
	struct s_player		player;
	t_timer				time;
	t_wad				wad;
	t_sprite			test[15];
	int					buf1;
	int					buf2;
	bool				quit;
}						t_doom;
/*
** main.c
*/
int						main(int ac, char **av);
/*
** debug_file.c
*/
void					doom_exit(t_doom *doom);
/*
** event_list.c
*/
void					event_list(t_doom *doom);
/*
** init_sdl.c
*/
bool					init_lib_sdl(t_doom *doom);
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
bool					load_res(t_doom *doom);
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
void					frame_tamer(t_doom *doom, t_frames *frame_table);
t_frames				*init_editor(t_doom *doom);
void					scale_rect_texture(SDL_Surface *dst, t_mouse mouse, SDL_Surface *src);

void					if_rect(SDL_Surface *src, t_rect *rsrc,
							SDL_Surface *dst, t_rect *rdst);

void					blit_surf_scaled(SDL_Surface *src, t_rect *rsrc,
							SDL_Surface *dst, t_rect *rdst);
void					blit_surface(SDL_Surface *src, t_rect *rsrc,
							SDL_Surface *dst, t_rect *rdst);

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

void					mouse_events(t_doom *doom);
bool					is_button_area(t_rect *area, t_mouse mouse);
void					is_mouse_presed(t_mouse *mouse);
bool					is_slidebar_area(t_rect *area, t_mouse mouse);
int						which_button(bool *mouse);


void					wad_put_patch(t_doom *doom, char *texture, t_patches pth, t_point start);
void					wad_draw_vertex(t_doom *doom, char *name_map);
void					wad_draw_linedefs(t_wad wad,
						t_vertex *vertex, SDL_Surface *surface, char *name_map);
SDL_Surface				*wad_draw_texture(t_doom *doom, t_point start, char *texture);
SDL_Surface				*wad_draw_patch(t_wad wad, char *pnames, t_sprite *sprite);
void					put_pixel_sprite(t_sprite *sprite, int x, int y, uint32_t color);
void					draw_sprite_anim(t_doom *doom, t_sprite **sprite, Uint32 delay);



void					clear_wad_dir(t_dir *dir);
void					print_bit(void *data);


#endif
