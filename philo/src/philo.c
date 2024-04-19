/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgoldenb <sgoldenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 20:44:07 by sgoldenb          #+#    #+#             */
/*   Updated: 2024/04/19 17:44:09 by sgoldenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	error_message(int errcode, char *source)
{
	if (source)
		ft_printf("%s : erreur %d\n", source, errcode);
	else
		ft_printf("Erreur %d\n", errcode);
	return (errcode);
}

int	usage(void)
{
	ft_printf(YELLOW ITALIC
		"./philo [nb_philos] [ttd] [tte] [tts] (total_meals)" RESET);
	return (1);
}

void	print_data(t_philo *data, char *location)
{
	ft_printf(GREEN "///DATA @ %s\n" RESET, location);
	ft_printf(BOLD"\t<--START_ARGS-->\n" RESET YELLOW);
	ft_printf("\t\t*STRUCT = %p\n", data->start_args);
	ft_printf("\t\tNB_PHILOS = %d\n", data->start_args->nb_philo);
	ft_printf("\t\tTTD = %d\n", data->start_args->ttd);
	ft_printf("\t\tTTE = %d\n", data->start_args->tte);
	ft_printf("\t\tTTS = %d\n", data->start_args->tte);
	ft_printf("\t\t(TOTAL_MEALS) = %d\n", data->start_args->total_meals);
	ft_printf("\t\tLOCK = %d @ %p\n" RESET, data->start_args->tmeals_lock, data->start_args->tmeals_lock);
	ft_printf(RESET BOLD"\t<--PHILOS-->\n"RESET YELLOW);
	for (int i = 0; data->philos[i]; i ++)
		ft_printf("\t\tPHILO [%d] =\t %p\tSTATE =\t%d @ %p\tDEFVALS->%p\n", i + 1, data->philos[i], data->philos[i]->state, data->philos[i]->thread, data->philos[i]->sval_link);
	ft_printf(RESET BOLD"\t<--FORKS-->\n" RESET YELLOW);
	for (int i = 0; i < data->start_args->nb_philo; i++)
		ft_printf("\t\t[%d]LOCK = \t%d @ %p\tSTATE = %d\n", i+1, data->forks[i]->lock, data->forks[i]->lock, data->forks[i]->state);
	ft_printf(RESET);
}

int	main(int argc, char **argv)
{
	t_philo		*data;

	if (argc < 5 || argc > 6 || check_args(argv, argc) == FALSE)
		return (usage());
	data = init_data(argv, argc);
	if (!data)
		return (free_and_exit(data, errno));
	print_data(data, "POST INIT");
	return (0);
}
