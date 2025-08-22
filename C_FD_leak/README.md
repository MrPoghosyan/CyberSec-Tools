File Descriptor Leak Vulnerability in C
📌 Description

Այս օրինակում ցուցադրվում է file descriptor leak տեսակի խոցելիություն․
Եթե parent պրոցեսում բացված ֆայլի դեսկրիպտորը (file descriptor) չփակվի կամ չնշվի որպես close-on-exec (O_CLOEXEC) դրոշակով, ապա այն կժառանգվի child պրոցեսի կողմից։

Արդյունքում՝ եթե child պրոցեսում աշխատեցվի կոդ, որը ստուգում է բացված դեսկրիպտորները, հնարավոր է կարդալ այն ֆայլերը, որոնք պետք է մնային գաղտնի։

⚠️ Vulnerability Example

Ծնող (parent) պրոցեսը բացում է secret_file.txt-ը․
  int fd = open("secret_file.txt", O_RDONLY);

Այնուհետև կատարվում է fork() և execl()․
Child պրոցեսը իրականացնում է ծրագիր (check_fds), որը փորձում է կարդալ բացված file descriptor-ները։

Child կոդում (check_fds.c) իրականացվում է հետևյալ ստուգումը․
  for (int i = 3; i != rlim.rlim_cur; ++i) {
    while ((res = read(i, buf, sizeof(buf)) > 0)) {
        printf("Found secret file!\n");
        printf("Contents:\n");
        printf("%s", buf);
        return 0;
    }
  }

## 🚀 How to Test the Vulnerability
  Այսպիսով, եթե parent պրոցեսում բացված էր գաղտնի ֆայլ, ապա child պրոցեսը հեշտությամբ գտնում է և արտածում դրա բովանդակությունը։

```bash
  cc -g -Wall -Wextra run_child.c -o run_proc
  cc -g -Wall -Wextra check_fds.c -o hack
  rm -f a.out
  ./run_proc hack

Demo Output
  Found secret file!
  Contents:
  Super secret file!

🔴 Security Risk

Թաքուն տվյալներ (գաղտնի ֆայլեր, կոնֆիգուրացիաներ, credentials) կարող են արտահոսել։

Հարձակվողը, ունենալով միայն child պրոցեսի կոդի կատարման հնարավորություն, կարող է ընթերցել այն, ինչ parent-ը արդեն բացել էր։

Այս խնդիրը դասական TOCTOU (Time-of-check to time-of-use) և file descriptor inheritance խոցելիությունների օրինակ է։

✅ Mitigation

Խնդիրը լուծելու համար անհրաժեշտ է․

1.Փակել file descriptor-ը ծնող պրոցեսում, եթե այն այլևս պետք չէ․
  close(fd);

#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    if (argc != 2)
        exit(1);

    int fd = open("secret_file.txt", O_RDONLY);
    if (fd < 0)
        perror("Open!");

    // Ֆայլը բացվելուց հետո անմիջապես փակվում է
    close(fd);

    pid_t pid = fork();
    if (pid == 0) {
        execl(argv[1], argv[1], NULL);
        _exit(1);
    }

    wait(NULL);
}



2.Կամ բացել ֆայլը O_CLOEXEC դրոշակով, որպեսզի այն ավտոմատ փակվի exec()-ի ժամանակ․
  int fd = open("secret_file.txt", O_RDONLY | O_CLOEXEC);

  #include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    if (argc != 2)
        exit(1);

    // O_CLOEXEC flag ensures the fd is closed on exec()
    int fd = open("secret_file.txt", O_RDONLY | O_CLOEXEC);
    if (fd < 0)
        perror("Open!");

    pid_t pid = fork();
    if (pid == 0) {
        execl(argv[1], argv[1], NULL);
        _exit(1);
    }

    wait(NULL);
}
