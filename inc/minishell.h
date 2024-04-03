/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:58:52 by xriera-c          #+#    #+#             */
/*   Updated: 2024/04/03 15:31:33 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <readline.h>

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

typedef	enum	e_bool
{
	false,
	true
}	t_bool;

#endif
