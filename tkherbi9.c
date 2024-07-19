# include "minishell.h"

int s_with_d_Q(char *s)
{
    int i;
    int is_quotes;

    i = 0;
    while (s[i++])
    {
        is_quotes = check_quotes(s[i], is_quotes);
        if (s[i])
    }
}