/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <apetitje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/29 14:52:41 by apetitje          #+#    #+#             */
/*   Updated: 2017/02/10 19:05:07 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	count_lines(const char *s)
{
	int		i;
	int		nb_lines;

	i = 0;
	nb_lines = 0;
	while (s[i])
	{
		if (s[i] && s[i] != '\n')
		{
			++nb_lines;
			while (s[i] && s[i] != '\n')
				++i;
		}
		if (s[i] && s[i] == '\n')
			++i;
	}
	return (nb_lines);
}

static int	parse_map(const char *s, int *index)
{
	while (s[*index] && s[*index] == ' ')
		*index += 1;
	if (s[*index] && s[*index] == '-')
		*index += 1;
	if (s[*index] && !ft_isdigit(s[*index]))
		return (-1);
	while (s[*index] && ft_isdigit(s[*index]))
		*index += 1;
	if (s[*index] && s[*index] == ',')
	{
		if (!ft_strncmp(s + *index + 1, "0x", 2))
			while (s[*index] && s[*index] != ' ' && s[*index] != '\n')
				*index += 1;
		else
			return (-1);
	}
	if (s[*index] && s[*index] != ' ' && s[*index] != '\n')
		return (-1);
	while (s[*index] && s[*index] == ' ')
		*index += 1;
	return (0);
}

static int	fill_map(const char *s, int *index, t_s *struc, int line)
{
	int		*data;
	int		i;

	i = 0;
	while (s[*index] && s[*index] != '\n')
	{
		data = (int *)malloc(sizeof(int));
		*data = ft_atoi(s + *index);
		ft_lstaddback(&S->map[line], ft_lstnew(data, sizeof(int)));
		++i;
		if (S->max_z < *data * 3 - line * 2)
			S->max_z = *data * 3 - line * 2;
		if (S->min_z < *data * -3 - line * 2)
			S->min_z = *data * -3 - line * 2;
		if (parse_map(s, index) == -1)
			return (-1);
	}
	*index += 1;
	return (i);
}

static void	init_var(int *map_i, int *index, t_s *struc)
{
	*map_i = 0;
	*index = 0;
	S->max_line_len = 0;
	S->max_z = 0;
	S->min_z = 0;
	S->width = 0;
}

int			input_to_map(const char *s, t_s *struc)
{
	int		nb_lines;
	int		map_i;
	int		line_len;
	int		index;

	init_var(&map_i, &index, struc);
	if ((nb_lines = count_lines(s)) == 0)
		return (0);
	if (!(S->map = (t_list **)malloc(sizeof(t_list *) * (nb_lines + 1))))
		return (0);
	while (map_i < nb_lines)
	{
		S->map[map_i] = NULL;
		S->map[map_i + 1] = NULL;
		if ((line_len = fill_map(s, &index, struc, map_i)) == -1)
			return (0);
		if (S->max_line_len < line_len)
			S->max_line_len = line_len;
		ft_list_index(&S->map[map_i]);
		++map_i;
	}
	S->nb_lines = nb_lines;
	S->width = S->max_line_len + nb_lines;
	S->height = nb_lines + S->max_line_len + S->max_z + S->min_z;
	return (1);
}
