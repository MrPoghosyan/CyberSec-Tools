#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv)
{
	if (argc != 2)
		exit(1);

	int fd = open("secret_file.txt", O_RDONLY);//(... | O_CLOEXEC)
	if (fd < 0)
		perror("Open!");

	//....//

	pid_t pid = fork();
	if (pid == 0){
		//or close(fd) this;
		execl(argv[1], argv[1], NULL);
		_exit(1);
	}
	
	wait(NULL);
}
