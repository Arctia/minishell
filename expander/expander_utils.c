#include "../global.h"


///receives cmd, 
// void    handle_quotes(t_command cmd)
// {
//     int         i;
//     char        c;
//     char     *tmp;

//     i = 0;
//     while (&cmd.command[i])
//     {}


// }

int mini_sort(char *str)
{
    char set[2];
    int min;
    int qi;
    int wi;
    int ci;

    set[0] = '\'';
    set[1] = '"';
    set[2] = '$';
    qi = ft_strchr_len(str, set[0]);
    wi = ft_strchr_len(str, set[1]);
    ci = ft_strchr_len(str, set[2]);
    if (qi < wi && wi < ci)
        min = qi;
    if (wi < qi && qi < ci)
        min = wi;
    if (ci < qi && qi < wi)
        min = ci;
    return(min);
}

int    expansion_explosion(char *str,char tmp[4095], int *index, char **env)
{
    char    *to_ret;
    char    buff[4095];
    int     i;
    int     j;

    i = *index;
    j = 0;
    while (str[++i] != '\''|| str[i] != '"' 
        || str[i] != '$' || str[i] != '\0' || !ft_isspace(str[i]))
    {
        buff[j++] = str[i];
    }
    *index = i;
    i = 0;
    buff[j] = '\0';
    to_ret = exp_tkn(buff, env);
    j = ft_strlen(tmp);
    while (to_ret[i])
        tmp[j++] = to_ret[i++];
    return (i);
}

char    *new_tkn_aux(char *str, t_command cmd, int i , int k)
{
    int f;
    int c;
    char tmp[4095];
    
    f = mini_sort(str);
    c = str[f];
    while (++k < f && (str[k] != c && (c == '"' || c == '\'') || str[k]))
    {
        if ((str[k] == '$' && c == '"') || (c != '\'' && str[k] == '$'))
            i += expansion_explosion(str, tmp[4095], &k, &cmd.shell->env);
        tmp[i] = str[k];
    }
    return (tmp);
}

// char    *new_tkn(char *ol_tkn, t_command cmd) 
// {
//     int     i;
//     int     f;
//     int     k;
//     char    tmp[4095];
//     char    c;

//     i = 0;
//     k = -1;
//     if (mini_sort(ol_tkn) >= 0)
//     {
//         while (i < ft_strlen(ol_tkn))
//         {
//             new_tkn_aux(ol_tkn, cmd, i, k);
//             // f = mini_sort(ol_tkn);
//             // c = ol_tkn[f];
//             // while (++k < f)
//             // {   
//             //     if (ol_tkn[k] == '$')
//             //         i += expansion_explosion(ol_tkn,tmp, &k, &cmd.shell->env);
//             //     tmp[i] = ol_tkn[k];
//             //     while (ol_tkn[++k] != c)
//             //     {
//             //         if (ol_tkn[k] == '$')
//             //             i += expansion_explosion(ol_tkn, tmp, &k, &cmd.shell->env);
//             //         tmp[i] = ol_tkn[k];
//             //     }
//             // }
//         }
//         return (tmp);
//     }
//     else
//         return(ol_tkn);
// }

char *new_tkn(char *ol_tkn, t_command cmd)
{
    int i;
    int f;
    int k;
    char tmp[4095];
    char c;

    i = 0;
    k = -1;
    if (mini_sort(ol_tkn) >= 0)
    {
        while (i < ft_strlen(ol_tkn))
        {
            f = mini_sort(ol_tkn);
            c = ol_tkn[f];
            while (++k < f && (ol_tkn[k] != c && (c == '"' || c == '\'') || ol_tkn[k]))
            {
                if ((ol_tkn[k] == '$' && c == '"') || (c != '\'' && ol_tkn[k] == '$'))
                    i += expansion_explosion(ol_tkn, tmp[4095], &k, &cmd.shell->env);
                tmp[i] = ol_tkn[k];
            }
            return (tmp);
        }
    }
    else
        return (ol_tkn);
}
