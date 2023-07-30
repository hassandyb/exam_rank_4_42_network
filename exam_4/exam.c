
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

int ft_error(char *err)
{
    int i = -1;
    while(err[++i])
        write(2, &err[i], 1);
    return 1;
}

int ft_cd (char **argv, char **envp)
{
    if(argv[1] == NULL || ft_strcmp(argv[1], "|") == 1 || ft_strcmp(argv[1], ";") == 1)
        return (ft_error ("error: cd: bad arguments\n"));
    else if(chdir(argv[1]) == -1)
    {
        ft_error(" cd: ");
        ft_error(argv[1]);
        ft_error(": No such file or directory");
        return (1);
    }
    return (0);
}

int ft_exec(char **argv, int i, char **envp)
{
    int fd[2];
    int status;
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
                status = ft_cd(argv, envp);
            else if(i != 0) // i == 0 means we are in the end 
                status = ft_exec(argv, i, envp)
            printf("%d\n", i);
        }
    }
    return status;
}












