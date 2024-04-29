/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgoldenb <sgoldenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:03:28 by sgoldenb          #+#    #+#             */
/*   Updated: 2024/04/29 14:21:27 by sgoldenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	debug_data(t_env *env, char *src)
{
	if (src)
		printf(GREEN "//ENV @ %s\n" RESET, src);
	else
		printf(GREEN "//ENV\n" RESET);
	printf(BOLD "\t--PHILOS\n" RESET);
	for (int i = 0; i < env->nb_philo ; i ++)
	{
		printf(YELLOW "\t\t[%d] @ %p\tSTATE = %d\t THREAD @ %p\t ENV @ %p\n",
			env->philos[i]->id, env->philos[i], env->philos[i]->state,
			env->philos[i]->thread, env->philos[i]->env);
	}
}
