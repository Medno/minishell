/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_maths.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 10:59:23 by pchadeni          #+#    #+#             */
/*   Updated: 2018/01/23 13:33:59 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

uint8_t	ft_expten(int n)
{
	if (n >= 1000000000)
		return (10);
	else if (n >= 100000000)
		return (9);
	else if (n >= 10000000)
		return (8);
	else if (n >= 1000000)
		return (7);
	else if (n >= 100000)
		return (6);
	else if (n >= 10000)
		return (5);
	else if (n >= 1000)
		return (4);
	else if (n >= 100)
		return (3);
	else if (n >= 10)
		return (2);
	else if (n > 0)
		return (1);
	return (0);
}

int		ft_pow(int n, int pow)
{
	if (pow < 0)
		return (0);
	if (pow == 0)
		return (1);
	if (pow > 1)
		return (n * ft_pow(n, pow - 1));
	return (n);
}

int		ft_sqrt(int nb)
{
	int	i;

	i = 1;
	if (nb <= 0)
		return (0);
	while (i * i <= nb && i * i)
	{
		if (i * i == nb)
			return (i);
		i++;
	}
	return (0);
}
