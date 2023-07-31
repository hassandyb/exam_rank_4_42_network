
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
    int has_pipe = 0;
    if(argv[i] != NULL && ft_strcmp(argv[i], "|") == 1)
        has_pipe = 1;
    if(has_pipe == 1 && pipe(fd) == -1)
        return (ft_error("error: fatal\n"));
    int pid = fork();
    if(pid == 0)//child process
    {
        if(has_pipe == 1 && (dup2(fd[1], 1) == -1 || close(fd[0]) == -1 || close(fd[1]) == -1))
            return ft_error("error: fatal\n");
        execve(*argv, argv, envp);
        return ft_error (*argv), ft_error(": command not found\n");
    }
    waitpid(pid, &status, 0);
    if(has_pipe == 1 && (dup2(fd[0], 0) == -1 || close(fd[0] == -1 || close(fd[1]) == -1)))
        return ft_error("error fatal\n");
    return (WIFEXITED(status) && WEXITSTATUS(status));
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
            // printf("%s\n", *argv);
            if(ft_strcmp(*argv, "/bin/cd") == 1)
                status = ft_cd(argv, envp);
            else if(i != 0) // i == 0 means we are in the end 
                status = ft_exec(argv, i, envp);
         
        }
    }
    return status;
}












