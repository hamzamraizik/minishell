# include "minishell.h"
void expand(char **s)
{
	char *tmp = *s;
	if (strcmp(*s, "HOME") == 0)
	{
		*s = strdup("/home/mizoo");
	}
	else if (strcmp(*s, "USER") == 0)
		*s = strdup("mizoo");
	else
		return ;
	free(tmp);
	return ;
	// exit(1);
}

char	*no_q_var(char **word, int i, int is_q)
{
	int		start;
	char	*result;
	char	*s;

	start = 0;
	s = strdup("");
	char space[2] = {' ', '\0'};
	result = strdup("");
	start = ++i;
	is_q = check_quotes(is_q, (*word)[i]);
	while (!is_q && (*word)[i + 1] != '\0' && (*word)[i + 1] != ' ' && (*word)[i + 1] != '$')
	{
		++i;
		is_q = check_quotes(is_q, (*word)[i + 1]);
	}
	s = strndup((*word) + start, i - start + 1);
	expand(&s);
	result = ft_strjoin(result, s);
	result = ft_strjoin(result, space);
	return (result);
}

char *var_with_d_q(char **word, int i, int is_q)
{
	int		start;
	char	*result;
	char	*s;

	start = 0;
	s = strdup("");
	char space[2] = {' ', '\0'};
	result = strdup("");
	++i; // to skip the double quotes
	start = ++i; // skip $ symbol
	while (is_q == 2 && (*word)[i + 1] && (*word)[i + 1] != ' ' && (*word)[i + 1] != '$' && (*word)[i + 1] != '\"')
	{
		is_q = check_quotes(is_q, (*word)[i]);
		i++;
	}
	s = strndup((*word) + start, i - start + 1);
	expand(&s);
	result = ft_strjoin(result, s);
	result = ft_strjoin(result, space);
	return (result);
}

char	*not_var(char **word, int i, int is_q, char *result)
{
	int		start;
	char	*s;

	start = 0;
	s = strdup("");
	char space[2] = {' ', '\0'};
	result = strdup("");
	start = ++i;// to skip the single quotes
	while (is_q == 1 && (*word)[i + 1] && (*word)[i + 1] != '\0' && (*word)[i + 1] != '\'')
	{
		is_q = check_quotes(is_q, (*word)[i]);
		i++;
	}
	s = strndup((*word) + start, i - start + 1);
	// expand(&s);
	result = ft_strjoin(result, s);
	result = ft_strjoin(result, space);
	return (result);
}

char	*var_expand(char **word)
{
	int		is_quotes;
	char	*result;
	int		i;
	int		start;

	i = is_quotes = start = 0;
	if (!word || !*word)
		return NULL;
	result = strdup("");
	while ((*word)[i])
	{
		is_quotes = check_quotes(is_quotes, (*word)[i]);
		if (is_quotes == 0 && (*word)[i] && (*word)[i] == '$' && (*word)[i + 1])
			result = ft_strjoin(result, no_q_var(word, i, is_quotes));
		else if (is_quotes == 2 && (*word)[i + 1] && (*word)[i + 1] == '$' && (*word)[i + 2] && (*word)[i + 2] != '\"')
			result = ft_strjoin(result, var_with_d_q(word, i, is_quotes));
		else if (is_quotes == 1 && (*word)[i + 1] && (*word)[i + 1] == '$' && (*word)[i + 2] && (*word)[i + 2] != '\'')
		{
			result = ft_strjoin(result, not_var(word, i, is_quotes, result));
			while ( (*word)[i] && (*word)[i + 1] && (*word)[i + 1] != '\'')
				i++;
		}
		i++;
	}
		if (result[0] == '\0')
			result = *word;
	return (result);
}

void	expanding(t_list **head)
{
	// int		i;
	t_list	*tmp;
	char	*tmp2;

	// i = 0;
	if (head == NULL || !*head)
		return ;
	tmp = *head;
	while (tmp)
	{
		if (tmp->content && tmp->type == WORD && ft_strchr(tmp->content, '$'))
		{
			tmp2 = tmp->content;
			tmp->content = var_expand(&tmp->content);
			free(tmp2);
		}
		tmp = tmp->next;
	}
}
