/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_index.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetitje <apetitje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/06 16:07:03 by apetitje          #+#    #+#             */
/*   Updated: 2017/01/30 18:48:31 by apetitje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_list_index(t_list **list)
{
	t_list	*ptr;
	int		index;

	index = 0;
	ptr = *list;
	if (ptr)
	{
		while (ptr != NULL)
		{
			ptr->index = index;
			ptr = ptr->next;
			++index;
		}
	}
}
