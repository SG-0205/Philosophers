/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgoldenb <sgoldenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 20:44:07 by sgoldenb          #+#    #+#             */
/*   Updated: 2024/04/24 14:28:32 by sgoldenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	error_message(int errcode, char *source)
{
	if (source)
		printf("%s : erreur %d\n", source, errcode);
	else
		printf("Erreur %d\n", errcode);
	return (errcode);
}

int	usage(void)
{
	printf(YELLOW ITALIC
		"./philo [nb_philos] [ttd] [tte] [tts] (total_meals)" RESET);
	return (1);
}

void	print_data(t_philo *data, char *location)
{
	printf(GREEN "///DATA @ %s\n" RESET, location);
	printf(BOLD"\t<--START_ARGS-->\n" RESET YELLOW);
	printf("\t\t*STRUCT = %p\n", data->start_args);
	printf("\t\tNB_PHILOS = %d\n", data->start_args->nb_philo);
	printf("\t\tTTD = %d\n", data->start_args->ttd);
	printf("\t\tTTE = %d\n", data->start_args->tte);
	printf("\t\tTTS = %d\n", data->start_args->tte);
	if (data->start_args->total_meals != ENDLESS)
		printf("\t\t(TOTAL_MEALS) = %d\n", data->start_args->total_meals);
	printf("\t\tLOCK = %p\n" RESET, data->start_args->tmeals_lock);
	printf(RESET BOLD"\t<--PHILOS-->\n"RESET YELLOW);
	for (int i = 0; data->philos[i]; i ++)
		printf("\t\tPHILO [%d] =\t %p\tSTATE =\t%d @ %p\tDEFVALS->%p\tTABLE->%p\n", data->philos[i]->id, data->philos[i], data->philos[i]->state, data->philos[i]->thread, data->philos[i]->sval_link, data->philos[i]->sval_link->tmeals_lock);
	printf(RESET BOLD"\t<--FORKS-->\n" RESET YELLOW);
	for (int i = 0; i < data->start_args->nb_philo; i++)
		printf("\t\t[%d]LOCK = \t%p\tSTATE = %d\n", i + 1, data->forks[i]->lock, data->forks[i]->state);
	printf(RESET);
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
	create_threads(data);
	return (0);
}
