/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ma.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabakhar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 14:39:57 by yabakhar          #+#    #+#             */
/*   Updated: 2021/03/25 14:44:26 by yabakhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void sfefw(char *str)
{
	int i = 0;
	int debut = 0;
	int fin = 0;
	int flag = 0;

	while (str[i])
	{
		if (str[i] && str[i] == '!' && !flag)
		{
			flag = 1;
			debut = i;
		}
		else if (str[i] && (str[i] == ' ' || str[i] == '|' || str[i] == '&' || str[i] == ';' || str[i] == '$'))
		{
			fin = i;
			break ;
		}
		i++;
	}
	if (fin == 0)
		fin = i;
	char *ret = ft_strsub(str,debut,fin - debut);
	ft_putstr(ret);
}

int main(int ac,char **av)
{
	ac = 1;
	char *str = "pwd!dfjewpwd!!feo\"wih!feiowh!!fiehwo";
	sfefw(str);
}
