/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fg_blt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macos <macos@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 14:35:16 by oelazzou          #+#    #+#             */
/*   Updated: 2021/03/10 20:48:04 by macos            ###   ########.fr       */
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

    if ((size = get_arr_size(cmd)) == 1)
        return (CURRENT_JOB);
    if (size > 1)
    {
        if (cmd[1] && cmd[1][0] == '%' && cmd[1][1] == '-' && !cmd[1][2])
            return (size_of_lst(g_jobs_lst) - 1);
        else if (cmd[1] && cmd[1][0] == '%' && (cmd[1][1] == '+' || cmd[1][1] == '%') && !cmd[1][2])
            return (CURRENT_JOB);
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
    while (ptr && job_id > 0)
    {
        if (((ptr->job_id == job_id) && ((ptr->mode & IS_BACKGROUD) || (ptr->mode & IS_SUSPENDED))) || (job_id == 1 && ptr->c == '+'))
        {
            if (tcsetpgrp(fd, ptr->grp_pid) == -1)
            {
                close(fd);
                perror("tcsetpgrp");
                return (1);
            }
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
		    	{
                    // ft_putnbr_wspace(ptr->job_id);
                    // ft_putendl_fd("Done", 1);
                    delete_node(&g_jobs_lst, ptr->grp_pid);
				    //ptr->mode = IS_TERMINATED;
			    } else if (WIFSIGNALED(status)) {
                    delete_node(&g_jobs_lst, ptr->grp_pid);
				   // ptr->mode = IS_TERMINATED;
			    }
            }
            sig_groupe();
            break ;
        }
        ptr = ptr->next;
    }
    close(fd);
    signal(SIGCHLD, checkchild2);
    return (0);
}
