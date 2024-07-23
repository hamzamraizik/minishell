# include "minishell.h"
void expand(char *s)
{
	(void)s;
	printf("hello there!!!!!!!!!!");
	// exit(1);
}

void var_expand(char **word)
{
	int		is_quotes;
	char	*s;
	int		i;
	int		start;

	i = is_quotes = start = 0;
	s = strdup("");
	if (!word || !*word)
		return ;
	while ((*word)[i])
	{
		is_quotes = check_quotes(is_quotes, (*word)[i]);
		if (is_quotes == 0 && (*word)[i] && (*word)[i] == '$')
		{
		// printf("!!!!!");
		// exit(1);
			start = ++i;
			while (!is_quotes && (*word)[i + 1] != '\0' && (*word)[i + 1] != ' ')
				i++;
			s = strndup((*word) + start, i - start + 1);
			// printf("!!!!!!!!!!\n%s\n", s);
			expand(s);
		}
		i++;
	} 
}

void	expanding(t_list **head)
{
	int		i;
	t_list	*tmp;

	i = 0;
	// if (head == NULL || !*head)
	// 	return ;
	// (void)head;
	tmp = *head;
	while (tmp)
	{
		if (tmp->content && tmp->type == WORD && ft_strchr(tmp->content, '$'))
			var_expand(&tmp->content);
			// printf("!!!!!");
			// exit(1);
		tmp = tmp->next;
	}
}
