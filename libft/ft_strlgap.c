/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlgap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 16:32:54 by pchadeni          #+#    #+#             */
/*   Updated: 2018/01/18 17:05:57 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strlgap(char *str, char delim, int pos)
{
	int		i;
	int		j;
	char	*s;

	i = 0;
	j = 0;
	s = str;
	while (s[i] && j < pos)
	{
		if (s[i] == delim)
		{
			j++;
			if (j == pos)
				return (ft_strsub(s, 0, i));
		}
		i++;
	}
	return ((pos - 1 == ft_nbchar(str, delim)) ? ft_strsub(s, 0, i) : NULL);
}
