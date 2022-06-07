
typedef unsigned char uint8_t;
#include <stdio.h>
#include <stdlib.h>


int print_char (char val)
{
   printf ("%u : ", val);
   for (int idx = 7 ; idx >= 0 ; idx --){
       if (val & (0x01 << idx)) putchar ('1'); 
       else putchar('0');
   }
   putchar ('\n');
}

void shift_byte_array (unsigned char *byte_ptr, int byte_len, int shift_bits)
{
   while (shift_bits){
      shift_byteArray_shiftRight(byte_ptr, byte_len ,
   }
}


void shift_byteArray_shiftRight(unsigned char *byte_ptr, int byte_len, int shift_bits)
{
   uint8_t carry_bits = 0, carry_bits_copy = 0;

   for (int byte_idx = 0; byte_idx < byte_len; byte_idx ++){
      carry_bits_copy = byte_ptr[byte_idx] & ((0x01 << shift_bits) - 1);
      carry_bits_copy = carry_bits_copy << (8 - shift_bits);

      byte_ptr[byte_idx] = ((byte_ptr[byte_idx] >> shift_bits) &  ((0x01 << (8-shift_bits)) - 1)) | carry_bits;

      carry_bits = carry_bits_copy;
   }

}

void print_bytes (char *byte_ptr, int byte_len)
{
    int idx, j ;

    for (idx = 0; idx < byte_len ; idx++) {
        for (j =  8 - 1 ; j >= 0 ; j--){
           (byte_ptr[idx] & (0x1 << j)) ? putchar ('1') : putchar ('0');
           if ((j % 4) == 0) putchar (' ');
        }
        if ((idx % 8 ) == 0) putchar (' ');
    }

   putchar ('\n');

   return;
}

void
main( int argc, char **argv)
{
   unsigned char bytearray[] = { 16, 16 };
   int shift = 0;

   if (argc > 1 )
       shift = atoi (argv[1]);
   else shift = 4;
   printf ("shift  %d \n", shift);

   print_bytes ((char*)bytearray, 2);
   shift_byteArray_shiftRight (bytearray,2,shift);
   print_bytes ((char*)bytearray, 2);
}
