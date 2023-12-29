#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
	if (argc != 2) {
		printf("Usage: %s N\n", argv[0]);
		_exit(EXIT_FAILURE);
	}

	int n = atoi(argv[1]);
	pid_t parent_pid = getpid();
	pid_t child_pid;

	srand(time(NULL));

	for (int i = 0; i < n; i++) {
		child_pid = fork();
		int random_int = rand() % 6 + 5;

		if (child_pid < 0) {
			perror("fork");
			_exit(EXIT_FAILURE);
		}

		if (child_pid == 0) {
			// child process
			char arg[8];
			sprintf(arg, "%d", random_int);
			char *argv[] = { arg, NULL };
			execve("./out/child.exe", argv, NULL);
			_exit(EXIT_SUCCESS);
		} else {
			// parent process
			printf("Parent[%d]: I ran children process with PID %d.\n",
				parent_pid,
				child_pid
			);
		}
	}

	int status;
	int wait_pid;

	while ((wait_pid = wait(&status)) > 0) {
		if (WIFEXITED(status)) {
			int exit_status = WEXITSTATUS(status);

			printf("Parent[%d]: Child with PID %d terminated. Exit status %d.\n",
				parent_pid,
				getpid(),
				exit_status
			);


			if (exit_status != 0) {
				child_pid = fork();

				if (child_pid < 0) {
					perror("fork");
					_exit(EXIT_FAILURE);
				}

				if (child_pid == 0) {
					// child process
					srand(time(NULL));
					int random_int = rand() % 6 + 5;
					char arg[8];
					sprintf(arg, "%d", random_int);
					char *argv[] = { arg, NULL };
					execve("./out/child.exe", argv, NULL);
					_exit(EXIT_SUCCESS);
				} else {
					// parent process
					printf("Parent[%d]: I ran children process with PID %d.\n",
						parent_pid,
						child_pid
					);
				}
			}
		}
	}

	return 0;
}
