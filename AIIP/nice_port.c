#include "nice_port.h"
#include "hbird_sdk_soc.h"


static volatile int finish_flag = 0;

void nice_start(){
 finish_flag = 0;
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

void nice_set_len(int data){
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
  finish_flag = 1;
}

// 先初始化中断再使用等待函数
void nice_wait()
{
  while (!finish_flag)
  {
    // do nothing
  }
  finish_flag = 0;
}

void nice_irq_setup()
{
  static int inited = 0 ;
  if (!inited)
  {
    PLIC_Register_IRQ(PLIC_QSPI2_IRQn , 1 ,plic_spi2_handler);
    spi_enable_interrupt(SPI2) ;
    __enable_irq();
  }else inited = 1;
}