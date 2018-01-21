/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 14:48:29 by pchadeni          #+#    #+#             */
/*   Updated: 2018/01/19 12:57:46 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list			*ft_lstsplit(char const *s, char c)
{
	t_list	*lst;
	size_t	i;
	size_t	len;
	char	*tmp;

	i = 0;
	len = 0;
	lst = NULL;
	if (s && c)
		while (s[i])
		{
			if (s[i] != c && s[i + 1])
			{
				len = 0;
				while (s[i + len] != c && s[i + len])
					len++;
				tmp = ft_strsub(s, i, len);
				ft_lstaddlast(&lst, ft_lstnew(tmp, len));
				ft_strdel(&tmp);
				i += len;
			}
			i = (s[i]) ? i + 1 : i;
		}
	return (lst);
}
