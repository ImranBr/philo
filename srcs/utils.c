/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibarbouc <ibarbouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 16:48:25 by ibarbouc          #+#    #+#             */
/*   Updated: 2025/09/14 01:07:23 by ibarbouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	ft_atol(const char *str)
{
	int		i;
	long	result;

	i = 0;
	result = 0;
	while ((str[i] == ' ') || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	result;

	i = 0;
	result = 0;
	while ((str[i] == ' ') || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result);
}

long	get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	print_action(t_philo *philo, char *action)
{
	long	timestamp;

	pthread_mutex_lock(&philo->data->print_lock);
	pthread_mutex_lock(&philo->data->stop_mutex);
	if (!philo->data->stop_dinner)
	{
		timestamp = get_time_in_ms() - philo->data->start_time;
		printf("%ld %d %s\n", timestamp, philo->id, action);
	}
	pthread_mutex_unlock(&philo->data->stop_mutex);
	pthread_mutex_unlock(&philo->data->print_lock);
}

void	ft_usleep(long ms)
{
	long	start;
	long	elapsed;
	long	remain;

	start = get_time_in_ms();
	while (1)
	{
		elapsed = get_time_in_ms() - start;
		if (elapsed >= ms)
			break;
		remain = ms - elapsed;
		if (remain > 1)
			usleep((remain > 1000) ? 1000 : remain);
	}
}
