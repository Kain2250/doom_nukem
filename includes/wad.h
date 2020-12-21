/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wad.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 12:14:39 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/12/21 17:41:27 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WAD_H
# define WAD_H

# include <stdint.h>
# include <stdbool.h>
# include "tree_struct.h"
# include "rect.h"
# include "sprite_kit.h"
# include "libft.h"
# include "errorout.h"
# include "define_resource.h"

# ifdef __APPLE__
#  include "SDL.h"
# elif __linux__
#  include "SDL2/SDL.h"
# endif

typedef struct s_wad_head	t_wad_head;
typedef struct s_wad_dir	t_wad_dir;
typedef struct s_wad_menu	t_wad_menu;
typedef struct s_wad		t_wad;

struct			s_wad_head {
	char		wad_type[5];
	uint32_t	dir_count;
	uint32_t	dir_offset;
};

struct			s_wad_dir {
	uint32_t	lump_offset;
	uint32_t	lump_size;
	char		lump_name[9];
	t_wad_dir	*next;
};

struct			s_wad_menu {
	t_wad_sprite	*background;
	t_wad_sprite	**buttons;
};

struct			s_wad {
	uint8_t			*map;
	t_wad_head		head;
	t_wad_dir		*dir;
	uint32_t		color[14][256];
	uint32_t		colormap[34][256];
	t_things		*things;
	t_linedef		*linedef;
	t_sidedef		*sidedefs;
	t_vertex		*vert;
	t_seg			*segs;
	t_ssectors		*ssectors;
	t_node			*nodes;
	t_sector		*sectors;
	t_pnames		pname;
	t_texture_head	textures1;
	t_texture_head	textures2;
	t_wad_menu		*menu;
	t_wad_hud		*hud;
	char			**name;
	t_wad_sprite	**sprites;
	int				buf1;
	int				buf2;
	uint16_t		bright;
	uint16_t		baff;
	uint16_t		temp_step;
};

uint16_t		bytes_to_short(const uint8_t *data, int offset);
uint32_t		bytes_to_int(const uint8_t *data, int offset);

void			wad_loader(t_wad *wad, char *path);
bool			wad_reader(t_wad *wad);

void			wad_get_linedefs(t_wad *wad, char *name_map);
void			wad_get_vertex(t_wad *wad, char *name_map);
t_patch			wad_get_patch_info(const uint8_t *data, uint32_t offset);
void			wad_get_playpal(t_wad *wad);
void			wad_get_colormap(t_wad *wad);
void			wad_get_textures(const uint8_t *data, uint32_t offset,
					t_texture_head *texture);
void			wad_get_pnames(const uint8_t *data, t_wad_dir *dir,
					t_pnames *pname);
void			wad_get_nodes(t_wad *wad, char *map_name);
void			wad_get_sidedefs(t_wad *wad, char *name_map);
void			wad_get_segs(t_wad *wad, char *name_map);
void			wad_get_ssectors(t_wad *wad, char *name_map);
void			wad_get_sectors(t_wad *wad, char *name_map);
void			wad_get_things(t_wad *wad, char *name_map);

void			read_head_data(const uint8_t *data, int offset,
					t_wad_head *head);
void			read_dir_data(const uint8_t *data, int offset,
					t_wad_dir *dir);
void			wad_pars_name(const uint8_t *data, uint32_t offset,
					char name[9]);
void			wad_pars_box(const uint8_t *data, uint32_t offset,
					int16_t box[4]);

uint32_t		find_offset_lump(t_wad_dir *dir, char *lable, char *name_map);
uint32_t		find_size_lump(t_wad_dir *dir, char *lable, char *name_map);
uint32_t		wad_find_texture(t_wad_dir *dir, char *name);
t_wad_sprite	*sprite_create(t_wad *wad, char *name);
t_wad_hud		*init_hud(t_wad *wad);
void			put_column(t_wad *wad, uint32_t offset,
					int x, t_wad_sprite *sprite);
void			wad_destroy_patch(t_patch patch);
void			draw_hud(SDL_Surface *screen, t_wad_hud *hud,
					t_wad_player status);

void			wad_draw_menu(SDL_Surface *screen, t_wad *wad);
void			wad_init_menu(t_wad *wad);
t_wad			*init_wad(char *av);

#endif
