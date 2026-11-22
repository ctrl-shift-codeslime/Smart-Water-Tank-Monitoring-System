#include <stdio.h>

int isValid(float level) {
    return (level >= 0 && level <= 100);
}

void showRecommendation(float level) {
    printf("Water Level    : %.2f%%\n", level);
    if (level < 25) {
        printf("Recommendation : START FILLING / LOW LEVEL\n");
    } else if (level < 90) {
        printf("Recommendation : MONITOR LEVEL\n");
    } else {
        printf("Recommendation : STOP PUMP / TANK NEAR FULL\n");
    }
}

int main() {
    float levels[10];
    int n, i, fillCount;
    char choice;
    FILE *fp;

    printf("=== Smart Water Tank Monitoring System ===\n");
    printf("(Note: Pump actions are recommendations only)\n");

    do {
        fillCount = 0;

        printf("\nEnter number of tanks (1-10): ");
        scanf("%d", &n);
        while (n < 1 || n > 10) {
            printf("Invalid! Enter number of tanks (1-10): ");
            scanf("%d", &n);
        }

        for (i = 0; i < n; i++) {
            printf("Enter water level for Tank %d (0-100%%): ", i + 1);
            scanf("%f", &levels[i]);

            while (!isValid(levels[i])) {
                printf("Invalid input! Re-enter level (0-100%%): ");
                scanf("%f", &levels[i]);
            }

            if (levels[i] < 25) {
                fillCount++;
            }
        }

        fp = fopen("report.txt", "a");
        printf("\n--- Monitoring Report ---\n");
        for (i = 0; i < n; i++) {
            printf("\nTank %d:\n", i + 1);
            showRecommendation(levels[i]);

            if (fp != NULL) {
                fprintf(fp, "Tank %d | Level: %.2f%% | ", i + 1, levels[i]);
                if (levels[i] < 25)
                    fprintf(fp, "START FILLING / LOW LEVEL\n");
                else if (levels[i] < 90)
                    fprintf(fp, "MONITOR LEVEL\n");
                else
                    fprintf(fp, "STOP PUMP / TANK NEAR FULL\n");
            }
        }
        if (fp != NULL) {
            fprintf(fp, "Tanks needing filling: %d\n\n", fillCount);
            fclose(fp);
        }

        printf("\nTanks needing filling: %d\n", fillCount);
        printf("Check again? (y/n): ");
        scanf(" %c", &choice);

    } while (choice == 'y' || choice == 'Y');

    return 0;
}