/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/19 17:39:29 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/12/12 16:15:22 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// # include "SDL.h"
// # include "SDL_image.h"
#include <stdlib.h>
#include <stdio.h>
#include "libft.h"
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
	// SDL_Surface		*front;
	// SDL_Surface		*rear;
}					t_linedef;

typedef struct		s_tree
{
	void			*data;
	short			num_nod;
	struct s_tree	*node_front;
	struct s_tree	*node_rear;
}					t_tree;

int			*data_addit(int *data)
{
	int		*ret;

	ret = (int *)ft_xmemalloc(sizeof(int));
	*ret = *data;
	return (ret);
}

t_tree		*new_node(int *data, short num_nod)
{
	t_tree	*node;

	node = (t_tree *)ft_xmemalloc(sizeof(t_tree));
	node->data = data_addit(data);
	node->num_nod = num_nod;
	node->node_front = NULL;
	node->node_rear = NULL;
	return (node);
}

void		node_filling(int *arr)
{
	short	num_nod;
	int		i;

	i = 0;
}

void		draw_map(int **arr)
{
	int		i;
	int		j;

	i = 0;
	if (arr[i][j] == 1);
		
}

int			main(void)
{
	int		**arr;
	int		i;
	int		j;

	i = 0;
	arr = ft_xmemalloc(sizeof(int *) * 7);
	while (i != 7)
	{
		j = 0;
		arr[i] = ft_xmemalloc(sizeof(int) * 10);
		while (j != 10)
		{
			if ((i == 1 && j == 1) || (i == 1 && j == 3) || (i == 1 && j == 5) || (i == 1 && j == 8) ||
				(i == 2 && j == 3) || (i == 2 && j == 5) ||
				(i == 4 && j == 1) || (i == 4 && j == 4) || (i == 4 && j == 7) || (i == 4 && j == 8) ||
				(i == 5 && j == 4) || (i == 5 && j == 7))
				arr[i][j] = 1;
			else
				arr[i][j] = 0;
			j++;
		}
		i++;
	}
	draw_map(arr);
	// node_filling(arr);
	return (0);
}
