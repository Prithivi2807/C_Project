#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Include this line

void get_cpu_cores() {
    FILE *cpuinfo = fopen("/proc/cpuinfo", "r");
    char line[256];
    int cores = 0;

    if (cpuinfo == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    while (fgets(line, sizeof(line), cpuinfo)) {
        if (strncmp(line, "processor", 9) == 0) {
            cores++;
        }
    }

    fclose(cpuinfo);

    printf("Number of CPU cores: %d\n", cores);
}

void get_memory_info() {
    FILE *meminfo = fopen("/proc/meminfo", "r");
    char line[256];
    long total_mem = 0, free_mem = 0, available_mem = 0;

    if (meminfo == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    while (fgets(line, sizeof(line), meminfo)) {
        if (sscanf(line, "MemTotal: %ld kB", &total_mem) == 1) {
            // total_mem parsed
        } else if (sscanf(line, "MemFree: %ld kB", &free_mem) == 1) {
            // free_mem parsed
        } else if (sscanf(line, "MemAvailable: %ld kB", &available_mem) == 1) {
            // available_mem parsed
        }
    }

    fclose(meminfo);

    long used_mem = total_mem - free_mem;

    printf("Total Memory: %ld kB\n", total_mem);
    printf("Used Memory: %ld kB\n", used_mem);
    printf("Free Memory: %ld kB\n", free_mem);
    printf("Available Memory: %ld kB\n", available_mem);
}

int main() {
    get_cpu_cores();
    get_memory_info();
    return 0;
}
