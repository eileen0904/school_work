#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h>
#define MAX 500
#define MAX_THREAD 8
/*
測試發現,thread數等於core數的結果會最好,
因為老師的電腦是四核+hyper thread,
所以這邊MAX_THREAD設為8
*/
double matrix1[MAX][MAX], matrix2[MAX][MAX], matrix3[MAX][MAX];

void trans(double matrix1[][MAX]) {
    double x;
    int i, j;
    for (i = 0; i < MAX; i++) {
        for (j = i+1; j < MAX; j++) {
            x = matrix1[i][j];
            matrix1[i][j] = matrix1[j][i];
            matrix1[j][i] = x;
        }
    }
}

void* multiply(void* arg) {
    int id = *((int*)arg);
    int st = id * MAX / MAX_THREAD;
    int ed = (id + 1) * MAX / MAX_THREAD - 1;
    int i, j, k;
    for (i = st; i <= ed; i++) {
        for (j = 0; j < MAX; j++) {
            double sum = 0;
            for (k = 0; k < MAX; k++) {
                sum += matrix1[i][k] * matrix2[j][k];
            }
            matrix3[i][j] = sum;
        }
    }
    return NULL;
}

int main() {
    int raw, col, i = 0, j = 0, k = 0, x = 0;
    float val;
    char infilename[20], outfilename[20];
    FILE *infile, *outfile;
    struct timeval tp_s, tp_e;
    struct timezone tzp_s, tzp_e;
    for (i = 0; i < raw; i++) {
        for (j = 0; j < col; j++)
            matrix1[i][j] = matrix2[i][j] = matrix3[i][j] = 0;
    }
    gettimeofday(&tp_s, &tzp_s);
    for (x = 0; x < 1000; x++) {
        sprintf(infilename, "in%d.txt", x + 1);
        sprintf(outfilename, "out%d.txt", x + 1);
        if ((infile = fopen(infilename, "r")) == NULL)
            perror("in open error~\n");
        fscanf(infile, "%d", &raw);
        fscanf(infile, "%d", &col);
        printf("%d\n", x);
        for (i = 0; i < raw; i++)  // set matrix value
        {
            for (j = 0; j < col; j++) {
                fscanf(infile, "%f", &val);
                matrix1[i][j] = matrix2[i][j] = val;
            }
        }
        trans(matrix2);
        pthread_t* threads;
        threads = (pthread_t*)malloc(MAX_THREAD * sizeof(pthread_t));
        /*
        for (i = 0; i < raw; i++)  // matrix1's raw
        {
            for (j = 0; j < col; j++)  // matrix2's col
            {
                val = 0;
                for (k = 0; k < raw; k++)  // matrix2's raw
                {
                    val += matrix1[i][k] * matrix2[k][j];
                }
                matrix3[i][j] = val;
            }
        }
        */
        for (int i = 0; i < MAX_THREAD; i++) {
            int* p = (int*)malloc(sizeof(int));
            *p = i;
            pthread_create(&threads[i], NULL, multiply, (void*)(p));
        }
        for (i = 0; i < MAX_THREAD; i++) {
            pthread_join(threads[i], NULL);
        }
        if ((outfile = fopen(outfilename, "w")) == NULL)
            perror("out open error~\n");
        fprintf(outfile, "%d\n%d\n", raw, col);
        for (i = 0; i < raw; i++) {
            for (j = 0; j < col; j++, val++)
                fprintf(outfile, "%f\n", matrix3[i][j]);
        }
        fclose(infile);
        fclose(outfile);
    }
    gettimeofday(&tp_e, &tzp_e);
    if ((outfile = fopen("time.txt", "w")) == NULL)
        perror("out open error~\n");
    fprintf(outfile, "Total execution time =%ld\n", tp_e.tv_sec - tp_s.tv_sec);
    fclose(outfile);
}
