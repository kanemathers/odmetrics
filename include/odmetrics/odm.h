/**
 * @file odm.h
 */

#ifndef ODM_ODM_H
#define ODM_ODM_H

#include <pthread.h>

/* @cond */
struct metric;

typedef struct odm
{
    struct metric *metrics;
    pthread_t      server;
} odm_t;
/* @endcond */

/**
 * Initializes a new ``odm_t`` object.
 *
 * This should be called before any other ``odm_*`` functions.
 *
 * @param odm An uninitialized ``odm_t`` object.
 *
 * @return Returns 0 on success and -1 on failure.
 */
int odm_init(odm_t *odm);

/**
 * Frees the members of the ``odm_t`` object.
 *
 * ``odm_destroy()`` should be called when you're finished with odmetrics
 * to free space.
 *
 * @param odm The ``odm_t`` object to destroy.
 */
void odm_destroy(odm_t *odm);

#endif
