/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgoldenb <sgoldenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 15:47:06 by sgoldenb          #+#    #+#             */
/*   Updated: 2024/08/08 19:22:37 by sgoldenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*print_full(t_philo *table)
{
	mutex_operation(table->locks[PRINT], LOCK);
	printf(BOLD "%ld All philosophers ate %d time each.\n" RESET,
		(get_time(MS) - table->start_time), table->nb_meals);
	mutex_operation(table->locks[PRINT], UNLOCK);
	set_value(table->locks[STRUCT], &table->flag_stop, TRUE);
	return (NULL);
}

void	print_state(t_thinker *phi, int phi_state)
{
	if (phi->ate == FULL)
		return ;
	mutex_operation(phi->table->locks[PRINT], LOCK);
	if (phi_state == EATING && !get_value(phi->table->locks[STRUCT],
			(int*)&phi->table->flag_stop))
		printf(GREEN "%ld %d is eating\n" RESET, (get_time(MS)
				- phi->table->start_time), phi->id + 1);
	else if ((phi_state == TAKE_FF || phi_state == TAKE_SF)
		&& !get_value(phi->table->locks[STRUCT], (int *)&phi->table->flag_stop))
		printf(BLUE "%ld %d has taken a fork\n" RESET, ((get_time(MS)
					- phi->table->start_time)), phi->id + 1);
	else if (phi_state == DEAD)
		printf(RED "%ld %d died\n" RESET, (get_time(MS)
				- phi->table->start_time), phi->id + 1);
	else if (phi_state == SLEEPING && !get_value(phi->table->locks[STRUCT],
			(int *)&phi->table->flag_stop))
		printf(YELLOW "%ld %d is sleeping\n" RESET, (get_time(MS)
				- phi->table->start_time), phi->id + 1);
	else if (phi_state == THINKING && !get_value(phi->table->locks[STRUCT],
			(int *)&phi->table->flag_stop))
		printf(CYAN "%ld %d is thinking\n" RESET, (get_time(MS)
				- phi->table->start_time), phi->id + 1);
	mutex_operation(phi->table->locks[PRINT], UNLOCK);
}

// void	print_vals(t_philo *vals)
// {
// 	int	i;

// 	i = -1;
// 	if (!vals)
// 		printf(RED "NO VALS\n" RESET);
// 	printf(BOLD GREEN "VALS @ %p\n" RESET, vals);
// 	printf(BOLD YELLOW "\tBASIC INFO\n" RESET);
// 	printf(CYAN "\t\tNB_PHI : %d\n\t\tTTE : %d\n\t\tTTS : %d\n\t\tTTD : %d\n"
// 		RESET, vals->nb_philos, vals->tte, vals->tts, vals->ttd);
// 	printf(CYAN "\t\tSTOP FLAG : %d\n\t\t(NB MEALS : %d)\n" RESET,
// 		vals->flag_stop, vals->nb_meals);
// 	printf(BOLD YELLOW "\tMUTEXES\n" RESET);
// 	printf(GREEN "\t\tFORKS @ %p\n" RESET, vals->forks);
// 	while (vals->forks[++i])
// 		printf(MAGENTA "\t\t\t@ %p\n" RESET, vals->forks[i]);
// 	i = -1;
// 	printf(GREEN "\t\tLOCKS @ %p\n" RESET, vals->locks);
// 	while (vals->locks[++i])
// 		printf(MAGENTA "\t\t\t@ %p\n" RESET, vals->locks[i]);
// 	i = -1;
// 	printf(BOLD BLUE "\tTHREADS @ %p\n" RESET, vals->philos);
// 	while (vals->philos[++i])
// 	{
// 		printf(MAGENTA "\t\t\t@ %p\n" RESET, vals->philos[i]);
// 		printf(CYAN "\t\t\t\tTHREAD@ %p\n" RESET, vals->philos[i]->thread);
// 		printf(CYAN "\t\t\t\tE_C %d\n" RESET, vals->philos[i]->eat_count);
// 		printf(CYAN "\t\t\t\tTABLE@ %p\n" RESET, vals->philos[i]->table);
// 		printf(CYAN "\t\t\t\tID %d\n" RESET, vals->philos[i]->id);
// 	}
// }