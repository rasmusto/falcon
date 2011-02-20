#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, const char *argv[])
{
    char cmd[128];
    char param1[128];
    char param2[128];
    char str[128];
    str[0] = 0;
    int i = 0;
    printf("argc = %d\n", argc);
    while(argv[i] != NULL)
    {
        printf("argv[%d] = %s\n", i, argv[i]); 
        strcat(str,argv[i]);
        strcat(str," ");
        i++;
    }

    char ** test_argv;

    printf("str = \"%s\"\n", str);
    sscanf(str, "%s %s %s", cmd, param1, param2);


    int test_argc = 0;
    while(sscanf(str, "%s", test_argv[test_argc]))
        test_argc++;

    for (i=0; i<test_argc; i++)
        printf("test_argv[%d] = %s\n", test_argc, test_argv[i]);

    printf("cmd    = %s\n", cmd);
    printf("param1 = %s\n", param1);
    printf("param2 = %s\n", param2);

    
    return 0;
}
