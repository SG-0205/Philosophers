/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgoldenb <sgoldenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 20:38:06 by sgoldenb          #+#    #+#             */
/*   Updated: 2024/04/18 21:12:49 by sgoldenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "libft/libft.h"

# define ENDLESS -1

typedef struct s_strart_values
{
	int	nb_philo;
	int	ttd;
	int	tte;
	int	tts;
	int	total_meals;
}		t_args;

#endif