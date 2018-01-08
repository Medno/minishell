/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstemp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/06 11:04:35 by pchadeni          #+#    #+#             */
/*   Updated: 2018/01/06 11:05:10 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclean(void *str, size_t size)
{
	char	*tmp;

	tmp = (char *)str;
	ft_strdel(&tmp);
	size = 0;
}