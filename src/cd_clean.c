/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_clean.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 10:10:46 by pchadeni          #+#    #+#             */
/*   Updated: 2018/01/29 10:12:09 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minish.h"

uint8_t	slash_del(char **tab, int i)
{
	if ((tab[i + 1] && tab[i] && ft_strequ(tab[i + 1], "..") &&
				!ft_strequ(tab[i], "..")) || ft_strequ(tab[i], ".")
			|| ((!tab[i + 1] || (tab[i + 1] && ft_strequ(tab[i], "..")))
				&& ft_strequ(tab[i], "..")))
		return (1);
	return (0);
}

char	**clean_slash(char **slash, int j)
{
	char	**tmp;
	int		i;
	int		k;

	if (!(tmp = (char **)malloc(sizeof(char *) * j + 1)))
		return (NULL);
	i = 0;
	k = 0;
	while (slash[k])
	{
		if (!slash_del(slash, k))
		{
			tmp[i] = ft_strdup(slash[k]);
			i++;
		}
		k++;
	}
	tmp[i] = NULL;
	return (tmp);
}

void	clean_path(char **tmp)
{
	char	**epur;
	char	**slash;
	int		i;
	int		j;

	i = 0;
	j = 0;
	slash = ft_strsplit(*tmp, '/');
	while (slash && slash[i])
	{
		j = (!slash_del(slash, i)) ? j + 1 : j;
		i++;
	}
	ft_strdel(tmp);
	epur = clean_slash(slash, j);
	*tmp = ft_strdup("/");
	i = 0;
	while (epur && epur[i])
	{
		*tmp = ft_strjoinfree(*tmp, epur[i]);
		*tmp = (epur[i + 1]) ? ft_strjoinfree(*tmp, "/") : *tmp;
		i++;
	}
	ft_tabdel(slash);
	ft_tabdel(epur);
}
