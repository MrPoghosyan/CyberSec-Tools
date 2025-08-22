#include <unistd.h>
#include <stdio.h>
#include <sys/resource.h>

int main(void)
{
	struct rlimit rlim;

	int res = getrlimit(RLIMIT_NOFILE, &rlim);
	if (res < 0)
		perror("Limit!");
	//printf("%ld, %ld\n", rlim.rlim_cur, rlim.rlim_max);

	char buf[1024];
	for (int i = 3; i != rlim.rlim_cur; ++i){
		while ((res = read(i, buf, sizeof(buf)) > 0)){
			printf("Found secret file!\n");
			printf("Contents:\n");
			printf("%s", buf);
			return 0;
		}
	}
	return 0;
}
