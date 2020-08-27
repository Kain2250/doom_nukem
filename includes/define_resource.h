/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_resource.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 15:07:49 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/08/23 18:00:50 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_RESOURCE_H
# define DEFINE_RESOURCE_H

# define IMG_TEST "resource/textures/test.bmp"
# define IMG_IRON "resource/textures/ract_iron.bmp"

typedef enum		e_texture
{
	texture_test,
	texture_iron,
	texture_test2,
	texture_editor_back,
	texture_total
}					t_texture;

#endif