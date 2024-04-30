/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgoldenb <sgoldenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 12:27:47 by sgoldenb          #+#    #+#             */
/*   Updated: 2024/04/29 14:48:41 by sgoldenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	usage(void)
{
	printf(YELLOW ITALIC "./philo [nb_philo] [ttd] [tte] [tts] (meals_nb)\n"
		RESET);
	return (EINVAL);
}

int	main(int argc, char **argv)
{
	t_env	*env;

	if (argc < 5 || argc > 6)
		return (usage());
	env = (t_env *)malloc(sizeof(t_env));
	if (!env)
		return (1);
	if (init_env(argc, argv, env) == TRUE)
		debug_data(env, "INIT");
	return (0);
}
