#include "minishell.h"

// Dummy expand function for testing
void expand(char **s)
{
	char *tmp = *s;
	if (*s && strcmp(*s, "HOME") == 0)
	{
		*s = strdup("/home/mizoo");
	}
	else if (*s && strcmp(*s, "USER") == 0)
	{
		*s = strdup("mizoo");
	}
	else
	{
		*s = NULL;
		return;
	}
	free(tmp);
}

char *expand_variable(const char *str, int *index)
{
	char *result = NULL;
	char var_name[256];
	int var_len = 0;

	while (str[*index] && (isalnum(str[*index]) || str[*index] == '_'))
	{
		var_name[var_len++] = str[*index];
		(*index)++;
	}
	var_name[var_len] = '\0';
	(*index)--;

	result = is_var(ft_envp, var_name);
	// if (strcmp(var_name, "HOME") == 0)
	// 	result = strdup("/home/mizoo");
	// else if (strcmp(var_name, "USER") == 0)
	// 	result = strdup("mizoo");
	// else
	// 	result = strdup(""); // Handle undefined variables as empty string

	return result;
}

char *handle_double_quotes(const char *str, int *index)
{
	char *result = strdup("");
	char *tmp;
	int start = *index;

	(*index)++; // Skip the initial double quote

	while (str[*index] && str[*index] != '"')
	{
		if (str[*index] == '$')
		{
			// Expand variable inside double quotes
			tmp = strndup(str + start, *index - start);
			result = ft_strjoin(result, tmp);
			free(tmp);
			(*index)++;
			tmp = expand_variable(str, index);
			result = ft_strjoin(result, tmp);
			free(tmp);

			start = *index + 1;
		}
		(*index)++;
	}

	tmp = strndup(str + start, *index - start);
	result = ft_strjoin(result, tmp);
	free(tmp);

	(*index)++; // Skip the closing double quote

	return result;
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

	(*index)++; // Skip the closing single quote

	return result;
}

char *var_expand(const char *word)
{
	char *result = strdup("");
	char *tmp;
	int i = 0, start = 0;

	while (word[i])
	{
		if (word[i] == '\'')
		{
			tmp = strndup(word + start + 1, i - start);
			result = ft_strjoin(result, tmp);
			free(tmp);

			tmp = handle_single_quotes(word, &i);
			result = ft_strjoin(result, tmp);
			free(tmp);

			start = i;
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

	return result;
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
		if (tmp->content && tmp->type == WORD && ft_strchr(tmp->content, '$'))
		{
			tmp2 = tmp->content;
			tmp->content = var_expand(tmp->content);
			free(tmp2);
		}
		tmp = tmp->next;
	}
}
