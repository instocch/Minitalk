/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstocche <mstocche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 11:51:34 by mstocche          #+#    #+#             */
/*   Updated: 2023/05/17 17:25:13 by mstocche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "libft/libft.h"

void receive_str(int sig, char *str, int *pos)
{
    static int  bits = 0;

    str[*pos] <<= 1;
    if (sig == SIGUSR1)
    {
        str[*pos] |= 1;
    }
    bits++;
    if (bits == 8)
    {
        (*pos)++;
        bits = 0;
    }
}

void handler(int sig, siginfo_t *info, void *cont)
{
    (void)cont;
    static int len_bits = 0;
    static unsigned int str_len = 0;
    static int str_bits = 0;
    static char *str;
    static int  pos = 0;

    if (len_bits < 32)
    {
        str_len <<= 1;
        if (sig == SIGUSR1) {
            str_len |= 1;
        }
        len_bits++;
        if (len_bits == 32)
        {
            str = calloc(str_len + 1, sizeof(char));
            str[str_len] = '\0';
            if (!str)
            {
                printf("Error while calloc\n");
                exit(EXIT_FAILURE);
            }
            str_bits = str_len * 8;
        }
    }
    else
    {
        if (str_bits >= 0)
        {
            receive_str(sig, str, &pos);
            str_bits--;
            if (str_bits == 0)
            {
                /* write(1, str, str_len); */
                printf("Received string from client: %s\n", str);
                len_bits = 0;
                pos = 0;
                free(str);
            }
        }
    }
    kill(info->si_pid, SIGUSR1);
}

int main(void) {
    pid_t pid;
    // char str;
    struct sigaction sig;

    pid = getpid();
    printf("Server pid: %d\n", pid);

    sig.sa_sigaction = handler;
    sig.sa_flags = SA_SIGINFO;
    sigaction(SIGUSR1, &sig, NULL);
    sigaction(SIGUSR2, &sig, NULL);

    while(1) {
        pause();
    }
}
