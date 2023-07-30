
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdio.h>


int ft_strcmp(char *s1, char *s2)
{
    int i = 0;
    if(s1 == NULL || s2 == NULL)
        return 1;
    while(s1[i] && s2[i] && s1[i] == s2[i])
        i++;
    if(s1[i] == '\0' && s2[i] == '\0')
        return 1;
    return (0);
}










int main (int argc, char **argv, char **envp)
{
    int i = 0;
    int status = 0;
    if(argc > 1)
    {
        while(argv[i] && argv[++i])
        {
            argv = argv + i;
            i = 0;
            while(argv[i] && ft_strcmp(argv[i], "|") == 0 && ft_strcmp(argv[i], ";") == 0)
            {
                i++;
            }
            if(ft_strcmp(*argv, "cd") == 1)
                status = ft_cd(argv, i, envp);
            else
                status = ft_exec()
            // printf("%d\n", i);
        }
    }
}












