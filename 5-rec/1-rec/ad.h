#define ADSTATUS() (ADCSR & 0x80)
#define ADREAD() ADDRAH

extern void ad_init();
extern void ad_start(unsigned char ch, unsigned char int_sw);
