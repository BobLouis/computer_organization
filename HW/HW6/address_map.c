#include <stdio.h>
#include <stdlib.h>
#include <math.h> 


int main(){
    unsigned int cache_size;
    unsigned int block_size;
    unsigned int word_offset_size;
    unsigned int word_offset;
    unsigned int idx_size;
    unsigned int idx;
    unsigned int tag;
    unsigned int tag_size;
    unsigned int addr;
    scanf("%d%d", &cache_size, &block_size);
    word_offset_size = log2(block_size);
    idx_size = log2(cache_size/block_size);
    tag_size = 32 - word_offset_size - idx_size;
    printf("word_size: %d idx_size: %d tag_size: %d\n",word_offset_size,idx_size, tag_size);
    while(scanf("%d",&addr) != EOF){ //
        word_offset = (addr << (32-word_offset_size))>>(32-word_offset_size);
        idx = (addr << tag_size) >> (32 - idx_size);
        tag = addr >> (32 - tag_size);
        
        printf("tag: %d\n",tag);
        printf("index: %d\n",idx);
        printf("word offset: %d\n",word_offset);
    }
}