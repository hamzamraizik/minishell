# include "minishell.h"
void expand(char *s)
{
	printf("%s", s);
	exit(1);
}

void var_expand(char **word)
{
    int		is_quotes;
	char	*s;
    int		i;

    i = is_quotes = 0;
	s = strdup("");
    while ((*word)[i])
    {
        is_quotes = check_quotes(is_quotes, (*word)[i]);
        if (is_quotes == 0 && (*word)[i] && (*word)[i] == '$')
        {
            ++i;
            while (!is_quotes && (*word)[i + 1] != '\0' && (*word)[i + 1] != ' ')
            {
                is_quotes = check_quotes(is_quotes, (*word)[i]);
				s = ft_strjoin(s, &(*word)[i]);
                i++;
            }
            expand(s);
        }
        i++;
    }
}

void expanding(t_list **head)
{
	int	i;
	t_list *tmp;

	i = 0;
	tmp = *head;
	while (tmp)
	{
		if (tmp->type == WORD && ft_strchr(tmp->content, '$'))
			var_expand(&(tmp->content));
		tmp = tmp->next;
	}
}
