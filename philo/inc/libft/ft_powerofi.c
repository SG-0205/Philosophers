/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_powerofi.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgoldenb <sgoldenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 17:19:11 by sgoldenb          #+#    #+#             */
/*   Updated: 2024/04/16 17:22:33 by sgoldenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_powerofi(int nb, int exp)
{
	if (exp == 0)
		return (1);
	while (exp > 1)
	{
		nb = nb * nb;
		exp --;
	}
	return (nb);
}
