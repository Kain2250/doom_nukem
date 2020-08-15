/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/15 06:55:31 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/08/15 07:59:19 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

int					main(int ac, char **av)
{
	t_doom_nukem	*doom;

	if (ac == 2)
	{
		doom = ft_memalloc(sizeof(t_doom_nukem));
		free(doom);
		(void)av;
	}
	else
		ft_putendl("USAGE_DOOM");
	return (0);
}