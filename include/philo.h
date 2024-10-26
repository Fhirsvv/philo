/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecortes- <ecortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 12:10:26 by ecortes-          #+#    #+#             */
/*   Updated: 2024/10/26 13:38:35 by ecortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdio.h>
# include <stdbool.h>
# include <sys/time.h>
# include <limits.h>
# include <errno.h>

# include "structs.h"

void	dead_write(t_philos *ph);
//---UTILS
int		ft_atoi(char *str);
int		check_argvs(char **argv);
void	*safe_malloc(size_t bytes);
size_t	get_current_time(void);
int		ft_usleep(size_t time);

//---INIT
void	init(t_program *pr, char **argv);

//---THREADS
void	threads(t_program *pr);
void	*routine(void *pr);
void	set_dead_flag(int i, t_philos *ph);
int		is_dead_flag(t_philos *ph);

//---FREE
void	free_program(t_program *pr);

#endif