/**
 * @file metrics.h
 */

#ifndef ODM_METRICS_H
#define ODM_METRICS_H

#include "odmetrics/odm.h"
#include "odmetrics/uthash.h"

/* @cond */
struct metric
{
    const char     *key;
    int            *value;
    UT_hash_handle  hh;
};
/* @endcond */

/**
 * Add a new metric.
 *
 * Metrics are simply pointers to an integer, within your program, that
 * represent some value.
 *
 * @param key Name of the metric.
 * @param value Pointer to an integer representing your metric.
 *
 * @return Returns 0 on success and -1 on failure.
 */
int odm_metrics_add(odm_t *odm, const char *key, int *value);

/**
 * Free the allocated metrics.
 *
 */
void odm_metrics_free(odm_t *odm);

/**
 * Print the metrics to stdout.
 */
void odm_metrics_print(odm_t *odm);

/**
 * Serialize the metrics to a string.
 *
 * @return Returns the string. You must free the pointer when you've
 * finished with it.
 */
char *odm_metrics_serialize(odm_t *odm);

#endif
