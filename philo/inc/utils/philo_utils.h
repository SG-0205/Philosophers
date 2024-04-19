/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgoldenb <sgoldenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 09:20:01 by sgoldenb          #+#    #+#             */
/*   Updated: 2024/04/19 12:55:31 by sgoldenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_UTILS_H
# define PHILO_UTILS_H

# include <errno.h>
# include <stdarg.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define TRUE 1
# define FALSE 0
# define ERROR 2

# define RESET "\e[0m"
# define BOLD "\e[1m"
# define FAINT "\e[2m"
# define ITALIC "\e[3m"
# define UNDERLINE "\e[4m"
# define BLINK "\e[5m"
# define INVERSE "\e[7m"
# define HIDDEN "\e[8m"
# define STRIKETHROUGH "\e[9m"
# define RESET_BOLD "\e[21m"
# define RESET_FAINT "\e[22m"
# define RESET_ITALIC "\e[23m"
# define RESET_UNDERLINE "\e[24m"
# define RESET_BLINK "\e[25m"
# define RESET_INVERSE "\e[27m"
# define RESET_HIDDEN "\e[28m"
# define RESET_STRIKETHROUGH "\e[29m"

# define BLACK "\e[30m"
# define RED "\e[31m"
# define GREEN "\e[32m"
# define YELLOW "\e[33m"
# define BLUE "\e[34m"
# define MAGENTA "\e[35m"
# define CYAN "\e[36m"
# define WHITE "\e[37m"
# define LIGHT_BLACK "\e[90m"
# define LIGHT_RED "\e[91m"
# define LIGHT_GREEN "\e[92m"
# define LIGHT_YELLOW "\e[93m"
# define LIGHT_BLUE "\e[94m"
# define LIGHT_MAGENTA "\e[95m"
# define LIGHT_CYAN "\e[96m"
# define LIGHT_WHITE "\e[97m"

# define BG_BLACK "\e[40m"
# define BG_RED "\e[41m"
# define BG_GREEN "\e[42m"
# define BG_YELLOW "\e[43m"
# define BG_BLUE "\e[44m"
# define BG_MAGENTA "\e[45m"
# define BG_CYAN "\e[46m"
# define BG_WHITE "\e[47m"
# define BG_LIGHT_BLACK "\e[100m"
# define BG_LIGHT_RED "\e[101m"
# define BG_LIGHT_GREEN "\e[102m"
# define BG_LIGHT_YELLOW "\e[103m"
# define BG_LIGHT_BLUE "\e[104m"
# define BG_LIGHT_MAGENTA "\e[105m"
# define BG_LIGHT_CYAN "\e[106m"
# define BG_LIGHT_WHITE "\e[107m"

typedef int			t_bool;

void	ft_intlen(long int n, size_t *container);
int		ft_atoi(const char *nptr);
int		ft_isdigit(int c);
size_t	ft_strlen(const char *str);
void	ft_arrfree(void **array);
int		ft_arrlen(void **array);

//PRINTF
# define SPEC "csdiupxX%"
# define BASE_HEX_MIN "0123456789abcdef"
# define BASE_HEX_MAJ "0123456789ABCDEF"
# define BASE_TEN "0123456789"

void				ft_putunsigned(unsigned long long nbr, const char *base,
						int *len);
void				ft_putnbr_base_f(int nbr, const char *base, int *len);
void				ft_printpointer(unsigned long long pointer,
						const char *base, int *len);
void				ft_putchar_f(char c, int *len);
void				ft_putstr_f(const char *str, int *len);
int					ft_printf(const char *format, ...);

#endif