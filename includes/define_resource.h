/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_resource.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 15:07:49 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/09/09 13:18:54 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_RESOURCE_H
# define DEFINE_RESOURCE_H

# define IMG_TEST "resource/textures/test.bmp"
# define IMG_IRON "resource/textures/ract_iron.bmp"
# define IMG_ICON "resource/textures/icon.bmp"
# define IMG_EDITHOR_BACK "resource/textures/editor_back.bmp"
# define IMG_TEST2 "resource/textures/sw2cmt.bmp"

# define FONT_BUTTON "resource/font/button.otf"
# define FONT_TEXT "resource/font/robotron.otf"

typedef enum		e_texture
{
	texture_icon,
	texture_test,
	texture_iron,
	texture_test2,
	texture_editor_back,
	texture_total
}					t_texture;

typedef enum		e_font
{
	font_button,
	font_text,
	font_total
}					t_font;

#endif
