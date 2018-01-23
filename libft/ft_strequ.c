/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strequ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 18:48:40 by pchadeni          #+#    #+#             */
/*   Updated: 2018/01/23 13:06:17 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strequ(char const *s1, char const *s2)
{
	const char	*tmp_s1;
	const char	*tmp_s2;

	tmp_s1 = s1;
	tmp_s2 = s2;
	if (s1 && s2)
	{
		if (!ft_strcmp(tmp_s1, tmp_s2))
			return (1);
	}
	return (0);
}

int	ft_strnequ(char const *s1, char const *s2, size_t n)
{
	if (!s1 && !s2)
		return (0);
	if (s1 && s2)
		if (!ft_strncmp(s1, s2, n))
			return (1);
	return (0);
}
