
#include "../../includes/sh.h"
#include <sys/wait.h>

int child_group;
int g_status;
int g_pid;

void check_child(int sig) {

    int status = 0;

    waitpid(child_group * -1, &status, WUNTRACED | WCONTINUED | WNOHANG);
    if (WIFCONTINUED(status)) {
        printf("continued\n");
    }
    if (WIFEXITED(status)) 
    {
        printf("exited, status=%d\n", WEXITSTATUS(status));
    } if (WIFSIGNALED(status)) {
        printf("killed by signal %d\n", WTERMSIG(status));
    } if (WIFSTOPPED(status)) {
        printf("stopped by signal %d\n", WSTOPSIG(status));
    }
}

void    ctrl_c(int sig)
{
    if (sig == SIGINT)
        printf("SIGINT catched\n");
    return ;
}

void _echo(char **av) {
    int i = 0;
    while (av[i]) {
        ft_putendl_fd(av[i], 1);
        i++;
    }
    exit(0);
}

int main(int ac, char *av[], char **env)
{
    pid_t pid;
    int status;

    char *arv[4] = {"/bin/sleep", "45545", NULL, NULL};
    char *arv1[4] = {"/bin/sleep", "1212", NULL ,NULL};
    int pip[2];

    status = 0;
    if (pipe(pip) ==  -1)
        exit(444);
    int tmp_pipinput = pip[0];
    if ((pid = fork()) < 0)
        return (2);
    if (!g_pid && pid)
        g_pid = pid;
    if (pid == 0) 
    {
        //g_pid == 0 ? g_pid = pid : 0;
        if (setpgid(getpid(), g_pid) == -1)
            exit (444);
        dup2(pip[1], 1);
        close(pip[1]);
        close(pip[0]);
        execve(arv[0], arv, NULL);
        //_echo(arv);
        //exit(444);
    }
    else
    {
        int childp = 0;
        if (tcsetpgrp(open(ttyname(0), O_RDWR), g_pid) == -1)
            perror("error :");
        close(pip[1]);
        if ((childp = fork()) == 0) {
            if (setpgid(getpid(), g_pid) == -1)
                exit(42);
            dup2(tmp_pipinput, 0);
            close(tmp_pipinput);
            execve(arv1[0], arv1, NULL);
            exit(555);
        }
        close(tmp_pipinput);
        // signal(SIGCHLD, checkchild);
        // signal(SIGINT, ctrl_c);
        // while (waitpid(childp, &status, WNOHANG | WUNTRACED | WCONTINUED) != -1){
        //     ;
        // }
        int pp = 0;
        while ((pp = waitpid(g_pid * -1, &status, 0)) != -1){
           ;
        }
        // while (wait(0) > -1){
        //     printf("exit\n");
        // }
        signal(SIGTTIN, SIG_IGN);
        signal(SIGTTOU, SIG_IGN);
        if (tcsetpgrp(open(ttyname(0), O_RDWR), getpid()) == -1)
            perror("error :");
        signal(SIGTTIN, SIG_DFL);
        signal(SIGTTOU, SIG_DFL);
    }
    return (-1);
}