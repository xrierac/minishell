/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   admin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xriera-c <xriera-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 10:46:29 by xriera-c          #+#    #+#             */
/*   Updated: 2024/04/26 17:23:33 by xriera-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void check_token(t_lex **lex_arr, t_env *env)
{
    if (lex_arr[0]->token == R_INPUT)
    if (lex_arr->token == R_OUTPUT)
    if (lex_arr->token == HEREDOC)
    if (lex_arr->token == APPEND)
    if (lex_arr->token == ENV)
    if (lex_arr->token == STATUS)
    if (lex_arr->token == OUTFILE)
    if (lex_arr->token == CMD)

    if (lex_arr->token == ARG)
    if (lex_arr->token == FLAG)
}

void    admin(t_lex **lex_arr, t_env *env)
{
    int i;

    i = 0;
    while (lex_arr[i])
    {
        check_token(lex_arr[i], env);
        i++;
    }
}