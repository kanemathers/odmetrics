odmetrics
=========

odmetrics - On Demand Metrics
-----------------------------

A library to provide realtime metrics, from your program, to network
attached clients.

Usage
-----

Metrics are nothing more than pointers to integers within your program. When
clients connect to the odmetrics server, your metrics are JSON encoded and
returned to the client.

This example program will run for 10 seconds, printing out the seconds
elapsed as it goes. While the program runs, those seconds will be provided
to clients at ``127.0.0.1:8090``:

    #include <stdio.h>
    #include <unistd.h>

    #include <odmetrics.h>

    int main()
    {
        odm_t odm;
        int   t;

        odm_init(&odm);
        odm_metrics_add(&odm, "uptime", &t);
        odm_serve(&odm, "127.0.0.1", "8090");

        for (t = 0; t < 10; t++)
        {
            printf("t = %d\n", t);

            sleep(1);
        }

        odm_destroy(&odm);

        return 0;
    }

Fire up another terminal and grab the metrics:

    $ nc 127.0.0.1 8090
