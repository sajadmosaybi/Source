#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 256

void show_cpu_info()
{
    FILE *fp = fopen("/proc/cpuinfo", "r");
    if (!fp)
    {
        perror("Cannot open /proc/cpuinfo");
        return;
    }

    char buffer[BUFFER_SIZE];
    printf("\n========== CPU INFORMATION ==========\n");

    while (fgets(buffer, BUFFER_SIZE, fp))
    {
        if (strstr(buffer, "model name") ||
            strstr(buffer, "Hardware") ||
            strstr(buffer, "processor") ||
            strstr(buffer, "cpu cores"))
        {
            printf("%s", buffer);
        }
    }

    fclose(fp);
}

void show_memory_info()
{
    FILE *fp = fopen("/proc/meminfo", "r");
    if (!fp)
    {
        perror("Cannot open /proc/meminfo");
        return;
    }

    char buffer[BUFFER_SIZE];
    printf("\n========== MEMORY INFORMATION ==========\n");

    while (fgets(buffer, BUFFER_SIZE, fp))
    {
        if (strstr(buffer, "MemTotal") ||
            strstr(buffer, "MemFree") ||
            strstr(buffer, "MemAvailable") ||
            strstr(buffer, "SwapTotal") ||
            strstr(buffer, "SwapFree"))
        {
            printf("%s", buffer);
        }
    }

    fclose(fp);
}

void show_system_status()
{
    FILE *fp;
    char buffer[BUFFER_SIZE];

    printf("\n========== SYSTEM STATUS ==========\n");

    // Uptime
    fp = fopen("/proc/uptime", "r");
    if (fp)
    {
        double uptime;
        fscanf(fp, "%lf", &uptime);
        printf("Uptime: %.2f seconds\n", uptime);
        fclose(fp);
    }

    // Load Average
    fp = fopen("/proc/loadavg", "r");
    if (fp)
    {
        fgets(buffer, BUFFER_SIZE, fp);
        printf("Load Average: %s", buffer);
        fclose(fp);
    }
}

int main()
{
    printf("===== LINUX SYSTEM INFORMATION =====\n");

    show_cpu_info();
    show_memory_info();
    show_system_status();

    printf("\n=====================================\n");

    return 0;
}