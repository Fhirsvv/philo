/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecortes- <ecortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 12:41:38 by ecortes-          #+#    #+#             */
/*   Updated: 2024/10/26 13:39:33 by ecortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

int	check_argvs(char **argv)
{
	if (!argv[1] || ft_atoi(argv[1]) > 200 || ft_atoi(argv[1]) <= 0)
		return (printf("Invalid philosophers number\n"));
	if (!argv[2] || ft_atoi(argv[2]) <= 0)
		return (printf("Invalid time to die\n"));
	if (!argv[3] || ft_atoi(argv[3]) <= 0)
		return (printf("Invalid time to eat\n"));
	if (!argv[4] || ft_atoi(argv[4]) <= 0)
		return (printf("Invalid time to sleep\n"));
	if (argv[5] && ft_atoi(argv[5]) < 0)
		return (printf("Invalid times must eat\n"));
	return (0);
}

void	*safe_malloc(size_t bytes)
{
	void	*ret;

	ret = malloc(bytes);
	if (!ret)
		printf("Error in malloc");
	return (ret);
}

int	ft_atoi(char *str)
{
	unsigned long	result;
	int				sign;

	sign = 1;
	result = 0;
	while ((*str == ' ' || ('\t' <= *str && *str <= '\r')))
		str++;
	if (*str == '-')
	{
		sign = -sign;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		if (result > LONG_MAX && sign > 0)
			return (-1);
		if (result > LONG_MAX && sign < 0)
			return (0);
		str++;
	}
	return (result * sign);
}

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		printf("gettimeofday() error\n");
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_usleep(size_t time)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < time)
		usleep(time / 10);
	return (0);
}
