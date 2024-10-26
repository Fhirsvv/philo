/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_program.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecortes- <ecortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 19:46:57 by ecortes-          #+#    #+#             */
/*   Updated: 2024/10/26 13:38:45 by ecortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

void	free_program(t_program *pr)
{
	size_t	i;

	i = -1;
	while (++i)
		pthread_mutex_destroy(&pr->forks[i]);
	pthread_mutex_destroy(&pr->write_lock);
	pthread_mutex_destroy(&pr->write_lock);
	pthread_mutex_destroy(&pr->meals_lock);
	if (pr->forks)
	{
		free(pr->forks);
		pr->forks = NULL;
	}
	if (pr->philos)
	{
		free(pr->philos);
		pr->philos = NULL;
	}
}
