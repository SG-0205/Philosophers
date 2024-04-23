/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgoldenb <sgoldenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 12:50:44 by sgoldenb          #+#    #+#             */
/*   Updated: 2024/04/23 12:51:24 by sgoldenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	find_fork(t_thinker *thinker, int to_find)
{
	if (to_find == R_FORK)
	{
		if (thinker->id == thinker->sval_link->nb_philo - 1)
			return (0);
		else
			return (thinker->id + 1);
	}
	else if (to_find == L_FORK)
	{
		if (thinker->id == 0)
			return (thinker->sval_link->nb_philo - 1);
		else
			return (thinker->id - 1);
	}
	return (0);
}
