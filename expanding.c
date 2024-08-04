#include "minishell.h"

char *expand_variable(const char *str, int *index) {
	char *result;
	int Name_length;
	int var_len;
	char *name;
	int i = *index;

	Name_length = var_len = 0;
	result = NULL;
	while (str[i] && str[i] != ' ' && (isalnum(str[i]) || str[i] == '_')) {
		Name_length++;
		i++;
	}
	name = malloc(Name_length + 1);
	if (!name)
		return (printf("malloc failed!\n"), NULL);
	while (str[*index] && str[*index] != ' ' && str[*index] != '"' 
			&& (isalnum(str[*index]) || str[*index] == '_'))
	{
		name[var_len] = str[*index];
		var_len++;
		(*index)++;
	}
	name[var_len] = '\0';
	result = is_var(ft_envp, name);
	free(name);
	if (!result)
		return (strdup(""));
	return (result);
}

int special_vars(char **result, const char **str, int *start, int *index)
{
	char	*tmp;
	int		flag = 0;

	if ((*str)[*index] == '$' && (*str)[*index + 1] == '0')
	{
		flag = 1;
		tmp = strndup((*str) + (*start), (*index) - (*start));
		*result = ft_strjoin(*result, tmp);
		free(tmp);
		*result = ft_strjoin(*result, "bash");
		(*index)++; //skip the symbol '$'
		(*start) = (*index) + 1; // ++1 for start after '0'
	}
	else if ((*str)[*index] == '$' && (*str)[*index + 1] && isnum((*str)[*index + 1]))
	{
		flag = 2;
		tmp = strndup((*str) + (*start), *index - (*start));
		*result = ft_strjoin(*result, tmp);
		free(tmp);
		(*index)++;
		(*start) = (*index) + 1;
	}
	return (flag);
}

char *handle_double_quotes(const char *str, int *index) {
	char *result = strdup("");
	char *tmp;
	int start = *index;

	while (str[*index] && str[*index] != '"')
	{
		if (special_vars(&result, &str, &start, index))
		{
			(*index)++;
			continue;
		}
		if (str[*index] == '$' && str[*index + 1] && !isnum(str[*index + 1]))
		{
			tmp = strndup(str + start, *index - start);
			result = ft_strjoin(result, tmp);
			free(tmp);
			(*index)++;
			tmp = expand_variable(str, index);
			result = ft_strjoin(result, tmp);
			free(tmp);
			start = *index;
		}
		else
			(*index)++;
	}
	tmp = strndup(str + start, *index - start);
	result = ft_strjoin(result, tmp);
	free(tmp);
	(*index)++; // Skip the closing double quote
	return (result);
}

char *handle_single_quotes(const char *str, int *index)
{
	char *result = strdup("");
	int start = *index;

	while (str[*index] && str[*index] != '\'')
	{
		(*index)++;
	}

	result = strndup(str + start, *index - start);
	(*index)++; // Skip the closing single quote
	return result;
}

char *var_expand(const char *word) {
	char *result = strdup("");
	char *tmp;
	int i = 0, start = 0;

	while (word[i])
	{
		if (word[i] == '\'') {
			tmp = strndup(word + start, i - start);
			result = ft_strjoin(result, tmp);
			free(tmp);
			start = ++i;
			tmp = handle_single_quotes(word, &i);
			result = ft_strjoin(result, tmp);
			free(tmp);
			start = i;
		} else if (word[i] == '"') {
			tmp = strndup(word + start, i - start);
			result = ft_strjoin(result, tmp);
			free(tmp);
			start = ++i;
			tmp = handle_double_quotes(word, &i);
			result = ft_strjoin(result, tmp);
			free(tmp);
			start = i;
		}
		else if (word[i] == '$')
		{
			if (special_vars(&result, &word, &start, &i) != 0)
			{
				i++;
				continue;
			}
			tmp = strndup(word + start, i - start);
			result = ft_strjoin(result, tmp);
			free(tmp);
			i++;
			tmp = expand_variable(word, &i);
			result = ft_strjoin(result, tmp);
			free(tmp);
			start = i;
		}
		else
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
