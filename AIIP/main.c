// See LICENSE for license details.
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "hbird_sdk_soc.h"

void print_misa(void)
{
    CSR_MISA_Type misa_bits = (CSR_MISA_Type) __RV_CSR_READ(CSR_MISA);
    static char misa_chars[30];
    uint8_t index = 0;
    if (misa_bits.b.mxl == 1) {
        misa_chars[index++] = '3';
        misa_chars[index++] = '2';
    } else if (misa_bits.b.mxl == 2) {
        misa_chars[index++] = '6';
        misa_chars[index++] = '4';
    } else if (misa_bits.b.mxl == 3) {
        misa_chars[index++] = '1';
        misa_chars[index++] = '2';
        misa_chars[index++] = '8';
    }
    if (misa_bits.b.i) {
        misa_chars[index++] = 'I';
    }
    if (misa_bits.b.m) {
        misa_chars[index++] = 'M';
    }
    if (misa_bits.b.a) {
        misa_chars[index++] = 'A';
    }
    if (misa_bits.b.b) {
        misa_chars[index++] = 'B';
    }
    if (misa_bits.b.c) {
        misa_chars[index++] = 'C';
    }
    if (misa_bits.b.e) {
        misa_chars[index++] = 'E';
    }
    if (misa_bits.b.f) {
        misa_chars[index++] = 'F';
    }
    if (misa_bits.b.d) {
        misa_chars[index++] = 'D';
    }
    if (misa_bits.b.q) {
        misa_chars[index++] = 'Q';
    }
    if (misa_bits.b.h) {
        misa_chars[index++] = 'H';
    }
    if (misa_bits.b.j) {
        misa_chars[index++] = 'J';
    }
    if (misa_bits.b.l) {
        misa_chars[index++] = 'L';
    }
    if (misa_bits.b.n) {
        misa_chars[index++] = 'N';
    }
    if (misa_bits.b.s) {
        misa_chars[index++] = 'S';
    }
    if (misa_bits.b.p) {
        misa_chars[index++] = 'P';
    }
    if (misa_bits.b.t) {
        misa_chars[index++] = 'T';
    }
    if (misa_bits.b.u) {
        misa_chars[index++] = 'U';
    }
    if (misa_bits.b.x) {
        misa_chars[index++] = 'X';
    }

    misa_chars[index++] = '\0';

    printf("MISA: RV%s\r\n", misa_chars);
}

void nice_conv(){
 int zero = 0 ;
 asm volatile (
     ".insn r 0x5b, 0, 0, x0, x0, x0"
     :"=r"(zero)
 //    :"r"(src_addr),"r"(dst_addr)
   );
}

//void nice_clear(int *src_addr , int *dst_addr){
void nice_clear(){
 int zero = 0 ;
 asm volatile (
     ".insn r 0x5b, 0, 3, x0, x0, x0"
     :"=r"(zero)
 //    :"r"(src_addr),"r"(dst_addr)
   );
}

void nice_length(int data ){
 int zero = 0 ;
 asm volatile (
     ".insn r 0x5b, 2, 4, x0, %1, x0"
     :"=r"(zero)
     :"r"(data)
   );
}

void nice_en_a(int data , int mask){
 int zero = 0 ;
 asm volatile (
     ".insn r 0x5b, 3, 5, x0, %1, %2"
     :"=r"(zero)
     :"r"(data),"r"(mask)
   );
}

void nice_en_b(int data , int mask){
 int zero = 0 ;
 asm volatile (
     ".insn r 0x5b, 3, 6, x0, %1, %2"
     :"=r"(zero)
     :"r"(data),"r"(mask)
   );
}

int nice_read(){
 int data = 0 ;
 asm volatile (
     ".insn r 0x5b, 4, 7, %0, x0, x0"
     :"=r"(data)
   );
 return data ;
}

void nice_irq(){
 int zero = 0 ;
 asm volatile (
     ".insn r 0x5b, 0, 7, x0, x0, x0"
     :"=r"(zero)
 //    :"r"(src_addr),"r"(dst_addr)
   );
}

void plic_spi2_handler(void)
{
	//clear intetupt
//	unsigned int * isr_r ;
//	isr_R = (unsigned int *) ISR ;
//	*isr_r= 0xffffffff ;

	printf("Enter interruptr\n");
	for(int i = 0 ; i<32 ; i++){
	    int data = nice_read();
	    printf("read conv-%d = %d \r\n", i , data) ;
	}

}


int main(void)
{

//	spi_disable_interrupt(SPI2);
	PLIC_Register_IRQ(PLIC_QSPI2_IRQn , 1 ,plic_spi2_handler);
	spi_enable_interrupt(SPI2) ;
	__enable_irq();

    srand(__get_rv_cycle()  | __get_rv_instret() | __RV_CSR_READ(CSR_MCYCLE));
    uint32_t rval = rand();
    rv_csr_t misa = __RV_CSR_READ(CSR_MISA);

    printf("MISA: 0x%lx\r\n", misa);
    print_misa();

//    nice_irq();
//    printf("irq over!\r\n");

    nice_clear() ;
    printf("clear over!\r\n");

    nice_length(50);
    printf("length over!\r\n");

    int mask = 0x00000001 ;

    for(int j = 0 ; j < 32 ; j++) {
    	for(int i = 0 ; i < 50 ; i++) {
    	    nice_en_a((i+1)+j,mask);
//    	    printf("en_a_%d over!\r\n",i);
    	}
    	mask = mask << 1 ;
    }
    printf("en_a over!\r\n");
    mask = 0x00000001 ;
    for(int j = 0 ; j < 32 ; j++) {
        for(int i = 0 ; i < 50 ; i++) {
            nice_en_b(256*j,mask);
//            printf("en_b_%d over!\r\n",i);
        }
        mask = mask << 1 ;
    }
    printf("en_b over!\r\n");

    nice_conv();
    printf("conv over!\r\n");

    mask = 0x00000001 ;
    for(int j = 0 ; j < 32 ; j++) {
        	for(int i = 0 ; i < 50 ; i++) {
        	    nice_en_a((i+1)+j,mask);
//        	    printf("en_a_%d over!\r\n",i);
        	}
        	mask = mask << 1 ;
    }
    printf("en_a over!\r\n");

    nice_conv();
    printf("conv over!\r\n");


    nice_clear() ;
    printf("clear over!\r\n");

    return 0;
}

