/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 16:36:57 by pchadeni          #+#    #+#             */
/*   Updated: 2018/01/09 17:14:26 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_tabdup(char **tab)
{
	char	**tmp;
	int		size;

	if (!tab)
		return (NULL);
	size = 0;
	while (tab[size])
		size++;
	if (!(tmp = (char **)malloc(sizeof(char *) * size + 1)))
		return (NULL);
	tmp[size] = NULL;
	size--;
	while (size >= 0)
	{
		tmp[size] = ft_strdup(tab[size]);
		size--;
	}
	return (tmp);
}
