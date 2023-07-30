#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdio.h>



int ft_strcmp(char *s1, char *s2)
{
    int i = 0;
    if(s1 == NULL || s2 == NULL)
        return 0;
    while(s1[i] && s2[i] && s1[i] == s2[i])
        i++;
    if(s1[i] == '\0' && s2[i] == '\0')
        return 1;
    return (0);
}

int main()
{
    printf("%d\n", ft_strcmp("|", "|"));
}