/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_map.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarc <mcarc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 20:37:43 by mcarc             #+#    #+#             */
/*   Updated: 2020/08/18 23:11:55 by mcarc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EDITOR_MAP_H
# define EDITOR_MAP_H

#include "doom_nukem.h"

# define MAP_WIDTH 300
# define MAP_HEIGHT 200
# define MAX_ROOM_VERTEXES 4

typedef struct			s_vertex
{
	int					x;
	int					y;
}						t_vertex;

typedef struct			s_sector
{
	t_vertex			vertex[MAX_ROOM_VERTEXES];
	unsigned int		height;
	struct t_sector		*next;
	/*space for other entities*/
}						t_sector;

typedef struct			s_field
{
	SDL_Surface			*surface;
	bool				map[MAP_HEIGHT][MAP_WIDTH];
	double		zoom;
	struct t_sector		*sectors;
}						t_field;

typedef struct			s_map_editor
{
	struct s_sdl_sys	sdl;
	t_field		field;
}						t_map_editor;



void					draw_map_field(t_map_editor *map_editor);
t_map_editor			*map_editor_init(t_doom_nukem *doom);
void					map_editor_event_list(t_map_editor *map_editor);

#endif
