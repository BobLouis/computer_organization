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
    int cache_size;
    int block_size;
    int asso;
    int re_al; //0 => FIFO=0, LRU =1
    int set_size;
    int addr; //word address
    Cache *cache; 
    int tag;
    int idx;
    int hit=0, miss=0;
    int cnt =0;
    float miss_rate;
    scanf("%d%d%d%d",&cache_size,&block_size,&asso,&re_al);
    set_size = cache_size/block_size;

    cache = malloc(cache_size * sizeof(Cache));
    for(int i=0;i<cache_size;++i){
        cache[i].tag = 0;
        cache[i].valid = 0;
    }
    while(scanf("%d",&addr) != EOF){
        // printf("%d",addr);
        idx = addr % set_size;
        tag = addr >> (int)log2(set_size)+(int)log2(block_size);
        switch(asso){
            case 0:
                if(cache[idx].valid){
                    printf("%d\n", cache[idx].tag);
                    if(cache[idx].tag == tag){
                        ++hit;
                        continue;
                    }else{
                        ++miss;
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