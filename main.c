#include <stdio.h>
#include <stdlib.h>
#include "bit_flags.h"
#define MAX_NUM 2000000000

void clear_keyboard_buffer(void);

int main(int argc, char* argv[])
{
    int i, num;
    BIT_FLAGS bit_Flag = bit_flags_init_number_of_bits(MAX_NUM + 1);
    if (bit_Flag == NULL)
    {
        exit(1);
    }
   
    scanf("%d", &num);
    clear_keyboard_buffer();
    while(num != -1)
    {
        bit_flags_set_flag(bit_Flag, num);
        scanf("%d", &num);
        clear_keyboard_buffer();
    }

    for (i = 0; i <= bit_flags_get_size(bit_Flag); i++)
    {
        if (bit_flags_check_flag(bit_Flag, i) == 1)
        {
            printf("%d\n",i);
        }
    }
    
    bit_flags_destroy(&bit_Flag);
    return 0;
}

void clear_keyboard_buffer(void)
{
    char c;
    int noc;
    do
    {
        noc = scanf("%c", &c);
    } while (noc == 1 && c != '\n');
}
