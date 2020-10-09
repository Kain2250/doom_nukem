/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bytes_shift.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 20:38:16 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/10/09 20:43:36 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

int16_t		bytes_to_ishort(const uint8_t *data, int offset)
{
	return ((data[offset + 1] << 8) | data[offset]);
}

uint16_t	bytes_to_short(const uint8_t *data, int offset)
{
	return ((data[offset + 1] << 8) | data[offset]);
}

uint32_t	bytes_to_int(const uint8_t *data, int offset)
{
	return ((data[offset + 3] << 24) |
			(data[offset + 2] << 16) |
			(data[offset + 1] << 8) | data[offset]);
}
