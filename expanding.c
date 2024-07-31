#include "minishell.h"

char *expand_variable(const char *str, int *index)
{
	char	*result = NULL;
	int		Name_length = 0;
	int		var_len = 0;
	char	*name;
	int		i;

	i = *index;
	while (str[i] && (isalnum(str[i]) || str[i] == '_'))
	{
		Name_length++;
		i++;
	}
	name = malloc(Name_length + 1);
	while (str[*index] && (isalnum(str[*index]) || str[*index] == '_'))
	{
		name[var_len] = str[*index];
		var_len++;
		(*index)++;
	}
	name[var_len] = '\0';
	(*index)--; //because i was incremented one more, in the loop.

	result = is_var(ft_envp, name);
	return (result);
}

int	special_vars(char **result, const char **str, int *start, int *index)
{
	char	*tmp;
	int		flag;

	flag = 0;
	if ((*str)[*index] == '$' && (*str)[*index + 1] == '0')
	{
		flag = 1;
		tmp = strndup((*str) + (*start), *index - (*start));
		*result = ft_strjoin(*result, tmp);
		free(tmp);
		*result = ft_strjoin(*result, "bash");
		(*index)++; //skip the symbol '$'
		(*start) = (*index) + 1; // ++1 for start after '0'
	}
	if ((*str)[*index] == '$' && (*str)[*index + 1] && isnum((*str)[*index + 1]))
	{
		flag = 2;
		tmp = strndup((*str) + (*start), *index - (*start));
		*result = ft_strjoin(*result, tmp);
		free(tmp);
		(*index)++;
		(*start) = (*index) + 1;
	}
	else
		return(flag);
	return (flag);
}

char *handle_double_quotes(const char *str, int *index)
{
	char *result = strdup("");
	char *tmp;
	int start = *index;

	(*index)++; // for the first double quote

	while (str[*index] && str[*index] != '"')
	{
		if (special_vars(&result, &str, &start, index))
			continue;
		if (str[*index] == '$' && str[*index + 1] && !isnum(str[*index + 1]))
		{
			tmp = strndup(str + start, *index - start);
			result = ft_strjoin(result, tmp);
			free(tmp);
			(*index)++;
			// Expand variable inside double quotes
			tmp = expand_variable(str, index);
			result = ft_strjoin(result, tmp);
			free(tmp);

			start = *index + 1; // +1 for start being equal to index after incremented in the loop
		}
		(*index)++;
	}
	(*index)++; // for skip the closing double quote
	tmp = strndup(str + start, *index - start - 1);
	result = ft_strjoin(result, tmp);
	free(tmp);
	return (result);
}

char *handle_single_quotes(const char *str, int *index)
{
	char *result = strdup("");
	int start = *index;

	(*index)++; // Skip the initial single quote

	while (str[*index] && str[*index] != '\'')
	{
		(*index)++;
	}

	result = strndup(str + start + 1, *index - start - 1);

	// (*index)++; // Skip the closing single quote

	return result;
}

char *var_expand(const char *word)
{
	char *result = strdup("");
	char *tmp;
	int i = 0, start = 0, is_quotes = 0;

	while (word[i])
	{
	
		if (word[i] == '\'' &&  is_quotes != 1)
		{
			tmp = strndup(word + start, i - start);
			result = ft_strjoin(result, tmp);
			free(tmp);

			tmp = handle_single_quotes(word, &i);
			result = ft_strjoin(result, tmp);
			free(tmp);
			start = i+1;
		}
		else if (word[i] == '"')
		{
			tmp = strndup(word + start, i - start);
			result = ft_strjoin(result, tmp);
			free(tmp);

			tmp = handle_double_quotes(word, &i);
			result = ft_strjoin(result, tmp + 1);
			free(tmp);

			start = i;
		}
		else if (word[i] == '$')
		{
			if (special_vars(&result, &word, &start, &i) != 0)
				continue;
			tmp = strndup(word + start, i - start);
			result = ft_strjoin(result, tmp);
			free(tmp);
			i++;
			tmp = expand_variable(word, &i);
			result = ft_strjoin(result, tmp);
			free(tmp);
			start = i + 1;
		}
		is_quotes = check_quotes(is_quotes, word[i]);
		i++;
	}
	tmp = strndup(word + start, i - start);
	result = ft_strjoin(result, tmp);
	free(tmp);
	return (result);
}

void expanding(t_list **head)
{
	t_list	*tmp;
	char	*tmp2;

	if (head == NULL || !*head)
		return;
	tmp = *head;
	while (tmp)
	{
		if (tmp->content && tmp->type == WORD && ft_strchr(tmp->content, '$')
			&& *(ft_strchr(tmp->content, '$') + 1)
				&& isalnum(*(ft_strchr(tmp->content, '$') + 1)))
		{
			// printf("__________????\n");
			tmp2 = tmp->content;
			tmp->content = var_expand(tmp->content);
			free(tmp2);
		}
		tmp = tmp->next;
	}
}
