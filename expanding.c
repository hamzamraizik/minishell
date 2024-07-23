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
	// exit(1);
}

char	*var_expand(char **word)
{
	int		is_quotes;
	char	*s;
	char	*result;
	int		i;
	int		start;

	i = is_quotes = start = 0;
	s = strdup("");
	char space[2] = {' ', '\0'};
	result = strdup("");
	if (!word || !*word)
		return NULL;
	while ((*word)[i])
	{
		is_quotes = check_quotes(is_quotes, (*word)[i]);
		if (is_quotes == 0 && (*word)[i] && (*word)[i] == '$')
		{
			start = ++i;
			while (!is_quotes && (*word)[i + 1] != '\0' && (*word)[i + 1] != ' ' && (*word)[i + 1] != '$')
				i++;
			s = strndup((*word) + start, i - start + 1);
			expand(&s);
			result = ft_strjoin(result, s);
			result = ft_strjoin(result, space);
		}
		i++;
	}
	printf("%s\n", result);
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
			// printf("!!!!!");
			// exit(1);
		tmp = tmp->next;
	}
}
