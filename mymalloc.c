#include<stdio.h>
#include<string.h>
#include "mymalloc.h"

#define c_size sizeof(char)
#define min_blk_size 10
typedef struct m_block *nxt_block;
typedef struct m_block memBlk;

char main_mem[20000/c_size];

struct m_block {
	unsigned int b_size;
	nxt_block next;
	unsigned int isFree;
};

#define blk_size sizeof(struct m_block)

void init (){;
    if((*(struct m_block *)main_mem).b_size==0){
        memBlk temp={.b_size=20000,.next=0,.isFree=1};
        memcpy(main_mem,&temp,sizeof(temp));
    }
}

void * MyMalloc(int bsize){
    init();
    nxt_block cur_point=best_fit(bsize);
    memBlk current=*cur_point;

    if (current.b_size<bsize+blk_size || current.isFree==0){
        return 0;
    }else{
        if(current.b_size-(bsize+blk_size)>=min_blk_size){
            memBlk temp={.b_size=current.b_size-(bsize+blk_size), .next=current.next,.isFree=1};
            memcpy(((void *)cur_point+bsize+blk_size),&temp,sizeof(temp));
            (*cur_point).next=(struct m_block *)((void *)cur_point+bsize+blk_size);
            (*cur_point).b_size=bsize;
        }
        (*cur_point).isFree=0;
        return (void *)((void *)cur_point+blk_size);
    }
}

void MyFree (void *ptr){
    (*(struct m_block *)((void *)ptr-blk_size)).isFree=1;
    fuse();
}

struct m_block * best_fit(int bsize){

    nxt_block cur_point=(struct m_block *)&main_mem;
    memBlk current=*(struct m_block *)main_mem;
    nxt_block out=0;
    while (current.next!=0){
            if(current.b_size>=bsize+blk_size && current.isFree==1){
                if(out==0){
                     out=cur_point;
                }
                if(out!=0 && (*out).b_size>current.b_size){
                    out=cur_point;
                }
                cur_point=current.next;
                current=*(current.next);
            }else{
                cur_point=current.next;
                current=*(current.next);
            }
    }

    if (out==0){
        out=cur_point;
    }
    return out;
}

void fuse (){
    memBlk current=*(struct m_block *)main_mem;
    while (current.next!=0){
        if(current.isFree==1 && (*(current.next)).isFree==1){
            if((*(current.next)).next!=0){
                current.next=(*(current.next)).next;
                current.b_size+=(*(current.next)).b_size;
                current=*(current.next);
            }else{
                current.b_size+=(*(current.next)).b_size;
                current.next=0;
            }
        }else{
            current=*(current.next);
        }

    }
}

