/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_f.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgoldenb <sgoldenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 14:38:01 by sgoldenb          #+#    #+#             */
/*   Updated: 2024/04/19 09:51:26 by sgoldenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_utils.h"

void	ft_putchar_f(char c, int *len)
{
	write(1, &c, 1);
	*len += 1;
}
