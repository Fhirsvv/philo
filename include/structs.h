/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecortes- <ecortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 12:10:43 by ecortes-          #+#    #+#             */
/*   Updated: 2024/10/30 15:46:18 by ecortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <pthread.h>
# include <stdlib.h>
# include <stdint.h>

typedef struct s_philos
{
	uint16_t		id;
	int				*dead_flag;
	uint16_t		*nb_philos;
	size_t			*time_die;
	size_t			*time_eat;
	size_t			*time_sleep;
	size_t			*max_meals;
	size_t			current_meals;
	size_t			start_time;
	size_t			time_lmeal;

	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;

	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meals_lock;

	pthread_t		thread;
}	t_philos;

typedef struct s_program
{
	uint16_t		nb_philos;
	int				dead_flag;
	size_t			time_die;
	size_t			time_eat;
	size_t			time_sleep;
	size_t			max_meals;
	size_t			how_many_finshed;

	pthread_mutex_t	write_lock;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meals_lock;

	t_philos		*philos;
	pthread_mutex_t	*forks;
}	t_program;

#endif