#include "minishell.c"

void check_validity(t_list *head)
{
    t_list *tmp;

    tmp = head;
    while (tmp != NULL)
    {
        if (tmp->type == PIPE)
        {
            if (!tmp || tmp->next == NULL)
            {
                printf("syntax error near unexpected token '|'\n");
                exit(1);
            }
            else if (tmp->type == PIPE || tmp->next->type == PIPE)
            {
                printf("syntax error near unexpected token '|'\n");
                exit(1);
            }
        }
        else if (tmp->type == SEMI)
        {
            if (tmp == NULL || tmp->next == NULL)
            {
                printf("syntax error near unexpected token ';'\n");
                exit(1);
            }
            else if (tmp->type == SEMI || tmp->next->type == SEMI)
            {
                printf("syntax error near unexpected token ';'\n");
                exit(1);
            }
        }
        else if (tmp->type == IN)
        {
            if (tmp == NULL || tmp->next == NULL)
            {
                printf("syntax error near unexpected token '<'\n");
                exit(1);
            }
            else if (tmp->type == IN || tmp->next->type == IN)
            {
                printf("syntax error near unexpected token '<'\n");
                exit(1);
            }
        }
        else if (tmp->type == OUT)
        {
            if (tmp == NULL || tmp->next == NULL)
            {
                printf("syntax error near unexpected token '>'\n");
                exit(1);
            }
            else if (tmp->type == OUT || tmp->next->type == OUT)
            {
                printf("syntax error near unexpected token '>'\n");
                exit(1);
            }
        }
        tmp = tmp->next;
    }
}
