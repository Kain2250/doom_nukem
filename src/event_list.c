/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/15 09:15:51 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/09/05 18:50:02 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

bool			event_exit(t_doom_nukem *doom)
{
	if ((doom->sdl.event.type == SDL_QUIT ||
		doom->sdl.state[SDL_SCANCODE_ESCAPE]) && doom->frame.quit == true)
		return (true);
	else
		return (false);
}

void			assig_rect(SDL_Rect *rect, SDL_Point xy, int w, int h)
{
	rect->x = xy.x;
	rect->y = xy.y;
	rect->h = h;
	rect->w = w;
}

void			drow_color_point(SDL_Surface *dst, Uint32 color)
{
	SDL_Point	mouse;

	SDL_GetMouseState(&mouse.x, &mouse.y);
	putpixel(dst, mouse.x, mouse.y, color);
}

int				which_button(bool *mouse)
{
	*mouse = true;
	if (SDL_BUTTON(SDL_BUTTON_RIGHT) & SDL_GetMouseState(NULL, NULL))
		return (SDL_BUTTON_RIGHT);
	else if (SDL_BUTTON(SDL_BUTTON_LEFT) & SDL_GetMouseState(NULL, NULL))
		return (SDL_BUTTON_LEFT);
	else if (SDL_BUTTON(SDL_BUTTON_MIDDLE) & SDL_GetMouseState(NULL, NULL))
		return (SDL_BUTTON_MIDDLE);
	else if (SDL_BUTTON(SDL_BUTTON_X1) & SDL_GetMouseState(NULL, NULL))
		return (SDL_BUTTON_X1);
	else if (SDL_BUTTON(SDL_BUTTON_X2) & SDL_GetMouseState(NULL, NULL))
		return (SDL_BUTTON_X2);
	*mouse = false;
	return (0);
}

t_rect			rect_fill_no_malloc(int x, int y, int w, int h)
{
	t_rect		q;

	q.x = x;
	q.y = y;
	q.w = w;
	q.h = h;
	return (q);
}

void			draw_frames(t_new_win *win)
{
	t_frames	*tmp_frames;
	t_block		*tmp_block;

	tmp_frames = win->frames;
	while (win->frames)
	{
		draw_feel_rect(win->screen,
			win->frames->main_frame, win->frames->color, 1);
		if (win->frames->blocks != NULL)
		{
			tmp_block = win->frames->blocks;
			while (win->frames->blocks)
			{
				blit_surf_scaled(win->frames->blocks->block_pic, NULL,
					win->screen, win->frames->blocks->rect_block);
				win->frames->blocks = win->frames->blocks->next;
			}
			win->frames->blocks = tmp_block;
		}
		win->frames = win->frames->next;
	}
	win->frames = tmp_frames;
}

void			render_new_win(t_new_win *frame,
				Uint32 color_screen, t_rect region)
{
	draw_feel_rect(frame->screen, &region, color_screen, 1);
	draw_frames(frame);
	SDL_UpdateWindowSurface(frame->win);
}

t_block			*new_block(SDL_Surface *pic, t_rect *rect_block)
{
	t_block		*block;

	block = (t_block *)ft_memalloc(sizeof(t_block));
	block->block_pic = pic;
	block->rect_block = (t_rect *)ft_memalloc(sizeof(t_rect));
	block->rect_block->x = rect_block->x;
	block->rect_block->y = rect_block->y;
	block->rect_block->w = rect_block->w;
	block->rect_block->h = rect_block->h;
	block->next = NULL;
	return (block);
}

void			open_new_win(t_new_win *frame, TTF_Font *font)
{
	t_rect		q;
	SDL_Color	color;

	color.r = 0;
	color.g = 0;
	color.b = 0;
	color.a = 255;
	frame->win = SDL_CreateWindow("New_win", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, 600, 700, SDL_WINDOW_SHOWN);
	frame->screen = SDL_GetWindowSurface(frame->win);
	frame->quit = false;
	q = rect_fill_no_malloc(10, 10, 60, 80);
	frame->frames = new_frame(&q, 0xa0a0a0,
		new_block(TTF_RenderText_Blended(font, "Knopka", color), &q));
	render_new_win(frame, 0xafafaf,
		rect_fill_no_malloc(0, 0, frame->screen->w, frame->screen->h));
}

void			close_new_win(t_new_win *frame)
{
	if (frame->screen != NULL)
		SDL_FreeSurface(frame->screen);
	if (frame->win != NULL)
		SDL_DestroyWindow(frame->win);
	frame->win = NULL;
	frame->quit = true;
}

void			keybord_events(t_doom_nukem *doom)
{
	if (doom->sdl.state[SDL_SCANCODE_N] && doom->frame.win == NULL)
		open_new_win(&doom->frame, doom->sdl.fonts[font_button]);
	if ((doom->sdl.state[SDL_SCANCODE_C] ||
		doom->sdl.state[SDL_SCANCODE_ESCAPE]) && doom->frame.win != NULL)
		close_new_win(&doom->frame);
	if (doom->sdl.state[SDL_SCANCODE_T] && doom->frame.win != NULL)
		SDL_SetWindowTitle(doom->frame.win, "Change_name_win");
}

void			mouse_events(t_doom_nukem *doom)
{
	int			button;

	if (doom->mouse.is_presed == false)
		SDL_GetMouseState(&doom->mouse.prew_x, &doom->mouse.prew_y);
	button = which_button(&doom->mouse.is_presed);
	if (SDL_BUTTON_RIGHT == button)
		scale_rect_texture(doom->sdl.surface, doom->mouse, doom->sdl.textures[texture_test2]);
		// scale_frame(doom->sdl.surface, doom->mouse, 0x00ff00, draw_rect);
	else if (SDL_BUTTON_LEFT == button)
		draw_fill_circl(doom->sdl.surface, 20,
			fill_point(doom->mouse.prew_x, doom->mouse.prew_y), 0xff00ff);
	else if (SDL_BUTTON_MIDDLE == button)
		drag_and_drop(doom->sdl.textures[texture_test], doom->sdl.surface);
}

void			event_list(t_doom_nukem *doom)
{
	SDL_PumpEvents();
	doom->sdl.state = SDL_GetKeyboardState(NULL);
	SDL_GetWindowSize(doom->sdl.window, &doom->sdl.width, &doom->sdl.height);
	if (event_exit(doom) == true)
		doom->quit = true;
	else
	{
		keybord_events(doom);
		mouse_events(doom);
	}
}
