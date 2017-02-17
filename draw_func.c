/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <apetitje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 14:32:01 by apetitje          #+#    #+#             */
/*   Updated: 2017/02/10 12:50:36 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	draw_two(t_list *l, int y, t_s *struc, unsigned int col)
{
	t_points		p;
	int				x;

	p.y1 = (l->index - y - 1 + S->nb_lines) * S->size1;
	p.x1 = (l->index + y + 1 + S->max_z - *((int *)(ft_list_at(S->map[y + 1],
						l->index)->data)) * 3) * S->size2;
	p.y2 = (l->index - y + S->nb_lines) * S->size1;
	p.x2 = (l->index + y + S->max_z - *((int *)l->data) * 3) * S->size2;
	x = p.y1 - 1;
	while (++x <= p.y2)
		ft_memcpy(S->im_ptr + (p.x1 + ((p.x2 - p.x1) * (x - p.y1))
			/ (p.y2 - p.y1)) * S->size_line + S->bpp / 8 * x, &col, S->bpp / 8);
	x = p.x1 - 1;
	while (++x <= p.x2)
		ft_memcpy(S->im_ptr + x * S->size_line + S->bpp / 8 * (p.y1
			+ ((p.y2 - p.y1) * (x - p.x1)) / (p.x2 - p.x1)), &col, S->bpp / 8);
	x = p.x2 - 1;
	while (++x <= p.x1)
		ft_memcpy(S->im_ptr + x * S->size_line + S->bpp / 8 * (p.y2
			+ ((p.y1 - p.y2) * (x - p.x2)) / (p.x1 - p.x2)), &col, S->bpp / 8);
}

static void	draw_one(t_list *l, int y, t_s *struc, unsigned int col)
{
	t_points		p;
	int				x;

	p.x1 = (l->index - y + S->nb_lines) * S->size1;
	p.y1 = (l->index + y + S->max_z - *((int *)l->data) * 3) * S->size2;
	p.x2 = (l->index + 1 - y + S->nb_lines) * S->size1;
	p.y2 = (l->index + 1 + y + S->max_z - *((int *)l->next->data) * 3)
		* S->size2;
	x = p.x1 - 1;
	while (++x <= p.x2)
		ft_memcpy(S->im_ptr + (p.y1 + ((p.y2 - p.y1) * (x - p.x1))
			/ (p.x2 - p.x1)) * S->size_line + S->bpp / 8 * x, &col, S->bpp / 8);
	x = p.y1 - 1;
	while (++x <= p.y2)
		ft_memcpy(S->im_ptr + x * S->size_line + S->bpp / 8 * (p.x1
			+ ((p.x2 - p.x1) * (x - p.y1)) / (p.y2 - p.y1)), &col, S->bpp / 8);
	x = p.y2 - 1;
	while (++x <= p.y1)
		ft_memcpy(S->im_ptr + x * S->size_line + S->bpp / 8 * (p.x2
			+ ((p.x1 - p.x2) * (x - p.y2)) / (p.y1 - p.y2)), &col, S->bpp / 8);
}

void		ft_draw(t_s *struc)
{
	t_list			*ptr;
	int				y;
	unsigned int	col;

	y = 0;
	col = mlx_get_color_value(struc->mlx, 0x00FFFFFF);
	while (struc->map[y])
	{
		ptr = struc->map[y];
		while (ptr)
		{
			if (ptr->next)
				draw_one(ptr, y, struc, col);
			if (struc->map[y + 1] && ft_list_at(struc->map[y + 1], ptr->index))
				draw_two(ptr, y, struc, col);
			ptr = ptr->next;
		}
		++y;
	}
	mlx_clear_window(struc->mlx, struc->win);
	mlx_put_image_to_window(struc->mlx, struc->win, struc->image,
			struc->win_x, struc->win_y);
}
