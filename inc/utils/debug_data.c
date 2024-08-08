/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgoldenb <sgoldenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:03:28 by sgoldenb          #+#    #+#             */
/*   Updated: 2024/08/05 15:28:15 by sgoldenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	print_vals(t_philo *vals)
{
	int	i;

	i = -1;
	if (!vals)
		printf(RED "NO VALS\n" RESET);
	printf(BOLD GREEN "VALS @ %p\n" RESET, vals);
	printf(BOLD YELLOW "\tBASIC INFO\n" RESET);
	printf(CYAN "\t\tNB_PHI : %d\n\t\tTTE : %d\n\t\tTTS : %d\n\t\tTTD : %d\n"
		RESET, vals->nb_philos, vals->tte, vals->tts, vals->ttd);
	printf(CYAN "\t\tSTOP FLAG : %d\n\t\t(NB MEALS : %d)\n" RESET,
		vals->flag_stop, vals->nb_meals);
	printf(BOLD YELLOW "\tMUTEXES\n" RESET);
	printf(GREEN "\t\tFORKS @ %p\n" RESET, vals->forks);
	while (vals->forks[++i])
		printf(MAGENTA "\t\t\t@ %p\n" RESET, vals->forks[i]);
	i = -1;
	printf(GREEN "\t\tLOCKS @ %p\n" RESET, vals->locks);
	while (vals->locks[++i])
		printf(MAGENTA "\t\t\t@ %p\n" RESET, vals->locks[i]);
	i = -1;
	printf(BOLD BLUE "\tTHREADS @ %p\n" RESET, vals->philos);
	while (vals->philos[++i])
	{
		printf(MAGENTA "\t\t\t@ %p\n" RESET, vals->philos[i]);
		printf(CYAN "\t\t\t\tTHREAD@ %p\n" RESET, vals->philos[i]->thread);
		printf(CYAN "\t\t\t\tE_C %d\n" RESET, vals->philos[i]->eat_count);
		printf(CYAN "\t\t\t\tTABLE@ %p\n" RESET, vals->philos[i]->table);
		printf(CYAN "\t\t\t\tID %d\n" RESET, vals->philos[i]->id);
	}
}
