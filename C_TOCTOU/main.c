#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

unsigned good_checksum = 105140; //write the required number of bytes

unsigned computer_checksum(int fd)
{
    unsigned sum = 0;
    char buf[32];
    ssize_t res;

    while ((res = read(fd, buf, sizeof(buf))) > 0){
        for (ssize_t i = 0; i != res; ++i)
            sum += buf[i];
    }
    return sum;
}

int main(int argc, char **argv)
{
    if(argc != 2)
        exit(1);

    int fd = open(argv[1], O_RDONLY);
    if (fd < 0)
        perror("open");

    unsigned checksum = computer_checksum(fd);
    close(fd);
    printf("Check sum: %d\n", checksum);
    if (checksum != good_checksum){
        printf("Hack prevented!\n");
        exit(1);
    }

    sleep(11); //Anything can happen instead of sleep() in code!

    execl(argv[1], argv[1], NULL);
    perror("");
}
