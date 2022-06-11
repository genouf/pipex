#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	main(void)
{
	int	pfd[2];
	int	pid;
	char *args_l[] = {"ls", (char *)0};
	char *args_w[] = {"wc", (char *)0};
	
	(void)argc;
	(void)argv;
	/* init du pipe */
	if (pipe(pfd) == -1)
	{
		ft_printf("pipe failed\n");
		return (1);
	}
	/* init du child */
	if ((pid = fork()) < 0)
	{
		ft_printf("fork failed\n");
		return (2);
	}
	/* process du child */
	if (pid == 0)
	{
		close(pfd[1]);
		dup2(pfd[0], 0);
		close(pfd[0]);
		execve(args_w[0], args_w, env);
		ft_printf("wc failed");
		return (3);
	}
	else
	{
		close(pfd[0]);
		dup2(pfd[1], 1);
		close(pfd[1]);
		execve(args_l[0], args_l, env);
		ft_printf("ls failed");
		return (4);
	}
	return (0);
}