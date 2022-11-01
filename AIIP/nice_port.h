#ifndef __NICE_PORT_H__
#define __NICE_PORT_H__

void nice_start(void);
void nice_clear(void);
void nice_set_len(int data);
void nice_en_a(int data , int mask);
void nice_en_b(int data , int mask);
int  nice_read(void);
void nice_irq(void);
void nice_wait(void);

#endif
