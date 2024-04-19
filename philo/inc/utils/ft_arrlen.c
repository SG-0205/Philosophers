/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgoldenb <sgoldenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 19:07:05 by sgoldenb          #+#    #+#             */
/*   Updated: 2024/04/19 15:40:06 by sgoldenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_utils.h"

int	ft_arrlen(void **array)
{
	int	size;

	size = -1;
	if (!array)
		return (size);
	while (array[++size])
		;
	return (size);
}

// int	main(void)
// {
// 	char *array[] = {"TRUE"/*, "TRUE", "FALSE"*/, NULL};

// 	ft_printf("3 = %d\n", ft_arrlen((void **)array));
// 	return (0);
// }