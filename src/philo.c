/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgoldenb <sgoldenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 20:44:07 by sgoldenb          #+#    #+#             */
/*   Updated: 2024/04/18 21:39:21 by sgoldenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

t_bool	check_args(char **args, int nb_args)
{
	size_t	intlen;
	size_t	arg_len;

	intlen = 0;
	while (--nb_args > 0)
	{
		arg_len = ft_strlen(args[nb_args]);
		ft_intlen(ft_atoi(args[nb_args]), &intlen);
		if (intlen != arg_len)
			return (FALSE);
		else
			while (arg_len -- > 0)
				if (ft_isdigit(args[nb_args][arg_len]) == 0)
					return (FALSE);
		intlen = 0;
		arg_len = 0;
	}
	return (TRUE);
}

t_args	*save_args(char	**args, int nb_args)
{
	t_args *var;

	var = (t_args *)malloc(sizeof(t_args));
	if (!var)
		exit(errno);
	var->nb_philo = ft_atoi(args[1]);
	var->ttd = ft_atoi(args[2]);
	var->tte = ft_atoi(args[3]);
	var->tts = ft_atoi(args[4]);
	if (nb_args == 6)
		var->total_meals = ft_atoi(args[5]);
	else
		var->total_meals = ENDLESS;
	return (var);
}

int	usage(void)
{
	ft_printf(YELLOW ITALIC"./philo [nb_philos] [ttd] [tte] [tts] (total_meals)"
		RESET);
	return (1);
}

int	main(int argc, char **argv)
{
	t_args	*args_struct;

	if (argc < 5 || argc > 6 || check_args(argv, argc) == FALSE)
		return (usage());
	args_struct = save_args(argv, argc);
	return (0);
}

