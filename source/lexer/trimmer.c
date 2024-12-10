/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trimmer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmitz <eschmitz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 18:58:09 by eschmitz          #+#    #+#             */
/*   Updated: 2024/12/09 12:03:16 by eschmitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static char	*ft_strndup(const char *s1, int len)
// {
// 	char	*result;
// 	int		i;

//     if (!s1)
//         return (NULL);
//     if (len > (int)ft_strlen(s1))
//         len = ft_strlen(s1);
// 	result = malloc((len + 1) * sizeof(char));
// 	if (!result)
// 		return (NULL);
// 	i = 0;
// 	while (i < len)
// 	{
// 		result[i] = s1[i];
// 		i++;
// 	}
// 	result[i] = '\0';
// 	return (result);
// }

// static char *trim_quotes(char *str, bool *in_single_quotes, bool *in_double_quotes, int *c)
// {
//     int i;
//     int j;
//     char    *result;
    
//     i = 0;
//     j = 0;
//     result = malloc((ft_strlen(str) + 1) * sizeof(char));
//     if (!result)
//         return (NULL);
//     while (str[i])
//     {
//         if (str[i] == '\'' && *in_double_quotes == 0)
//         {
//             if (!(*in_double_quotes))
//                 *in_single_quotes = 1;
//             else 
//                 *in_single_quotes = 0;
//         }
//         else if (str[i] == '\"' && *in_single_quotes == 0)
//         {
//             if (!(*in_double_quotes))
//                 *in_double_quotes = 1;
//             else
//                 *in_double_quotes = 0;
//         }
//         else 
//             result[j++] = str[i];
//         if (str[i] == '\'')
//             *c += 1;
//         i++;
//     }
//     result[j] = '\0';
//     return (result);
// }

// char *replace_env_vars(char *str, t_env **g_env, int *end_index) {
//     char    *new_str;
//     char    *env_value;
//     char    *var_name;
//     int     i;

//     i = 0;
//     if (!str[i] || !str[i + 1] || !(ft_isalnum(str[i + 1])))
//         return (NULL);
//     i++;
//     while (str[i] && (isalnum(str[i]) || str[i] == '_')) 
//         i++;
//     var_name = ft_strndup(&str[1], i - 1);
//     env_value = ft_getenv(var_name, g_env);
//     free(var_name);
//     if (!env_value)
//         new_str = ft_strdup("");
//     else 
//         new_str = ft_strdup(env_value);
//     *end_index = i;
//     return (new_str);
// }

// void trim_and_expand(t_token *tokens, t_shell *sh) {
//     char *str;
//     char *new_str;
//     int  i;
//     int  j;
//     int c;
//     int end_index;
//     bool in_single_quotes;
//     bool    in_double_quotes;

//     i = 0;
//     j = 0;
//     c = 0;
//     in_single_quotes = 0;
//     in_double_quotes = 0;
//     while (tokens) 
//     {
//         str = (char *)tokens->content;
//         str = trim_quotes(str, &in_single_quotes, &in_double_quotes, &c);
//         new_str = malloc(1024 * sizeof(char));
//         if (!new_str)
//             return;
//         i = 0;
//         j = 0;
//          while (str[i])
//          {
//             if (str[i] == '$' && str[i + 1] && (!(in_single_quotes) || c == 0))
//             {
//                 if (str[i + 1] == '?')
//                 {
//                     char    *exitcode_str = ft_itoa(sh->exit_status);
//                     // strncpy(&new_str[j], sh->exit_status, ft_strlen(sh->exit_status));
//                     // j += ft_strlen(sh->exit_status);
//                     // free(sh->exit_status);
//                     i++;
//                 }
//                 else 
//                 {
//                     char *expanded = replace_env_vars(&str[i], &sh->env, &end_index);
//                     strncpy(&new_str[j], expanded, ft_strlen(expanded));
//                     j += ft_strlen(expanded);
//                     free(expanded);
//                     i += end_index - 1;  
//                 }
//             } 
//             else
//                 new_str[j++] = str[i];
//             i++;
//         }
//         new_str[j] = '\0';
//         free(tokens->content);
//         tokens->content = new_str;
//         tokens = tokens->next;
//     }  
// }
