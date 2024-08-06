#include "minishell.h"
 /*this func when will the var expanded, replaced with it
 	real value in the env if it exist, if not exist
		then it will replaced by '\0'*/
char *expand_variable(const char *str, int *index)
{
	char *result;
	int Name_length;
	int var_len;
	char *name;
	int i = *index;

	Name_length = var_len = 0;
	result = NULL;
	while (str[i] && str[i] != ' ' && (isalnum(str[i]) || str[i] == '_'))
	{
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
	name = getenv(name);
	if (name)
		result = strdup(name);
	else
		result = strdup("");
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
	else if ((*str)[*index] == '$' && (*str)[*index + 1] == '-')
	{
		flag = 1;
		tmp = strndup((*str) + (*start), (*index) - (*start));
		*result = ft_strjoin(*result, tmp);
		free(tmp);
		*result = ft_strjoin(*result, "himBHs");
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
/*this func will handle the double quotes when there is an var inside it
	by cancatenate while inside quotes until find a $ and then take 
		the Var NAME after it, if it valid then will expand it */
char *handle_d_q_var(const char *str, int *index)
{
	char *result = strdup("");
	char *tmp;
	int start = *index;

	while (str[*index] && str[*index] != '"')
	{
		if (special_vars(&result, &str, &start, index) && (*index)++)
			continue;
		if (str[*index] == '$' && str[*index + 1] != '$'
			&& !isnum(str[*index + 1]) && str[*index + 1] != '"')
		{
			take_previous(&result, str, start, (*index));
			(*index)++;
			tmp = expand_variable(str, index);
			result = ft_strjoin(result, tmp);
			free(tmp);
			start = *index;
		}
		else if (str[*index] == '$' && str[*index + 1] == '$')
		{
			(*index) += 2;
			take_previous(&result, str, start, (*index));
			start = (*index);
		}
		else
			(*index)++;
	}
	take_previous(&result, str, start, (*index));
	(*index)++; // Skip the closing double quote
	return (result);
}
/* this func work when there is an single quotes so it will
	concatenate around the string until find 
			the closed quotes */
char *handle_s_q_var(const char *str, int *index)
{
	char *result;
	int start;

	start = (*index);
	while (str[*index] && str[*index] != '\'')
	{
		(*index)++;
	}
	result = strndup(str + start, *index - start);
	(*index)++; // Skip the closing single quote
	return (result);
}

/* this func take the characters that exist before expand the actual variable
 			and join it to the result like : "hello$USER" -> it will join 
					the word hello before expand $USER.
*/
void take_previous(char **result, const char *word, int start, int i)
{
	char	*tmp;

	tmp = strndup(word + start, i - start);
	*result = ft_strjoin(*result, tmp);
	free(tmp);
}

int double_$_cases(char **result,const char *word, int *i, int *start)
{
	// char	*tmp;
	int		flag;

	flag = 0;
	if (word[(*i)] == '$' && (word[(*i) + 1] == '$'
			|| word[(*i) + 1] == '"' || word[(*i) + 1] == '\''))
	{
		if (word[(*i) + 1] == '$')
		{
			(*i) += 2;
			take_previous(result, word, (*start), (*i));
		}
		else
		{
			take_previous(result, word, (*start), (*i));
			++(*i);
		}
		(*start) = *i;
		flag = 1;
	}
	return (flag);
}

int	quotes_cases(char **result,const char *word, int *i, int *start)
{
	char	*tmp;
	int		flag;

	flag = 0;
	if (word[*i] == '\'')
	{
			take_previous(result, word, *start, *i);
			*start = ++*i;//skip initial quotes
			tmp = handle_s_q_var(word, i);
			*result = ft_strjoin(*result, tmp);
			free(tmp);
			*start = *i;
			flag = 1;
	}
	else if (word[*i] == '"')
	{
			take_previous(result, word, *start, *i);
			*start = ++(*i);
			tmp = handle_d_q_var(word, i);
			*result = ft_strjoin(*result, tmp);
			free(tmp);
			*start = *i;
			flag = 2;
	}
	return (flag);
}

/*this func check the case of var, if it inside quotes or not...
	and deppend on this it expand it or not*/
char *handle_var(const char *word)
{
	char *result = strdup("");
	char *tmp;
	int i = 0, start = 0;

	while (word[i])
	{
		if (quotes_cases(&result, word, &i, &start))
			continue;
		 else if (word[i] == '$' && word[i + 1] != '$')
		{
			if (special_vars(&result, &word, &start, &i) != 0 && i++)
				continue;
			take_previous(&result, word, start, i);
			i++;
			tmp = expand_variable(word, &i);
			result = ft_strjoin(result, tmp);
			free(tmp);
			start = i;
		}
		else if (double_$_cases(&result, word, &i, &start))
			continue;
		else
			i++;
	}
	take_previous(&result, word, start, i);
	return (result);
}

int accepted_chars(t_list	*tmp)
{
	if (*(ft_strchr(tmp->content, '$') + 1) == '$'// for multi dollar
				|| *(ft_strchr(tmp->content, '$') + 1) == '_'// for underscore
				|| *(ft_strchr(tmp->content, '$') + 1) == '-'
				|| *(ft_strchr(tmp->content, '$') + 1) == '"'//for double quotes
				|| *(ft_strchr(tmp->content, '$') + 1) == '\'')//for single quotes)
			return (1);
	else
		return (0);
}

/*in this func will looping around all the tokenz and detect is the 
	an var exist, if it then pass it to handle_var to expand
					if it a valid var */
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
			&& *(ft_strchr(tmp->content, '$') + 1) // there is an $ and after it not '\0'
				&& (isalnum(*(ft_strchr(tmp->content, '$') + 1)) || accepted_chars(tmp))
				&& tmp->type != DELEMETRE)
		{
			tmp2 = tmp->content;
			tmp->content = handle_var(tmp->content);
			tmp->type = VAR;
			free(tmp2);
		}
		tmp = tmp->next;
	}
}
