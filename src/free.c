/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 13:18:28 by tcampbel          #+#    #+#             */
/*   Updated: 2024/05/06 15:16:34 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_all(t_sh *msh)
{
	if (msh->lex_arr != NULL)
	{
		free_lex(msh, msh->lex_arr);
		msh->lex_arr = NULL;
	}
	if (msh->env != NULL)
		free_env(msh->env);
	if (msh != NULL)
		free(msh);
}

void	free_lex(t_sh *msh, t_lex ***lex_arr)
{
	int	i;

	i = 0;
	while (msh->len--)
	{
		msh->tok_count = 0;
		is_token(msh, msh->pipe_arr[msh->len]);
		//printf("Len[%i]", msh->len);
		while (msh->tok_count--)
		{
			//if (lex_arr[msh->len][msh->tok_count]->cmd_arr != NULL)
				//ft_free_array(lex_arr[msh->len][msh->tok_count]->cmd_arr);
			free(lex_arr[msh->len][msh->tok_count]);
			//printf(" tok[%i]\n", msh->tok_count);
		}
		free(lex_arr[msh->len]);
		lex_arr[msh->len] = NULL;
	}
	free(lex_arr);
	lex_arr = NULL;
}

void	free_env(t_env *env)
{
	if (env->env_arr != NULL)
		ft_free_array(env->env_arr);
	if (env->env_path != NULL)
		free(env->env_path);
	if (env->path_arr != NULL)
		ft_free_array(env->path_arr);
	free(env);
}
