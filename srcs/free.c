/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcampbel <tcampbel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 13:18:28 by tcampbel          #+#    #+#             */
/*   Updated: 2024/04/05 13:29:33 by tcampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_all(t_sh *msh)
{
	if (msh->lex != NULL)
		free_lex(msh->lex);
	if (msh->env != NULL)
		free_env(msh->env);
	if (msh != NULL)
		free(msh);
}

void	free_lex(t_lex *lex)
{
	if (lex->lex != NULL)
		ft_free_array(lex->lex);
	free(lex);
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