/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_kit.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 19:37:12 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/12/12 19:57:25 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPRITE_KIT_H
# define SPRITE_KIT_H

# define PEH 5

/*
**Пехотинец - 1 фаза состояние покоя
*/
# define S_PEH_1 peh_e1

/*
**Пехотинец - 2 фаза движения
*/
# define S_PEH_2 peh_a1

/*
**Пехотинец - 3 фаза движения
*/
# define S_PEH_3 peh_b1

/*
**Пехотинец - 4 фаза движения
*/
# define S_PEH_4 peh_c1

/*
**Пехотинец - 5 фаза движения
*/
# define S_PEH_5 peh_d1

/*
**Пехотинец - Выстрел
*/
# define S_PEH_G peh_f1

/*
**Пехотинец - Урон
*/
# define S_PEH_DM peh_g1

/*
**Пехотинец - анимация смерти
*/
# define S_PEH_D peh_h0

# define IMP 5

/*
**Имп - 1 фаза состояние покоя
*/
# define S_IMP_1 "TROOE1" "TROOE2E8" "TROOE3E7" "TROOE4E6" "TROOE5"

/*
**Имп - 2 фаза движения
*/
# define S_IMP_2 "TROOA1" "TROOA2A8" "TROOA3A7" "TROOA4A6" "TROOA5"

/*
**Имп - 3 фаза движения
*/
# define S_IMP_3 "TROOB1"; name[1] = "TROOB2B8"; name[2] = "TROOB3B7"; S_IMP_33
# define S_IMP_33 name[3] = "TROOB4B6"; name[4] = "TROOB5"

/*
**Имп - 4 фаза движения
*/
# define S_IMP_4 "TROOC1"; name[1] = "TROOC2C8"; name[2] = "TROOC3C7"; S_IMP_44
# define S_IMP_44 name[3] = "TROOC4C6"; name[4] = "TROOC5"

/*
**Имп - 5 фаза движения
*/
# define S_IMP_5 "TROOD1"; name[1] = "TROOD2D8"; name[2] = "TROOD3D7"; S_IMP_55
# define S_IMP_55 name[3] = "TROOD4D6"; name[4] = "TROOD5"

/*
**Имп - Выстрел
*/
# define S_IMP_G "TROOG1"; name[1] = "TROOG2G8"; name[2] = "TROOG3G7"; S_IMP_GG
# define S_IMP_GG name[3] = "TROOG4G6"; name[4] = "TROOG5"

/*
**Имп - Урон
*/
# define S_IMP_DM "TROOH1"; name[1] = "TROOH2H8"; name[2] = "TROOH3H7"; S_IMP_MM
# define S_IMP_MM name[3] = "TROOH4H6"; name[4] = "TROOH5"

/*
**Имп - анимация смерти
*/
# define S_IMP_D "TROOI0"; name[1] = "TROOJ0"; name[2] = "TROOK0"; S_IMP_DD
# define S_IMP_DD name[3] = "TROOL0"; name[4] = "TROOM0"

# define SAW 2

/*
**Бензопила - анимация покоя
*/
# define S_SAW_S "SAWGC0"; name[1] = "SAWGD0"

/*
**Бензопила - анимация атаки
*/
# define S_SAW_G "SAWGA0"; name[1] = "SAWGB0"

# ifdef __APPLE__
#  include "SDL.h"
# elif __linux__
#  include "SDL2/SDL.h"
# endif

# include <stdint.h>
# include "rect.h"

typedef struct s_wad_player	t_wad_player;
typedef struct s_wad_hud	t_wad_hud;
typedef struct s_wad_sprite	t_wad_sprite;
typedef enum e_name_peh		t_name_peh;
typedef enum e_name_pig		t_name_pig;
typedef enum e_name_gun		t_name_gun;
typedef enum e_name_mili	t_name_mili;

enum		e_name_peh {
	peh_a1,
	peh_a2a8,
	peh_a3a7,
	peh_a4a6,
	peh_a8,
	peh_b1,
	peh_b2b8,
	peh_b3b7,
	peh_b4b6,
	peh_b8,
	peh_c1,
	peh_c2c8,
	peh_a3c7,
	peh_c4c6,
	peh_c8,
	peh_d1,
	peh_d2d8,
	peh_d3d7,
	peh_d4d6,
	peh_d8,
	peh_e1,
	peh_e2e8,
	peh_e3e7,
	peh_e4e6,
	peh_e8,
	peh_f1,
	peh_f2f8,
	peh_f3f7,
	peh_f4f6,
	peh_f8,
	peh_g1,
	peh_g2g8,
	peh_g3g7,
	peh_g4g6,
	peh_g8,
	peh_h0,
	peh_h1,
	peh_h2,
	peh_h3,
	peh_h4,
	peh_total
};

struct		s_wad_sprite {
	char		*name;
	uint32_t	*pixel;
	int32_t		w;
	int32_t		h;
	int32_t		left_offset;
	int32_t		top_offset;
};

struct		s_wad_hud {
	t_wad_sprite	*stbar;
	t_wad_sprite	**digit;
	t_wad_sprite	**big_digit;
};

struct		s_wad_player {
	t_limit			health;
	t_limit			shield;
	t_limit			ammo[4];
	uint8_t			cur_gan;
	t_wad_sprite	**gun;
};

uint32_t	get_pixel_sprite(t_wad_sprite *surface, int x, int y);
void		blit_sprite_scaled(t_wad_sprite *src, t_rect *rsrc,
				SDL_Surface *dst, t_rect *rdst);
void		blit_gan_scaled(t_wad_sprite *src, SDL_Surface *dst);
void		blit_hud_scaled(t_wad_sprite *src, SDL_Surface *dst);
void		blit_sprite_scale(t_wad_sprite *src,
				SDL_Surface *dst, t_rectf rdst);

#endif
