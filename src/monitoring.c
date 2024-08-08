/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgoldenb <sgoldenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 13:15:23 by sgoldenb          #+#    #+#             */
/*   Updated: 2024/08/08 15:10:17 by sgoldenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

t_bool	init_monitor(t_philo *table)
{
	if (!table)
		return (FALSE);
	table->monitor = (pthread_t *)malloc(sizeof(pthread_t));
	if (!table->monitor)
		return (FALSE);
	return (TRUE);
}

static t_bool	wait_philos(t_philo *table)
{
	t_bool	ret_val;

	mutex_operation(table->locks[MONITOR], LOCK);
	if (table->running == table->nb_philos)
		ret_val = TRUE;
	else
		ret_val = FALSE;
	mutex_operation(table->locks[MONITOR], UNLOCK);
	return (ret_val);
}

static t_bool	is_dead(t_thinker *philo)
{
	t_bool	dead;
	long	current_t;

	if (get_value(philo->phi_mut, &philo->ate) == FULL)
		return (FALSE);
	// printf("%d FLAG_STOP\n", philo->table->flag_stop);
	// printf("%ld - %ld\n", get_time(MS), get_value_l(philo->phi_mut,
			// &philo->last_meal_t));
	current_t = get_time(MS) - get_value_l(philo->phi_mut, &philo->last_meal_t);
	// printf("%ld LAST_MEAL_T - GET_TIME\n", current_t);
	if (current_t > philo->table->ttd)
		dead = TRUE;
	else
		dead = FALSE;
	return (dead);
}

void	*monitor_thread(void *data)
{
	t_philo	*table;
	int		i;

	table = (t_philo *)data;
	while (wait_philos(table) != TRUE)
		;
	while (!get_value(table->locks[STRUCT], &table->flag_stop))
	{
		// printf("MONOK\n");
		i = -1;
		while (++i < table->nb_philos && !get_value(table->locks[STRUCT],
				&table->flag_stop) && get_value(table->philos[i]->phi_mut,
				&table->philos[i]->ate) == HUNGRY)
		{
			if (is_dead(table->philos[i]) == TRUE)
			{
				printf("PHI [%d] DIED BC T - LM = %ld\n", table->philos[i]->id,
					get_time(MS) - table->philos[i]->last_meal_t);
				set_value(table->locks[STRUCT], &table->flag_stop, TRUE);
				print_state(table->philos[i], DEAD);
			}
		
		}//CHECKALLFULL?
	}
	return (NULL);
}
