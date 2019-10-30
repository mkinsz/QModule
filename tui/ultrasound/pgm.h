#ifndef PGM_H
#define PGM_H

int write_pgm_file (char *name, int w, int h, unsigned char *data);
int read_pgm_file (char *name, int *w, int *h, unsigned char **data);

#endif // PGM_H
