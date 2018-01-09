/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minish.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 15:06:46 by pchadeni          #+#    #+#             */
/*   Updated: 2018/01/09 13:38:59 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISH_H
# define MINISH_H

# define PROMPT "$> "
# include "./libft/libft.h"

typedef struct	s_line
{
	char			*var;
	char			*value;
	struct s_line	*next;
}				t_line;

t_line			*init_file(void);
t_line			*fill_line(char **env);
void			line_pushback(t_line **first, t_line *add);

#endif
