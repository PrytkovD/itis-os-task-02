#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	if (argc != 1) {
		printf("Usage: S\n");
		_exit(EXIT_FAILURE);
	}

	int s = atoi(argv[0]);

	pid_t my_pid = getpid();
	pid_t parent_pid = getppid();

	printf("Child[%d]: I am started. My PID %d. Parent PID %d.\n",
		my_pid,
		my_pid,
		parent_pid
	);

	sleep(s);

	printf("Child[%d]: I am ended. My PID %d. Parent PID %d.\n",
		my_pid,
		my_pid,
		parent_pid
	);

	return 0;
}
