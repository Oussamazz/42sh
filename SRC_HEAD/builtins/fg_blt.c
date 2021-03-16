/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fg_blt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelazzou <oelazzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 14:35:16 by oelazzou          #+#    #+#             */
/*   Updated: 2021/03/13 19:38:36 by oelazzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static int      size_of_lst(t_job_ctrl *lst)
{
    int size;
    t_job_ctrl *ptr;

    ptr = g_jobs_lst;
    size = 0;
    while (ptr)
    {
        size++;
        ptr = ptr->next;
    }
    return (size);
}

static int  get_job_id(char **cmd)
{
    int size;

    size = 0;
    if ((size = get_arr_size(cmd)) == 1)
        return (0);
    if (size > 1)
    {
        if (cmd[1] && cmd[1][0] == '%' && cmd[1][1] == '-' && !cmd[1][2])
            return (size_of_lst(g_jobs_lst) - 1);
        else if (cmd[1] && cmd[1][0] == '%' && (cmd[1][1] == '+' || cmd[1][1] == '%') && !cmd[1][2])
            return (0);
        else if (cmd[1] && cmd[1][0] == '%' && ft_isdigit(cmd[1][1]))
            return (ft_atoi(&cmd[1][1]));
    }
    return (-1);
}

int     fg_blt(char **cmd)
{
    int pid;
    int status;
    int fd;
    t_job_ctrl *ptr;
    int job_id;

    job_id = get_job_id(cmd);
    ptr = g_jobs_lst;
    fd = 0;
    if ((fd = open(ttyname(0), O_RDWR)) == -1)
		return (1);
    signal(SIGCHLD, NULL);
    while (ptr && job_id >= 0)
    {
        if (((ptr->c == '+' && !job_id) || (ptr->job_id == job_id && job_id))) // && ((ptr->mode & IS_BACKGROUD) || (ptr->mode & IS_RUNNING))
        {
            ft_putendl_fd("fg idkhlt", 2);
            if (tcsetpgrp(fd, ptr->grp_pid) == -1)
            {
                close(fd);
                perror("tcsetpgrp");
                return (1);
            }
            close(fd);
            kill(ptr->grp_pid * -1, SIGCONT);
            ptr->mode = IS_FOURGROUND | IS_RUNNING;
            while ((waitpid(ptr->grp_pid * -1, &status, WUNTRACED | WCONTINUED)) > 0)
            {
		        if (WIFSTOPPED(status))
                {
                    ptr->mode = IS_SUSPENDED;
			        break ;
                }
                else if (WIFEXITED(status))
                    delete_node(&g_jobs_lst, ptr->grp_pid);
			    else if (WIFSIGNALED(status))
                    delete_node(&g_jobs_lst, ptr->grp_pid);
            }
            sig_groupe();
            break ;
        }
        ptr = ptr->next;
    }
    signal(SIGCHLD, checkchild2);
    return (0);
}
