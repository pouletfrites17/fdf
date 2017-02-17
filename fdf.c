/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <apetitje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/15 18:53:32 by apetitje          #+#    #+#             */
/*   Updated: 2017/02/10 16:55:38 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		free_map(t_list **map)
{
	int		i;
	t_list	*ptr;

	i = 0;
	if (map)
		while (map[i])
		{
			while (map[i])
			{
				ptr = map[i];
				map[i] = map[i]->next;
				free(ptr->data);
				free(ptr);
				ptr = NULL;
			}
			++i;
		}
	map = NULL;
}

static void	init_struc(t_s *struc)
{
	struc->win_x = 0;
	struc->win_y = 10;
	struc->max_s1 = 32;
	struc->size1 = 32;
	struc->max_s2 = 16;
	struc->size2 = 16;
	struc->win_width = 3500;
	struc->win_height = 1200;
	S->size1 = S->win_width / S->width;
	S->size2 = S->win_height / S->height;
	if (S->size2 > 16)
		S->size2 = 16;
	else if (S->size2 < 1)
	{
		S->size1 = 2;
		S->size2 = 1;
	}
}

static void	fdf(t_s *struc)
{
	init_struc(struc);
	struc->mlx = mlx_init();
	mlx_do_key_autorepeaton(S->mlx);
	if (S->size1 > S->size2 * 2)
		S->size1 = S->size2 * 2;
	else if (S->size1 / 2 >= 1)
		S->size2 = S->size1 / 2;
	S->max_s1 = S->size1;
	S->max_s2 = S->size2;
	S->width *= S->size1;
	S->height *= S->size2;
	S->image = mlx_new_image(S->mlx, S->width, S->height);
	S->im_ptr = mlx_get_data_addr(S->image, &S->bpp, &S->size_line, &S->endian);
	S->win_width = S->width;
	S->win_height = S->height;
	if ((S->win = mlx_new_window(S->mlx, S->win_width, S->win_height, "fdf")))
	{
		S->size1_orig = S->size1;
		ft_draw(struc);
	}
	mlx_hook(S->win, 2, 1L << 0, &ft_event, struc);
	mlx_loop(S->mlx);
}

static void	read_buf(char **input, int fd)
{
	char	*ptr;
	int		ret;
	char	buffer[BUFF_SIZE + 1];

	while ((ret = read(fd, buffer, BUFFSIZE)))
	{
		buffer[ret] = '\0';
		ptr = *input;
		ft_asprintf(input, "%s%s", *input, buffer);
		if (ptr)
			free(ptr);
	}
	close(fd);
}

int			main(int argc, char **argv)
{
	int		fd;
	char	*input;
	t_s		struc;

	S.map = NULL;
	if (argc != 2)
		ft_dprintf(2, "usage : fdf [file]\n");
	else
	{
		input = NULL;
		if ((fd = open(argv[1], O_RDONLY)) == -1)
			perror("fdf ");
		else
		{
			read_buf(&input, fd);
			if (input && input_to_map(input, &struc))
				fdf(&struc);
			else
				ft_dprintf(2, "map error\n");
			free(input);
		}
	}
	free_map(S.map);
	return (0);
}
