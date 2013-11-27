#include "odmetrics/odm.h"
#include "odmetrics/metrics.h"

int odm_init(odm_t *odm)
{
    odm->metrics = NULL;

    return 0;
}

void odm_destroy(odm_t *odm)
{
    odm_metrics_free(odm);

    odm->metrics = NULL;
}
