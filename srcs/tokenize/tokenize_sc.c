/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Zyeoh <yeohzishen2002@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 08:16:58 by Zyeoh             #+#    #+#             */
/*   Updated: 2024/04/23 08:16:58 by Zyeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int count_redir(char *line)
{
    int count_redir;

    count_redir = 0;
    while (*line)
    {
        
    }

}


static int is_valid(char c)
{
    if (ft_isprint(c) && c != '>' && c != '<' && c != '|')
        return (1);
    return (0);
}

char *get_token_cmd(char *line)
{
    char *cmd;
    int n; 

    n = 0;
    while (line[n] && is_valid(line[n]))
        n++;
    cmd = ft_substr(line, 0, n);
    if (!cmd)
        perror_and_exit("Failed to allocate cmd token ", 125);
    return (cmd);
}

t_redir *get_token_redir(char *line)
{
    t_redir *redir;


}

t_node *tokenize_simple_command(char *line)
{
    char    *cmd;
    t_redir *redir;

    if (!line)
        return (NULL);
    cmd = get_token_cmd(line);
    while (*line && is_valid(*line))
        line++;
        
}
