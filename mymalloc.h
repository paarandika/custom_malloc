#ifndef MYMALLOC_H
#define MYMALLOC_H

struct m_block * best_fit(int);
void MyFree (void *);
void init ();
void * MyMalloc(int);
void fuse ();

#endif
