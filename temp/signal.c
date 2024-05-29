#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include "../readline/readline.h"

int main(void)
{
	char *input;

	input = NULL;
	input = readline("input$ ");
	printf("input = %p\n", &input);
	if (input)
		printf("input = %s\n", input);
	return (0);
}

// void	signal_handler(int sig, siginfo_t *info, void *context)
// {
// 	if (sig == SIGINT)
// 		return ;
// 	else
// 		printf("signal %d\n", sig);
// }

// int	test(void)
// {
// 	struct sigaction	act;
// 	int					n;
// 	char				*str;

// 	act.sa_sigaction = signal_handler;
// 	n = 0;
//     sigaction(SIGINT, &act, NULL);
// 	while (++n < 12)
// 	{
// 		str = strdup("hello");
// 		printf("str = %s\n", str);
// 		printf("n = %d\n", n);
// 		sleep(1);
//         printf("after sleep str = %s\n", str);
// 		free(str);
// 	}
// 	return (0);
// }

// int	main(void)
// {
// 	pid_t pid;
// 	chdir("--home_dir=~");
// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		execve("/bin/ls", (char *[]){"ls", "-l", NULL}, NULL);
// 	}
// 	return (0);
// }
