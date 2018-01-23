/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_case.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 11:51:48 by pchadeni          #+#    #+#             */
/*   Updated: 2018/01/23 13:33:18 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_stolower(char *str)
{
	int		i;
	char	*tmp;

	i = ft_strlen(str);
	tmp = ft_strnew(i);
	while (i >= 0)
	{
		tmp[i] = ft_tolower(str[i]);
		i--;
	}
	return (tmp);
}

int		ft_tolower(int c)
{
	if (c >= 65 && c <= 90)
		return (c + 32);
	return (c);
}

int		ft_toupper(int c)
{
	if (c >= 97 && c <= 122)
		return (c - 32);
	return (c);
}
