/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <apetitje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 16:49:41 by apetitje          #+#    #+#             */
/*   Updated: 2017/02/10 16:22:00 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	zoom_event(int keycode, void *param)
{
	if (keycode == PLUS)
	{
		if (P->size1 * 1.2 <= P->max_s1 && P->size1 * 1.2 / 2 <= P->max_s2)
		{
			P->size1 *= 1.2;
			P->size2 = P->size1 / 2;
		}
		else
		{
			P->size1 = P->max_s1;
			P->size2 = P->size1 / 2;
		}
	}
	else if (keycode == MINUS)
	{
		if (P->size1 * 0.8 / 2 > 1)
		{
			P->size1 *= 0.8;
			P->size2 = P->size1 / 2;
		}
	}
	mlx_destroy_image(P->mlx, P->image);
	P->image = mlx_new_image(P->mlx, P->width, P->height);
	ft_draw(param);
}

static void	destroy_event(int keycode, void *param)
{
	if (keycode == ESC)
	{
		mlx_destroy_image(P->mlx, P->image);
		mlx_destroy_window(P->mlx, P->win);
		free_map(P->map);
		exit(0);
	}
}

static void	move_event(int keycode, void *param)
{
	if (keycode == DOWN)
	{
		P->win_y += 10;
		mlx_clear_window(P->mlx, P->win);
		mlx_put_image_to_window(P->mlx, P->win, P->image, P->win_x, P->win_y);
	}
	else if (keycode == UP)
	{
		P->win_y -= 10;
		mlx_clear_window(P->mlx, P->win);
		mlx_put_image_to_window(P->mlx, P->win, P->image, P->win_x, P->win_y);
	}
	else if (keycode == LEFT)
	{
		P->win_x -= 10;
		mlx_clear_window(P->mlx, P->win);
		mlx_put_image_to_window(P->mlx, P->win, P->image, P->win_x, P->win_y);
	}
	else if (keycode == RIGHT)
	{
		P->win_x += 10;
		mlx_clear_window(P->mlx, P->win);
		mlx_put_image_to_window(P->mlx, P->win, P->image, P->win_x, P->win_y);
	}
}

static void	start_event(int keycode, void *param)
{
	if (keycode == SPACE)
	{
		P->win_y = 0;
		P->win_x = 0;
		P->size1 = P->size1_orig;
		P->size2 = P->size1 / 2;
		mlx_destroy_image(P->mlx, P->image);
		P->image = mlx_new_image(P->mlx, P->width, P->height);
		ft_draw(param);
	}
}

int			ft_event(int keycode, void *param)
{
	destroy_event(keycode, param);
	if (keycode == PLUS || keycode == MINUS)
		zoom_event(keycode, param);
	move_event(keycode, param);
	start_event(keycode, param);
	return (0);
}
