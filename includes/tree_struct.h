/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_struct.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/19 13:52:31 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/09/22 19:51:19 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_STRUCT_H
# define TREE_STRUCT_H

# include "SDL.h"
# include "SDL_image.h"
/*
** Флаги стен - Преграждает путь игрокам и монстрам
*/
# define LD_BLOCK_ALL 0
/*
** Флаги стен - Преграждает путь монстрам
*/
# define LD_BLOCK_MONSTER 0b1
/*
** Флаги стен - Двусторонняя
*/
# define LD_SIDED 0b10
/*
** Флаги стен - Верхняя текстура отключена
*/
# define LD_TOP_TEXTURE 0b100
/*
** Флаги стен - Нижняя текстура отключена
*/
# define LD_BOTOM_TEXTURE 0b1000
/*
** Флаги стен - Секрет
*/
# define LD_SECRET 0b10000
/*
** Флаги стен - Препятствует звуку
*/
# define LD_INTERFERENS_SOUND 0b100000
/*
** Флаги стен - Никогда не показывается на автокарте
*/
# define LD_NEWER_SHOW 0b1000000
/*
** Флаги стен - Всегда показывается на автокарте
*/
# define LD_ALWAYS_SHOW 0b10000000
/*
** Вершина
*/
typedef struct		s_vertex
{
	int16_t			x;
	int16_t			y;
}					t_vertex;
/*
** Стена
*/
typedef struct		s_linedef
{
	t_vertex		start;
	t_vertex		finish;
	uint16_t		flags;
	uint16_t		type;
	uint16_t		mark_sector;
	SDL_Surface		*front;
	SDL_Surface		*rear;
}					t_linedef;
/*
** Дерево
*/
typedef struct		s_tree
{
	void			*data;
	struct s_tree	*node_front;
	struct s_tree	*node_rear;
}					t_tree;

#endif
