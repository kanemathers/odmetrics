#ifndef ODM_ODM_H
#define ODM_ODM_H

#include <pthread.h>

struct metric;

typedef struct odm
{
    struct metric *metrics;
    pthread_t      server;
} odm_t;

int odm_init(odm_t *odm);
void odm_destroy(odm_t *odm);

#endif
