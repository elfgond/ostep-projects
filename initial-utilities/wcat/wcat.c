#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char buf[512];

void cat(int fd)
{
    int n;

    while ((n = read(fd, buf, sizeof(buf))) > 0)
    {
        if (write(1, buf, n) != n)
        {
            fprintf(stderr, "cat: write error\n");
            exit(1);
        }
    }
    if (n < 0)
    {
        fprintf(stderr, "cat: read error\n");
        exit(1);
    }
}

int main(int argc, char *argv[])
{
    // printf("%d\n", argc);
    if (argc <= 0)
    {
        cat(0);
        exit(0);
    }

    int fd, i;

    for (i = 1; i < argc; i++)
    {
        if ((fd = open(argv[i], 0)) < 0)
        {
            fprintf(stdout, "wcat: cannot open file\n");
            exit(1);
        }
        // printf("cat %s\n", argv[i]);
        cat(fd);
        close(fd);
    }
    exit(0);
}
