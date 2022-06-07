#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
int LRU[8][4];
int ful_LRU[128];
typedef struct Cache
{
    int tag;
    bool valid;
    int use;
} Cache;

void mod_LRU(int x,int idx){
    int tmp;
    if(LRU[idx][0]==x){
        return;
    }else if(LRU[idx][1] == x){
        tmp = LRU[idx][0];
        LRU[idx][0] = x;
        LRU[idx][1] = tmp;
    }else if(LRU[idx][2] == x){
        tmp = LRU[idx][0];
        LRU[idx][0] = x;
        LRU[idx][2] = LRU[idx][1];
        LRU[idx][1] = tmp;
    }else if(LRU[idx][3] == x){
        tmp = LRU[idx][0];
        LRU[idx][0] = x;
        LRU[idx][3] = LRU[idx][2];
        LRU[idx][2] = LRU[idx][1];
        LRU[idx][1] = tmp;
    }
    return ;
}

void ful_LRU_mod(int x){
    int match_idx;
    int i=1;
    int tmp;
    if(ful_LRU[0] == x)
        return;
    else{
        while(i < 128){
            if(ful_LRU[i] == x){
                match_idx = i;
                break;
            }
            ++i;   
        }
        tmp = ful_LRU[0];
        ful_LRU[0] = x;
        for(int i = match_idx; i > 1; --i){ //push back the array
            ful_LRU[i] = ful_LRU[i-1];
        }
        ful_LRU[1] = tmp;
    }
}

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
    int fully_cnt = 0;
    int fully_hit = 0;
    for(int i=0; i < 8; i++){
        LRU[i][0] = 0;
        LRU[i][1] = 1;
        LRU[i][2] = 2;
        LRU[i][3] = 3;
    }
    for (int i = 0; i < 128 ;++i){
        ful_LRU[i] = i;
    }
    Cache *cache; 
    int hit=0, miss=0;
    int cnt =0;
    float miss_rate;
    scanf("%d%d%d%d",&cache_size,&block_size,&asso,&re_al);
    word_offset_size = log2(block_size);
    if(asso==0){
        set_size = cache_size/block_size;
    }else if(asso==1){
        set_size = (cache_size/block_size)/4;
    }else if(asso==2){
        set_size = 1;

    }
    idx_size = log2(set_size);
    tag_size = 32 - word_offset_size - idx_size;
    cache = malloc(cache_size/block_size * sizeof(Cache));

    for(int i=0;i<cache_size/block_size;++i){
        cache[i].tag = 0;
        cache[i].valid = 0;
        cache[i].use = 0;
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
                if(cache[idx<<2].valid && cache[idx<<2].tag == tag){
                        ++hit;
                        printf("-1\n");
                        mod_LRU(0,idx);
                }else if(cache[(idx<<2) + 1].valid && cache[(idx<<2)+1].tag == tag){ 
                        ++hit;
                        printf("-1\n");
                        mod_LRU(1,idx);
                }else if(cache[(idx<<2) + 2].valid && cache[(idx<<2)+2].tag == tag){
                        ++hit;
                        printf("-1\n");
                        mod_LRU(2,idx);
                
                }else if(cache[(idx<<2) + 3].valid && cache[(idx<<2)+3].tag == tag){
                        ++hit;
                        printf("-1\n");
                        mod_LRU(3,idx);
                }
                else{
                    if(cache[idx<<2].valid==0){
                        ++miss;
                        cache[idx<<2].tag = tag;
                        cache[idx<<2].valid = true;
                        printf("-1\n");
                        mod_LRU(0,idx);
                    }else if(cache[(idx<<2)+1].valid==0){
                        ++miss;
                        cache[(idx<<2)+1].tag = tag;
                        cache[(idx<<2)+1].valid = true;
                        printf("-1\n");
                        mod_LRU(1,idx);
                    }else if(cache[(idx<<2)+2].valid==0){
                        ++miss;
                        cache[(idx<<2)+2].tag = tag;
                        cache[(idx<<2)+2].valid = true;
                        printf("-1\n");
                        mod_LRU(2,idx);
                    }else if(cache[(idx<<2)+3].valid==0){
                        ++miss;
                        cache[(idx<<2)+3].tag = tag;
                        cache[(idx<<2)+3].valid = true;
                        printf("-1\n");
                        mod_LRU(3,idx);
                    }else{//change the victim
                        ++miss;
                        printf("%d\n", cache[(idx<<2)+LRU[idx][3]].tag);//Least recent used
                        cache[(idx<<2)+LRU[idx][3]].tag = tag;
                        mod_LRU(LRU[idx][3],idx);
                    }
                }
            break; 

            case 2:
                fully_hit = 0;
                fully_cnt = 0;
                while(fully_cnt<(cache_size/block_size)){//search for hit
                    if(cache[fully_cnt].valid && cache[fully_cnt].tag == tag){
                        ++hit;
                        printf("-1\n");
                        // printf("-1 read hit%d\n",fully_cnt);
                        fully_hit = 1;
                        ful_LRU_mod(fully_cnt);
                        break;
                    } 
                    fully_cnt++;
                }
                fully_cnt = 0;
                if(fully_hit == 0){
                    while(fully_cnt<128){//write the block
                        if(cache[fully_cnt].valid == 0){
                            ++miss;
                            printf("-1\n");
                            // printf("-1 write %d\n",fully_cnt);
                            cache[fully_cnt].tag = tag;
                            cache[fully_cnt].valid = 1;
                            ful_LRU_mod(fully_cnt);
                            fully_hit = 1;
                            break;
                        } 
                        fully_cnt++;
                    }
                }

                if(fully_hit == 0){//replace the least used
                    ++miss;
                    printf("%d\n", cache[ful_LRU[127]].tag);//Least recent used
                    cache[ful_LRU[127]].tag = tag;
                    ful_LRU_mod(ful_LRU[127]);
                } 

            break; 

            default:


            break; 
        }
        ++cnt;
    }
    // printf("miss %d cnt%d\n", miss,cnt);
    // printf("word %d idx_size%d tag_size%d\n",word_offset_size,idx_size, tag_size);
    miss_rate = (float)miss / (float)cnt;
    printf("Miss rate = %f\n",miss_rate);
    return 0;
}