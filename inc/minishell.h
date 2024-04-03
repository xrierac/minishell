/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:34:27 by tcampbel          #+#    #+#             */
/*   Updated: 2024/04/03 16:27:03 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
//# include "../lib/libft/libft.h"

# define HGRN "\e[0;92m"
# define HBLK "\e[0;90m"
# define HRED "\e[0;91m"
# define reset "\e[0m"
typedef enum e_token_type
{
	S_QUOTE, //'
	D_QUOTE, //"
	R_INPUT, //<
	R_OUTPUT, //>
	HEREDOC, //<<
	APPEND, //>>
	PIPE, //|
	ENV, //$
	STATUS, //$?
	CMD,
	ARG
}	t_token_type;

typedef enum	e_bool
{
	false,
	true
}	t_bool;

typedef struct s_lex
{
	t_token_type	token;
	char			**lex;
}	t_lex;

void	get_input();
#endif
