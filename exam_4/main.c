
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
void ft_error(char *str)
{
    int i = 0;
    while(str[i])
    {
        write(2, &str[i], 1);
        i++;
    }
}

void ft_cd(char **cmd)
{
    if(cmd[1] == NULL || cmd[2] != NULL)// the first one means id we have only cd  - the second one means if we have more that one path
        ft_error("error: cd: bad arguments\n");
    else
    {
        if(chdir(cmd[1]) != 0)
        {
            ft_error("error: cd: cannot change directory to ");
            ft_error (cmd[1]);
            ft_error("\n");
        }
    }
}

int main (int ac, char **av, char **env)
{
    int i = 1;
    int j;
    int pip = 0;
    int pid;
    int p = 0;
    int fd[2];
    char *cmd[1000000] = {NULL};
    if(ac == 1)
        return 0;
    while(av[i])
    {
        pip = 0;
        j = 0;
        while(av[i] && (strcmp(av[i], "|") == 0 || strcmp(av[i], ";") == 0))// skip the | ;
            i++;
        if(av[i] == NULL)
            break;
        // i is in the indice of the beginig of teh each coamnd..
        while(av[i] && strcmp(av[i], "|")  != 0 && strcmp(av[i], ";") != 0)// fill the cmd
            cmd[j++] = av[i++];
        // i in the indice  | ; or \0
  
        cmd [j] = NULL;
        // -------------------------------------------------
        if(strcmp(cmd[0], "cd") == 0)//if the first command is cd
            ft_cd(cmd);
        // -------------------------------------------------
        else
        {
            
            if(av[i] && strcmp(av[i], "|") == 0)// check if we have a pipe
            {
                pip = 1;
                if(pipe(fd) != 0)
                {
                    ft_error("error:fatal\n");
                    exit(1);
                }
            }
            pid = fork();
            if(pid == -1)
            {
                ft_error("error: fatal\n");
                exit(1) ;
            }
            p++;
            if(pid == 0)// child process
            {
                if(pip == 1)
                {
                    close (1);
                    dup2(fd[1], 1);
                    close(fd[0]); close(fd[1]);
                }
                if(execve(cmd[0], cmd, env) < 0)
                {
                    ft_error("error: cannot execute ");
                    ft_error(cmd[0]);
                    ft_error("\n");
                    exit(1);
                }
            }
                // the parent process
            if(pip == 1)// if we have a pipe
            {
                close(0);
                dup2(fd[0], 0);
                close(fd[0]); close (fd[1]);
            }
            if(pip == 0)// if we dont have a pipe
            {
                for(int i = 0; i < p; i++)
                    waitpid(-1, NULL, 0); //-1 means wait for any child process
                p = 0;
            }
        }
        if(av[i] == NULL)
            break;
        i++;
    }
    return 0;
}




