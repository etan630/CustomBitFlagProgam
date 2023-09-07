#include <stdio.h>
#include <stdlib.h>
#include "bit_flags.h"

const int BIT_SIZE = sizeof(unsigned int)*8;

struct bitflag
{
    int size;
    int capacity;
    int* bit;
};
typedef struct bitflag Bitflag;


BIT_FLAGS bit_flags_init_number_of_bits(int number_of_bits)
{
    Bitflag *pBit = NULL;
    pBit = (Bitflag*)malloc(sizeof(Bitflag));
    
    //if pBit failed to allocate memory
    if (pBit == NULL)
    {
        printf("vector_init failed -- will return NULL\n");
        return NULL;
    }
    
    //needs to have bits > 0 to set size
    if (number_of_bits < 0)
    {
        printf("number_of_bits is invalid -- will return NULL\n");
        return NULL;
    }
    
    //initialize size
    pBit->size = number_of_bits;
    //initialize capacity
    pBit->capacity = BIT_SIZE;
    
    //since bit is a pointer -- and want to allocate based on how much capacity you have
    pBit->bit = (int*)calloc(pBit->capacity, sizeof(int));
    if (pBit->bit == NULL)
    {
        free(pBit); //to clean up after second fail
        printf("bit_flag_init_number_of_bits failed to create an internal array -- will return NULL\n");
        return NULL;
    }
    
    //part of the postcondition states that all flags are set at zero
    //*pBit->bit = 0; dont actually need this because used calloc which automatically sets everything to 0
    
    return pBit;
}


Status bit_flags_set_flag(BIT_FLAGS hBit_flags, int flag_position)
{
    Bitflag* pBit = (Bitflag*) hBit_flags;
    int *temp;
    int i;
    
    if (flag_position < 0)
    {
        printf("flag_position is nonexistant\n");
        return FAILURE;
    }
    
    //resize if the size is smaller than the flag_position that you want to set
    if (flag_position >= pBit->size)
    {
        if (flag_position >= pBit->capacity) //resizing to make capacity bigger
        {
            temp = (int*)malloc(pBit->capacity * 2 * sizeof(int));
            if (temp == NULL)
            {
                return FAILURE;
            }
            
            //copying data over to temp
            for (i = 0; i < pBit->size; i++)
            {
                temp[i] = pBit->bit[i];
            }
            
            //free because it's already copied and not needed anymore
            free(pBit->bit);
            //don't free temp because then it will erase the data just created
            pBit->bit = temp;
            pBit->capacity *= 2;
        }
        pBit->size = flag_position + 1;
    }
    
    int index = flag_position / BIT_SIZE;
    int num = 1 << (flag_position % BIT_SIZE);
    
    pBit->bit[index] |= num; //will change the specific index and place the bit to the flag position using bitwise or
    
    return SUCCESS;
}


Status bit_flags_unset_flag(BIT_FLAGS hBit_flags, int flag_position)
{
    Bitflag* pBit = (Bitflag*) hBit_flags;
    int *temp;
    int i;
    
    if (flag_position < 0)
    {
        printf("flag_position is nonexistant\n");
        return FAILURE;
    }
    
    //resize if flag_position is out of the bounds of what you already have
    if (flag_position >= pBit->size || flag_position >= pBit->capacity)
    {
        if (pBit->size < (pBit->capacity / 4)) //resizing capacity to make it smaller -- underutelized array
        {
            temp = (int*)malloc(pBit->capacity / 2 * sizeof(int));
            if (temp == NULL)
            {
                return FAILURE;
            }
            
            //copying data over
            for (i = 0; i < pBit->size; i++)
            {
                temp[i] = pBit->bit[i];
            }
            
            free(pBit->bit);
            pBit->bit = temp;
            pBit->capacity /= 2; //will half the flag
        }
        pBit->size = flag_position + 1;
    }
    
    int index = flag_position / BIT_SIZE;
    int num = 1 << (flag_position % BIT_SIZE);
    num = ~num; //reverses all of the 1s to 0s and 0s to 1s. This will allow the program to unset the flat with &
    
    pBit->bit[index] &= num;
  
    return SUCCESS;
}


int bit_flags_check_flag(BIT_FLAGS hBit_flags, int flag_position)
{
    Bitflag* pBit = (Bitflag*) hBit_flags;
    int bit;
    
    if (flag_position >= pBit->size || flag_position < 0)
    {
        printf("flag_position is nonexistant -- returning -1\n");
        return -1;
    }
    
    int index = flag_position / BIT_SIZE;
    int num = 1 << flag_position % BIT_SIZE;
    bit = pBit->bit[index] & num; //will get bit and see if its a 0 or 1
    
    if (bit == 0) //if the bit is 0 itll return 0
    {
        return 0;
    }
    else
    {
        return 1; //if the bit is 1 itll return 1
    }
}


int bit_flags_get_size(BIT_FLAGS hBit_flags)
{
    Bitflag* pBit = (Bitflag*) hBit_flags;
    
    return pBit->size;
}


int bit_flags_get_capacity(BIT_FLAGS hBit_flags)
{
    Bitflag* pBit = (Bitflag*) hBit_flags;
    return pBit->capacity;
}


void bit_flags_destroy(BIT_FLAGS* phBit_flags)
{
    Bitflag* pBit = (Bitflag*) *phBit_flags;
    free(pBit->bit);
    pBit->bit = NULL;
    
    free(pBit);
    *phBit_flags = NULL;
}
