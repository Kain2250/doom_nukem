/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_kit.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 19:37:12 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/11/21 21:19:53 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPRITE_KIT_H
# define SPRITE_KIT_H

/*Пехотинец - 1 фаза состояние покоя*/
# define S_PEH_1	"POSSE1", "POSSE2E8", "POSSE3E7", "POSSE4E6", "POSSE5"
/*Пехотинец - 2 фаза движения*/
# define S_PEH_2	"POSSA1", "POSSA2A8", "POSSA3A7", "POSSA4A6", "POSSA5"
/*Пехотинец - 3 фаза движения*/
# define S_PEH_3	"POSSB1", "POSSB2B8", "POSSB3B7", "POSSB4B6", "POSSB5"
/*Пехотинец - 4 фаза движения*/
# define S_PEH_4	"POSSC1", "POSSC2C8", "POSSC3C7", "POSSC4C6", "POSSC5"
/*Пехотинец - 5 фаза движения*/
# define S_PEH_5	"POSSD1", "POSSD2D8", "POSSD3D7", "POSSD4D6", "POSSD5"
/*Пехотинец - Выстрел*/
# define S_PEH_G	"POSSF1", "POSSF2F8", "POSSF3F7", "POSSF4F6", "POSSF5"
/*Пехотинец - Урон*/
# define S_PEH_DM	"POSSG1", "POSSG2G8", "POSSG3G7", "POSSG4G6", "POSSG5"
/*Пехотинец - анимация смерти*/
# define S_PEH_D	"POSSH0", "POSSI0", "POSSJ0", "POSSK0", "POSSL0"

/*Имп - 1 фаза состояние покоя*/
# define S_IMP_1	"TROOE1", "TROOE2E8", "TROOE3E7", "TROOE4E6", "TROOE5"
/*Имп - 2 фаза движения*/
# define S_IMP_2	"TROOA1", "TROOA2A8", "TROOA3A7", "TROOA4A6", "TROOA5"
/*Имп - 3 фаза движения*/
# define S_IMP_3	"TROOB1", "TROOB2B8", "TROOB3B7", "TROOB4B6", "TROOB5"
/*Имп - 4 фаза движения*/
# define S_IMP_4	"TROOC1", "TROOC2C8", "TROOC3C7", "TROOC4C6", "TROOC5"
/*Имп - 5 фаза движения*/
# define S_IMP_5	"TROOD1", "TROOD2D8", "TROOD3D7", "TROOD4D6", "TROOD5"
/*Имп - Выстрел*/
# define S_IMP_G	"TROOG1", "TROOG2G8", "TROOG3G7", "TROOG4G6", "TROOG5"
/*Имп - Урон*/
# define S_IMP_DM	"TROOH1", "TROOH2H8", "TROOH3H7", "TROOH4H6", "TROOH5"
/*Имп - анимация смерти*/
# define S_IMP_D	"TROOI0", "TROOJ0", "TROOK0", "TROOL0", "TROOM0"

/* Бензопила - анимация покоя*/
# define S_SAW_S	"SAWGС0", "SAWGD0"
/* Бензопила - анимация атаки*/
# define S_SAW_S	"SAWGA0", "SAWGB0"

#endif