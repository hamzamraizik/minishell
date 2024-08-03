#include "minishell.h"

char *expand_variable(const char *str, int *index)
{
	char	*result = NULL;
	int		Name_length = 0;
	int		var_len = 0;
	char	*name;
	int		i;

	i = *index;
	while (str[i] && str[i] != ' ' && (isalnum(str[i]) || str[i] == '_'))
	{
		Name_length++;
		i++;
	}
	name = malloc(Name_length + 1);
	while (str[*index] && str[*index] != ' ' && str[*index] != '"' && (isalnum(str[*index]) || str[*index] == '_'))
	{
		name[var_len] = str[*index];
		var_len++;
		(*index)++;
	}
	name[var_len] = '\0';
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

	while (str[*index] && str[*index] != '"')
	{
		// if (special_vars(&result, &str, &start, index))
		// 	continue;
		if (str[*index] == '$' && str[*index + 1] && !isnum(str[*index + 1]))
		{
			tmp = strndup(str + start, *index - start);
			result = ft_strjoin(result, tmp);
			free(tmp);
			(*index)++;
			// Expand variable inside double quotes
			tmp = expand_variable(str, index);
			printf("____%s_____\n", tmp);
			result = ft_strjoin(result, tmp);
			free(tmp);
			start = *index;
		}
		tmp = strndup(str + start, (*index - start));
		result = ft_strjoin(result, tmp);
		free(tmp);
		start = (*index);
		(*index)++;
	}
	return (result);
}

char *handle_single_quotes(const char *str, int *index)
{
	char *result = strdup("");
	int start = *index;

	// (*index)++; // Skip the initial single quote

	while (str[*index] && str[*index] != '\'')
	{
		(*index)++;
	}

	result = strndup(str + start, *index - start);

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
		is_quotes = check_quotes(is_quotes, word[i]);
		if (word[i] == '\'' &&  is_quotes == 1)
		{
			tmp = strndup(word + start, i - start);
			result = ft_strjoin(result, tmp);
			free(tmp);
			start = ++i;
			while (word[i] != '\'')
				i++;
			tmp = strndup(word + start, i - start);
			result = ft_strjoin(result, tmp);
			free(tmp);
			is_quotes = 0;
			start = i + 1;
		}
		else if (word[i] == '"' && is_quotes == 2)
		{
			tmp = strndup(word + start, i - start);
			result = ft_strjoin(result, tmp);
			free(tmp);

			++i;// skip the first quotes
			tmp = handle_double_quotes(word, &i);
			result = ft_strjoin(result, tmp);
			free(tmp);
			is_quotes = check_quotes(is_quotes, word[i]);
			start = i + 1;
		}
		if (word[i] == '$' && is_quotes == 0)
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
