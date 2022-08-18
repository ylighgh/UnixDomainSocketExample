#include <sys/socket.h>
#include <sys/un.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define MY_SOCK_PATH "/tmp/yl_c.sock"
#define LISTEN_BACKLOG 50
#define MAX 80
#define handle_error(msg)   \
    do                      \
    {                       \
        perror(msg);        \
        exit(EXIT_FAILURE); \
    } while (0)

void func(int connfd)
{
    char buff[MAX];
    char message[] = "From server: Hello!This is C Socket Server!\n";

    bzero(buff, MAX);
    read(connfd, buff, sizeof(buff));
    printf("From client: %s", buff);

    bzero(buff, MAX);
    write(connfd, message, sizeof(message));

    close(connfd);
}

int main(int argc, char *argv[])
{
    while (1)
    {
        int sfd, cfd;
        struct sockaddr_un my_addr, peer_addr;
        socklen_t peer_addr_size;
        sfd = socket(AF_UNIX, SOCK_STREAM, 0);
        if (sfd == -1)
        {
            handle_error("socket");
        }

        memset(&my_addr, 0, sizeof(my_addr));
        my_addr.sun_family = AF_UNIX;
        strncpy(my_addr.sun_path, MY_SOCK_PATH,
                sizeof(my_addr.sun_path) - 1);

        char sock_path[] = MY_SOCK_PATH;
        unlink(sock_path);

        //assigning a name to a socket
        if (bind(sfd, (struct sockaddr *)&my_addr,
                 sizeof(my_addr)) == -1)
        {
            handle_error("bind");
        }

        if (listen(sfd, LISTEN_BACKLOG) == -1)
        {
            handle_error("listen");
        }

        peer_addr_size = sizeof(peer_addr);
        cfd = accept(sfd, (struct sockaddr *)&peer_addr,
                     &peer_addr_size);
        if (cfd == -1)
        {
            handle_error("accept");
        }

        func(cfd);

        close(sfd);
    }
}