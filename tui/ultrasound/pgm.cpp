#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int write_pgm_file (char *name, int w, int h, unsigned char *data)
{

    FILE *fp = nullptr;

    if (!name) return -1;
    if (!data) return -2;
    if (w < 0 || h < 0) return -3;

    fopen_s (&fp, name, "wb");
    if (!fp) return -4;

    fprintf (fp, "P5\n%d %d\n255\n", w, h);
    fwrite (data, w * h * sizeof(unsigned char), 1, fp);
    fclose (fp);

    return 0;
}

int read_pgm_file (char *name, int *w, int *h, unsigned char **data)
{
    FILE *fp = nullptr;

    if (!name) return -1;
    if (!data) return -2;
    if (!w || !h) return -3;

    fopen_s(&fp, name, "rb");
    if (!fp) return -5;

    fscanf_s (fp, "%*c%*c\n%d %d\n%*d\n", w, h);
    *data = (unsigned char *) malloc (sizeof(unsigned char) * *w * *h);
    if (!(*data)) return -4;

    fread (*data, *w * *h * sizeof(unsigned char), 1, fp);
    fclose(fp);


    return 0;
}


