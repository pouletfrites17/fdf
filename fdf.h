/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <apetitje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/15 18:52:56 by apetitje          #+#    #+#             */
/*   Updated: 2017/02/10 16:21:55 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "mlx.h"
# include "ft_printf.h"
# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>

# define DISTANCE	105
# define ESC		53
# define PLUS		69
# define MINUS		78
# define RIGHT		124
# define DOWN		125
# define UP			126
# define LEFT		123
# define SPACE		49
# define BUFF_SIZE	1024
# define P			((t_s *)param)
# define S			struc

typedef struct	s_s
{
	void		*mlx;
	void		*win;
	void		*image;
	char		*im_ptr;
	t_list		**map;
	int			bpp;
	int			endian;
	int			size_line;
	double		size1;
	double		size2;
	double		size1_orig;
	double		width;
	double		height;
	int			max_z;
	int			min_z;
	int			nb_lines;
	double		max_s2;
	double		max_s1;
	double		win_height;
	double		win_width;
	int			max_line_len;
	int			win_x;
	int			win_y;
}				t_s;

typedef struct	s_points
{
	int			x1;
	int			y1;
	int			x2;
	int			y2;
}				t_points;

int				input_to_map(const char *s, t_s *struc);
void			ft_draw(t_s *struc);
void			free_map(t_list **map);
int				ft_event(int keycode, void *param);

#endif
