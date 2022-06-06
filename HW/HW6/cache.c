#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
typedef struct Cache
{
    int tag;
    bool valid;
} Cache;

int main(){
    unsigned int cache_size;
    unsigned int block_size;
    unsigned int word_offset_size;
    unsigned int word_offset;
    unsigned int idx_size;
    unsigned int idx;
    unsigned int tag;
    unsigned int tag_size;
    unsigned int asso;
    unsigned int re_al; //0 => FIFO=0, LRU =1
    unsigned int set_size;
    unsigned int addr; //word address
    Cache *cache; 
    int hit=0, miss=0;
    int cnt =0;
    float miss_rate;
    scanf("%d%d%d%d",&cache_size,&block_size,&asso,&re_al);
    set_size = cache_size/block_size;
    word_offset_size = log2(block_size);
    idx_size = log2(cache_size/block_size);
    tag_size = 32 - word_offset_size - idx_size;
    cache = malloc(cache_size * sizeof(Cache));
    for(int i=0;i<set_size;++i){
        cache[i].tag = 0;
        cache[i].valid = 0;
    }
    while(scanf("%d",&addr) != EOF){
        // printf("%d",addr);
        word_offset = (addr << (32-word_offset_size))>>(32-word_offset_size);
        idx = (addr << tag_size) >> (32 - idx_size);
        tag = addr >> (32 - tag_size);
        switch(asso){
            case 0:
                if(cache[idx].valid){
                    
                    if(cache[idx].tag == tag){
                        ++hit;
                        printf("-1\n");
                    }else{
                        ++miss;
                        printf("%d\n", cache[idx].tag);
                        cache[idx].tag = tag;
                    }
                }else{
                    ++miss;
                    printf("-1\n");
                    cache[idx].tag = tag;
                    cache[idx].valid = true;
                }
            break;    
            case 1:


            break; 

            case 2:


            break; 

            default:


            break; 
        }
        ++cnt;
    }

    miss_rate = miss/cnt;
    printf("Miss rate = %f\n",miss_rate);
    return 0;
}