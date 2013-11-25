#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include <pthread.h>

#include "rts/rts.h"

struct netinfo
{
    const char *hostname;
    const char *port;
};

static int net_listen(const char *hostname, const char *port)
{
    int              yes = 1;
    int              sockfd;
    struct addrinfo  hints;
    struct addrinfo *info;
    struct addrinfo *p;

    memset(&hints, 0, sizeof hints);

    hints.ai_family   = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if (getaddrinfo(hostname, port, &hints, &info) != 0)
        return -1;

    for (p = info; p != NULL; p = p->ai_next)
    {
        sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);

        if (sockfd < 0)
            continue;

        if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof yes) != 0)
        {
            close(sockfd);

            continue;
        }

        if (bind(sockfd, p->ai_addr, p->ai_addrlen) != 0)
        {
            close(sockfd);

            continue;
        }

        freeaddrinfo(info);

        if (listen(sockfd, 10) != 0)
        {
            close(sockfd);

            return -1;
        }

        return sockfd;
    }

    freeaddrinfo(info);

    return -1;
}

static int net_sendall(int sockfd, char *buffer, int *len)
{
    int total     = 0;
    int remaining = *len;
    int n;

    while (total < *len)
    {
        n = send(sockfd, buffer + total, remaining, 0);

        if (n == -1)
            break;

        total     += n;
        remaining -= n;
    }

    *len = total;

    return n < 0 ? -1 : 0;
}

static void sigchild_handler(int s)
{
    while (waitpid(-1, NULL, WNOHANG) > 0);
}

static void *start_server(void *info)
{
    struct netinfo         *netinfo = info;
    int                     sockfd;
    int                     new_fd;
    struct sockaddr_storage their_addr;
    socklen_t               sin_size;
    struct sigaction        sa;

    /* XXX: test data */
    char *test_data = "Hello, World!\n";
    int   test_len  = strlen(test_data);

    sockfd = net_listen(netinfo->hostname, netinfo->port);

    if (sockfd < 0)
        return NULL;

    sa.sa_handler = sigchild_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags   = SA_RESTART;

    if (sigaction(SIGCHLD, &sa, NULL) != 0)
        return NULL;

    while (1)
    {
        sin_size = sizeof their_addr;
        new_fd   = accept(sockfd, (struct sockaddr *) &their_addr, &sin_size);

        if (fork() == 0)
        {
            close(sockfd);
            net_sendall(new_fd, test_data, &test_len);
            close(new_fd);

            exit(0);
        }

        close(new_fd);
    }

    return NULL;
}

int rts_serve(rts_t *rts, const char *hostname, const char *port)
{
    struct netinfo netinfo;
    pthread_attr_t attrs;

    netinfo.hostname = hostname;
    netinfo.port     = port;

    pthread_attr_init(&attrs);
    pthread_attr_setdetachstate(&attrs, PTHREAD_CREATE_DETACHED);
    pthread_create(&(rts->server), &attrs, start_server, &netinfo);
    pthread_attr_destroy(&attrs);

    /* guessing this is needed to ensure ``start_server`` enters its
     * ``while (1)`` loop before we return.
     *
     * need a better way to do this.
     */
    sleep(1);

    return 0;
}
