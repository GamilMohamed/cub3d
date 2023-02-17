/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgamil <mgamil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 00:39:36 by mgamil            #+#    #+#             */
/*   Updated: 2023/02/17 19:24:41 by mgamil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

#define UDIV 1
#define VDIV 1
#define VMOVE 0.0

void	print_sprite(t_sprite *s, t_plane *p, int time)
{
	while (++s->i < s->de.x)
	{
		s->tex.x = (int)((256 * (s->i - (-s->sprite_w / 2 + s->spritescreen))
					* 64 / s->sprite_w) / 256);
		if (s->transform.y > 0 && s->i > 0 && s->i < WIDTH
			&& s->transform.y < p->tex_buff[s->i])
		{
			s->k = s->ds.y - 1;
			while (++s->k < s->de.y)
			{
				s->d = (s->k - s->vmove_s) * 256 - HEIGHT * 128 + s->sprite_h
					* 128;
				s->tex.y = ((s->d * 64) / s->sprite_h) / 256;
				s->color = p->tex_clock[time][64 * s->tex.y + s->tex.x];
				if ((s->color & 0x00FFFFFF))
					p->buff[s->k][s->i] = s->color;
			}
		}
	}
}

void	init_sprite_draw(t_sprite *s)
{
	s->ds.y = -s->sprite_h / 2 + HEIGHT_2 + s->vmove_s;
	if (s->ds.y < 0)
		s->ds.y = 0;
	s->de.y = s->sprite_h / 2 + HEIGHT_2 + s->vmove_s;
	if (s->de.y >= HEIGHT)
		s->de.y = HEIGHT - 1;

	s->sprite_w = (int)fabs((HEIGHT / s->transform.y) / UDIV);
	s->ds.x = -s->sprite_w / 2 + s->spritescreen;
	if (s->ds.x < 0)
		s->ds.x = 0;
	s->de.x = s->sprite_w / 2 + s->spritescreen;
	if (s->de.x >= WIDTH)
		s->de.x = WIDTH - 1;
	// s->sprite_h = (int)fabs((HEIGHT / s->transform.y) / VDIV);
	s->i = s->ds.x - 1;
}

void	init_sprite(t_plane *p, int time, t_luno2f pos)
{
	t_sprite	s;

	s.sprite_pos.x = pos.y + 25;
	s.sprite_pos.y = pos.x + 25;
	s.z = -1;
	while (++s.z < 64)
	{
		s.sprite = s.sprite_pos - p->pos;
		s.invdet = 1.0 / (p->plane.x * p->dir.y - p->dir.x * p->plane.y);
		s.transform.x = s.invdet * (p->dir.y * s.sprite.x - p->dir.x
				* s.sprite.y);
		s.transform.y = s.invdet * (-p->plane.y * s.sprite.x + p->plane.x
				* s.sprite.y);
		s.spritescreen = (int)((WIDTH_2) * (1 + s.transform.x
					/ s.transform.y));
		s.vmove_s = (int)(VMOVE / s.transform.y);
		s.sprite_h = (int)fabs((HEIGHT / s.transform.y) / VDIV);
		init_sprite_draw(&s);
		print_sprite(&s, p, time);
	}
}
