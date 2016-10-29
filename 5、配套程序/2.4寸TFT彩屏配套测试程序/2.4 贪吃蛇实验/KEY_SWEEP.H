
#ifndef __KEY_SWEEP_h__
#define __KEY_SWEEP_h__

#define	 Key_Up     10
#define	 Key_Down   2
#define	 Key_Left   7
#define	 Key_Right  5
#define	 Key_Return 8
#define	 Key_Enter  16
#define	 Key_0      12
#define	 Key_1      5
#define	 Key_2      9
#define	 Key_3      13
#define	 Key_4      6
#define	 Key_5      10
#define	 Key_6      14
#define	 Key_7      7
#define	 Key_8      11
#define	 Key_9      15

#define	 Key_Port   P3	  //4*4按键接口的位置  Key_Port

extern unsigned char Key_Value;
extern unsigned char Key_flag;

extern void Key (void) ;

#endif
