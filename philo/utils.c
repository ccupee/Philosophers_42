/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spgibber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 19:50:08 by spgibber          #+#    #+#             */
/*   Updated: 2022/04/18 19:50:10 by spgibber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	else
		return (0);
}

static long long	ft_check_sign(char sign, size_t len, long long number)
{
	if (sign == '-' && len < 19)
		number = (int)(number * (-1));
	return (number);
}

static long long	ft_another_check_sign(long long number, char sign)
{
	if (sign == '-')
		number = 0;
	else
		number = -1;
	return (number);
}

int	ft_atoi(const char *str)
{
	unsigned long long		number;
	size_t					i;
	char					sign;
	size_t					len;

	number = 0;
	i = 0;
	len = 0;
	sign = '+';
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if ((str[i] == 45 || str[i] == 43) && ft_isdigit(str[i + 1]))
		sign = str[i++];
	while (ft_isdigit(str[i]))
	{
		number = number * 10 + (str[i++] - '0');
		len++;
	}
	if (len >= 19)
		number = ft_another_check_sign(number, sign);
	number = ft_check_sign(sign, len, number);
	return ((int)number);
}
