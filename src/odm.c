#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "odmetrics/odm.h"
#include "odmetrics/metrics.h"
#include "odmetrics/server.h"

/* test */
#include <unistd.h>

int odm_init(odm_t *odm)
{
    odm->metrics = NULL;

    return 0;
}

void odm_destroy(odm_t *odm)
{
    odm_metrics_free(odm);
}

/* global metrics struct in users program */
struct metrics
{
    int wifi_sniffed;
    int wifi_pushed;
};

int main()
{
    struct metrics metrics;
    odm_t          odm;
    int            i;

    metrics.wifi_pushed  = 10;
    metrics.wifi_pushed += 5;
    metrics.wifi_sniffed = 7;

    odm_init(&odm);

    odm_metrics_add(&odm, "wifi_sniffed", &metrics.wifi_sniffed);
    odm_metrics_add(&odm, "wifi_pushed", &metrics.wifi_pushed);

    odm_serve(&odm, "127.0.0.1", "8000");

    for (i = 0; i < 10; i++)
    {
        metrics.wifi_pushed  += i;
        metrics.wifi_sniffed += i;

        printf("i: %d\n", i);
        sleep(1);
    }

    odm_destroy(&odm);

    return 0;
}
