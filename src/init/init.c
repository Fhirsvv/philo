/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecortes- <ecortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 12:43:42 by ecortes-          #+#    #+#             */
/*   Updated: 2025/01/26 11:13:05 by ecortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

static void	philos_init(t_program *pr)
{
	size_t	i;

	i = -1;
	while (++i < pr->nb_philos)
	{
		pr->philos[i].nb_philos = &pr->nb_philos;
		pr->philos[i].time_die = &pr->time_die;
		pr->philos[i].time_eat = &pr->time_eat;
		pr->philos[i].time_sleep = &pr->time_sleep;
		pr->philos[i].max_meals = &pr->max_meals;
		pr->philos[i].write_lock = &pr->write_lock;
		pr->philos[i].dead_lock = &pr->dead_lock;
		pr->philos[i].meals_lock = &pr->meals_lock;
		pr->philos[i].dead_flag = &pr->dead_flag;
		pr->philos[i].current_meals = 0;
		pr->philos[i].id = i + 1;
		pr->philos[i].start_time = get_current_time();
		pr->philos[i].time_lmeal = 0;
		pr->philos[i].left_fork = &pr->forks[i];
		if (i == 0)
			pr->philos[i].right_fork = &pr->forks[pr->nb_philos - 1];
		else
			pr->philos[i].right_fork = &pr->forks[i - 1];
	}
}

static void	mutex_init(t_program *pr)
{
	size_t	i;

	i = -1;
	while (++i < pr->nb_philos)
	{
		pthread_mutex_init(&(pr->forks[i]), NULL);
	}
	pthread_mutex_init(&pr->dead_lock, NULL);
	pthread_mutex_init(&pr->meals_lock, NULL);
	pthread_mutex_init(&pr->write_lock, NULL);
}

static void	program_init(t_program *pr, char **argv)
{
	pr->nb_philos = ft_atoi(argv[1]);
	pr->time_die = ft_atoi(argv[2]);
	pr->time_eat = ft_atoi(argv[3]);
	pr->time_sleep = ft_atoi(argv[4]);
	pr->max_meals = -1;
	pr->dead_flag = 0;
	if (argv[5])
		pr->max_meals = ft_atoi(argv[5]);
	pr->philos = (t_philos *)safe_malloc(sizeof(t_philos) * pr->nb_philos);
	pr->forks = (pthread_mutex_t *)safe_malloc(sizeof(pthread_mutex_t)
			* pr->nb_philos);
}

void	init(t_program *pr, char **argv)
{
	program_init(pr, argv);
	mutex_init(pr);
	philos_init(pr);
}
