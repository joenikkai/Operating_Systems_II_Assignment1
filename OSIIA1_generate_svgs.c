#include "OSIIA1_threads.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void generate_gantt_svg(const char *filename)
{
    FILE *f = fopen(filename, "w");
    if (!f) return;

    int pixels_per_second = 50;
    int block_h = 80;
    int margin = 40;
    
    long total_duration = 0;
    for (int i = 0; i < RECORDS_COUNT; i++)
    {
        if (RECORDS[i]) total_duration += RECORDS[i]->duration;
    }

    int width = total_duration * pixels_per_second + 2 * margin;
    if (width < 400) width = 400; // Minimum width
    int height = 220;

    fprintf(f, "<svg width=\"%d\" height=\"%d\" xmlns=\"http://www.w3.org/2000/svg\">\n", width, height);
    fprintf(f, "<rect width=\"100%%\" height=\"100%%\" fill=\"white\"/>\n");
    fprintf(f, "<text x=\"%d\" y=\"35\" font-family=\"monospace\" font-size=\"24\" font-weight=\"bold\">Gantt Chart (SRTF)</text>\n", margin);

    long current_time = 0;
    int current_x = margin;

    for (int i = 0; i < RECORDS_COUNT; i++)
    {
        if (!RECORDS[i]) continue;

        int block_w = RECORDS[i]->duration * pixels_per_second;
        int y = 70;

        // Block
        fprintf(f, "<rect x=\"%d\" y=\"%d\" width=\"%d\" height=\"%d\" fill=\"#e1f5fe\" stroke=\"black\" stroke-width=\"2\"/>\n", current_x, y, block_w, block_h);
        
        // Rx and Px labels
        // Center text if block is wide enough, otherwise just offset
        int text_x = current_x + (block_w / 2);
        fprintf(f, "<text x=\"%d\" y=\"%d\" font-family=\"monospace\" font-size=\"14\" text-anchor=\"middle\">R%d</text>\n", text_x, y + 30, (int)RECORDS[i]->burst_time);
        fprintf(f, "<text x=\"%d\" y=\"%d\" font-family=\"monospace\" font-size=\"14\" text-anchor=\"middle\" font-weight=\"bold\">P%d</text>\n", text_x, y + 60, (int)RECORDS[i]->job_id);
        
        // Time markers
        fprintf(f, "<text x=\"%d\" y=\"%d\" font-family=\"monospace\" font-size=\"12\" text-anchor=\"middle\">%ld</text>\n", current_x, y + block_h + 20, current_time);
        
        current_time += RECORDS[i]->duration;
        current_x += block_w;

        if (i == RECORDS_COUNT - 1)
        {
            fprintf(f, "<text x=\"%d\" y=\"%d\" font-family=\"monospace\" font-size=\"12\" text-anchor=\"middle\">%ld</text>\n", current_x, y + block_h + 20, current_time);
        }
    }

    fprintf(f, "</svg>\n");
    fclose(f);
}

static int compare_completed(const void *a, const void *b)
{
    struct job_instance_record *ra = *(struct job_instance_record **)a;
    struct job_instance_record *rb = *(struct job_instance_record **)b;
    return (int)(ra->job_id - rb->job_id);
}

void generate_process_table_svg(const char *filename)
{
    FILE *f = fopen(filename, "w");
    if (!f) return;

    // First, identify unique completed jobs
    struct job_instance_record *completed[MAXIMUM_RECORDS];
    int completed_count = 0;
    for (int i = 0; i < RECORDS_COUNT; i++)
    {
        if (RECORDS[i] && RECORDS[i]->finish_time > 0)
        {
            // Check if already in list (shouldn't happen with our logic, but safe)
            int found = 0;
            for(int j=0; j<completed_count; j++) {
                if(completed[j]->job_id == RECORDS[i]->job_id) {
                    found = 1;
                    break;
                }
            }
            if(!found) completed[completed_count++] = RECORDS[i];
        }
    }

    // Sort by Process ID to match example
    if (completed_count > 0)
    {
        qsort(completed, completed_count, sizeof(struct job_instance_record *), compare_completed);
    }

    int row_h = 35;
    int col_w[] = {100, 120, 100, 100, 80, 80, 300};
    int total_w = 0;
    for(int i=0; i<7; i++) total_w += col_w[i];
    int height = (completed_count + 3) * row_h + 120;

    fprintf(f, "<svg width=\"%d\" height=\"%d\" xmlns=\"http://www.w3.org/2000/svg\">\n", total_w + 60, height);
    fprintf(f, "<rect width=\"100%%\" height=\"100%%\" fill=\"white\"/>\n");
    fprintf(f, "<text x=\"30\" y=\"40\" font-family=\"monospace\" font-size=\"24\" font-weight=\"bold\">Process Execution Summary</text>\n");
    
    char *headers[] = {"Process ID", "Arrival Time", "Burst Time", "Exit Time", "TAT", "WT", "Exit Message"};
    int y = 70;
    int start_x = 30;

    // Header
    int x = start_x;
    for(int i=0; i<7; i++) {
        fprintf(f, "<rect x=\"%d\" y=\"%d\" width=\"%d\" height=\"%d\" fill=\"#eceff1\" stroke=\"black\" stroke-width=\"1\"/>\n", x, y, col_w[i], row_h);
        fprintf(f, "<text x=\"%d\" y=\"%d\" font-family=\"monospace\" font-size=\"13\" font-weight=\"bold\">%s</text>\n", x + 5, y + 22, headers[i]);
        x += col_w[i];
    }

    double total_tat = 0, total_wt = 0;

    for(int j=0; j<completed_count; j++) {
        y += row_h;
        x = start_x;
        long tat = completed[j]->finish_time - completed[j]->arrival_time;
        long wt = tat - completed[j]->original_burst;
        total_tat += tat;
        total_wt += wt;

        char *vals[7];
        char b1[16], b2[16], b3[16], b4[16], b5[16], b6[16];
        sprintf(b1, "P%d", (int)completed[j]->job_id);
        sprintf(b2, "%ld", completed[j]->arrival_time);
        sprintf(b3, "%ld", completed[j]->original_burst);
        sprintf(b4, "%ld", completed[j]->finish_time);
        sprintf(b5, "%ld", tat);
        sprintf(b6, "%ld", wt);
        vals[0] = b1; vals[1] = b2; vals[2] = b3; vals[3] = b4; vals[4] = b5; vals[5] = b6; vals[6] = completed[j]->message;

        for(int i=0; i<7; i++) {
            fprintf(f, "<rect x=\"%d\" y=\"%d\" width=\"%d\" height=\"%d\" fill=\"none\" stroke=\"black\" stroke-width=\"1\"/>\n", x, y, col_w[i], row_h);
            fprintf(f, "<text x=\"%d\" y=\"%d\" font-family=\"monospace\" font-size=\"12\">%s</text>\n", x + 5, y + 22, vals[i]);
            x += col_w[i];
        }
    }

    if (completed_count > 0) {
        y += row_h + 30;
        fprintf(f, "<rect x=\"%d\" y=\"%d\" width=\"400\" height=\"80\" fill=\"#f9f9f9\" stroke=\"#ccc\" rx=\"5\"/>\n", start_x, y - 20);
        fprintf(f, "<text x=\"%d\" y=\"%d\" font-family=\"monospace\" font-size=\"14\" font-weight=\"bold\">Performance Metrics:</text>\n", start_x + 15, y + 5);
        fprintf(f, "<text x=\"%d\" y=\"%d\" font-family=\"monospace\" font-size=\"14\">Average TAT: %.2f s</text>\n", start_x + 15, y + 25, total_tat / completed_count);
        fprintf(f, "<text x=\"%d\" y=\"%d\" font-family=\"monospace\" font-size=\"14\">Average WT:  %.2f s</text>\n", start_x + 15, y + 45, total_wt / completed_count);
        fprintf(f, "<text x=\"%d\" y=\"%d\" font-family=\"monospace\" font-size=\"14\">Total WT:    %.2f s</text>\n", start_x + 15, y + 65, total_wt);
    }

    fprintf(f, "</svg>\n");
    fclose(f);
}

