/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_kit.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 19:37:12 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/12/10 19:40:23 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPRITE_KIT_H
# define SPRITE_KIT_H

# define PEH 5

/*
**Пехотинец - 1 фаза состояние покоя
*/
# define S_PEH_1 "POSSE1"; name[1] = "POSSE2E8"; name[2] = "POSSE3E7"; S_PEH_11
# define S_PEH_11 name[3] = "POSSE4E6"; name[4] = "POSSE5"

/*
**Пехотинец - 2 фаза движения
*/
# define S_PEH_2 "POSSA1"; name[1] = "POSSA2A8"; name[2] = "POSSA3A7"; S_PEH_22
# define S_PEH_22 name[3] = "POSSA4A6"; name[4] = "POSSA5"

/*
**Пехотинец - 3 фаза движения
*/
# define S_PEH_3 "POSSB1"; name[1] = "POSSB2B8"; name[2] = "POSSB3B7"; S_PEH_33
# define S_PEH_33 name[3] = "POSSB4B6"; name[4] = "POSSB5"

/*
**Пехотинец - 4 фаза движения
*/
# define S_PEH_4 "POSSC1"; name[1] = "POSSC2C8"; name[2] = "POSSC3C7"; S_PEH_44
# define S_PEH_44 name[3] = "POSSC4C6"; name[4] = "POSSC5"

/*
**Пехотинец - 5 фаза движения
*/
# define S_PEH_5 "POSSD1"; name[1] = "POSSD2D8"; name[2] = "POSSD3D7"; S_PEH_55
# define S_PEH_55 name[3] = "POSSD4D6"; name[4] = "POSSD5"

/*
**Пехотинец - Выстрел
*/
# define S_PEH_G "POSSF1"; name[1] = "POSSF2F8"; name[2] = "POSSF3F7"; S_PEH_GG
# define S_PEH_GG name[3] = "POSSF4F6"; name[4] = "POSSF5"

/*
**Пехотинец - Урон
*/
# define S_PEH_DM "POSSG1"; name[1] = "POSSG2G8"; name[2] = "POSSG3G7"; S_PEH_MM
# define S_PEH_MM name[3] = "POSSG4G6"; name[4] = "POSSG5"

/*
**Пехотинец - анимация смерти
*/
# define S_PEH_D "POSSH0"; name[1] = "POSSI0"; name[2] = "POSSJ0"; S_PEH_DD
# define S_PEH_DD name[3] = "POSSK0"; name[4] = "POSSL0"

# define IMP 5

/*
**Имп - 1 фаза состояние покоя
*/
# define S_IMP_1 "TROOE1"; name[1] = "TROOE2E8"; name[2] = "TROOE3E7"; S_IMP_11
# define S_IMP_11 name[3] = "TROOE4E6"; name[4] = "TROOE5"

/*
**Имп - 2 фаза движения
*/
# define S_IMP_2 "TROOA1"; name[1] = "TROOA2A8"; name[2] = "TROOA3A7"; S_IMP_22
# define S_IMP_22 name[3] = "TROOA4A6"; name[4] = "TROOA5"

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

typedef struct		s_wad_sprite
{
	char			*name;
	uint32_t		*pixel;
	int32_t			w;
	int32_t			h;
	int32_t			left_offset;
	int32_t			top_offset;
}					t_wad_sprite;

typedef struct		s_wad_hud
{
	t_wad_sprite	*stbar;
	t_wad_sprite	**digit;
	t_wad_sprite	**big_digit;
}					t_wad_hud;

typedef struct		s_wad_player
{
	t_limit			health;
	t_limit			shield;
	t_limit			ammo[4];
	uint8_t			cur_gan;
	t_wad_sprite	**gun;
}					t_wad_player;

uint32_t			get_pixel_sprite(t_wad_sprite *surface, int x, int y);
void				blit_sprite_scaled(t_wad_sprite *src, t_rect *rsrc,
						SDL_Surface *dst, t_rect *rdst);
void				blit_gan_scaled(t_wad_sprite *src, SDL_Surface *dst);
void				blit_hud_scaled(t_wad_sprite *src, SDL_Surface *dst);
void				blit_sprite_scale(t_wad_sprite *src,
						SDL_Surface *dst, t_rectf rdst);


#endif
