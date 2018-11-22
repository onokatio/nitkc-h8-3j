#define MIC     0
#define SPEAKER 1

extern void da_init();
extern void da_out(unsigned char ch, unsigned char val);
extern void da_stop(unsigned char ch);
extern void speaker_switch(int mode);
