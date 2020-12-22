/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/15 09:15:51 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/12/22 19:59:49 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

bool			event_exit(t_doom *doom)
{
	if ((doom->sdl.event.type == SDL_QUIT ||
		doom->sdl.state[SDL_SCANCODE_ESCAPE]) && doom->frame.quit == true)
		return (true);
	else
		return (false);
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
	q = (t_rect){10, 10, 60, 80};
	frame->frames = new_frame(q, 0xa0a0a0,
		new_block(2, q, TTF_RenderText_Blended(font, "Knopka", color)));
	render_new_win(frame, 0xafafaf,
		(t_rect){0, 0, frame->screen->w, frame->screen->h});
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

void			keybord_events(t_doom *doom)
{
	// if (doom->sdl.state[SDL_SCANCODE_N] && doom->frame.win == NULL)
	// 	open_new_win(&doom->frame, doom->sdl.fonts[font_button]);
	// if ((doom->sdl.state[SDL_SCANCODE_C] ||
	// 	doom->sdl.state[SDL_SCANCODE_ESCAPE]) && doom->frame.win != NULL)
	// 	close_new_win(&doom->frame);
	// if (doom->sdl.state[SDL_SCANCODE_T] && doom->frame.win != NULL)
	// 	SDL_SetWindowTitle(doom->frame.win, "Change_name_win");
	if (doom->sdl.state[SDL_SCANCODE_D] && doom->frame.win == NULL)
	{
		if (doom->player.health.cur < doom->player.health.max)
			doom->player.health.cur++;
	}
	else if (doom->sdl.state[SDL_SCANCODE_A] && doom->frame.win == NULL)
	{
		if (doom->player.health.cur > doom->player.health.min)
			doom->player.health.cur--;
	}
	if (doom->sdl.state[SDL_SCANCODE_W])
		go += (go >= 5) ? -0.01 : 0.01;
	else if (doom->sdl.state[SDL_SCANCODE_S])
		go -= (go <= 0.01) ? -0.01 : 0.01; 
	if (doom->sdl.state[SDL_SCANCODE_E])
		doom->player.ammo[doom->player.cur_gan].cur += (doom->player.ammo[doom->player.cur_gan].cur < doom->player.ammo[doom->player.cur_gan].max) ? 1 : 0;
	else if (doom->sdl.state[SDL_SCANCODE_Q])
		doom->player.ammo[doom->player.cur_gan].cur -= (doom->player.ammo[doom->player.cur_gan].cur > doom->player.ammo[doom->player.cur_gan].min) ? 1 : 0;
	if (doom->sdl.state[SDL_SCANCODE_1])
	{
		doom->player.cur_gan = 0;
		doom->player.shot = wad_draw_pistol;
	}
	else if (doom->sdl.state[SDL_SCANCODE_2])
	{
		doom->player.cur_gan = 1;
		doom->player.shot = wad_draw_shotgun;
	}
	else if (doom->sdl.state[SDL_SCANCODE_3])
		doom->player.cur_gan = 2;
	else if (doom->sdl.state[SDL_SCANCODE_4])
		doom->player.cur_gan = 3;
}

void			event_list(t_doom *doom)
{
	SDL_PollEvent(&doom->sdl.event);
	// SDL_PumpEvents();
	if (event_exit(doom) == true)
		doom->quit = true;
	else
	{
		keybord_events(doom);
		mouse_events(doom);
	}
}
