#ifndef RTS_RTS_H
#define RTS_RTS_H

#include <pthread.h>

typedef struct rts
{
    pthread_t server;
} rts_t;

int rts_init(rts_t *rts);
void rts_destroy(rts_t *rts);

#endif
