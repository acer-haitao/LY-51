;P0口接J3，数据端口
;P2.2接 J2 B端子，表示段码锁存
;P2.3接 J2 A端子，标志位码锁存
; 这是一个9999 4位数倒计时，为了方便观察，定时时间稍短。
	LD1	BIT	P2.7
	LD2	BIT	P2.6
	LD3	BIT	P2.5
	LD4	BIT	P2.4
	LED1	BIT	P2.3
	LED2	BIT	P2.2
	LED3	BIT	P2.1
	LED4	BIT	P2.0
	BEEP	BIT	P3.6

        LATCH1 BIT P2.2
        LATCH2 BIT P2.3

	SUB		BIT	01H		;减位标志位
	BUF_LED1	EQU	24H		;LED1缓存
	BUF_LED2	EQU	25H		;LED2缓存
	BUF_LED3	EQU	26H		;LED3缓存
	BUF_LED4	EQU	27H		;LED4缓存
	BIN_LED1	EQU	28H
	BIN_LED2	EQU	29H
	BIN_LED3	EQU	2AH
	BIN_LED4	EQU	2BH
	BUFF_LP	EQU	2CH


	ORG	0000H
	LJMP	MAIN
	ORG	00BH
	LJMP	TT0
	ORG	0100H

MAIN:	MOV		SP,	#40H
	MOV		A,	#00H
	MOV		IE,	#00H
	MOV		R6,	#50H
	MOV		R0,	#20H
STR0:	MOV		@R0,	A
	INC		R0
	NOP
	DJNZ		R6,	STR0
	MOV		P1,#0FFH
	MOV		P0,#0FFH
	MOV		P2,#80H
	MOV		P3,#0FFH
	MOV		BUFF_LP,#00H
	MOV		TH0,#0FCH		;LED扫描周期1MS
	MOV		TL0,#18H
	MOV		TMOD,#01H
	mov	buf_led1,#6Fh
	mov	buf_led2,#6Fh
	mov	buf_led3,#6Fh
	mov	buf_led4,#6Fh
	MOV	BIN_LED1,#09H
	MOV	BIN_LED2,#09H
	MOV	BIN_LED3,#09H
	MOV	BIN_LED4,#09H
	SETB		EA			;1MS
	SETB		ET0
	SETB		TR0

WAIT:
        JB     SUB,SUB_L1
        LJMP WAIT
SUB_L1: MOV A,BIN_LED1
	CLR	SUB
	CJNE	A,#00H,SUB_EN
        MOV	BIN_LED1,#09
	LJMP	SUB_LED2
SUB_EN:  DEC	BIN_LED1
	 MOV	A,BIN_LED1
	 MOV	DPTR,#LED_CODE
	 MOVC	A,@A+DPTR
	 MOV	BUF_LED1,A
SUB_EN1: LJMP	WAIT
SUB_LED2:
	   MOV	BUF_LED1,#6FH
	   MOV	A,BIN_LED2
	   CJNE	A,#00H,SUB_EN2
           MOV	BIN_LED2,#09
	   LJMP	SUB_LED3
SUB_EN2: DEC	BIN_LED2
	 MOV	A,BIN_LED2
	 MOV	DPTR,#LED_CODE
	 MOVC	A,@A+DPTR
	 MOV	BUF_LED2,A
         LJMP	WAIT
SUB_LED3:
	   MOV	BUF_LED2,#6FH
	   MOV	A,BIN_LED3
	   CJNE	A,#00H,SUB_EN3
           MOV	BIN_LED3,#09
	   LJMP	SUB_LED4
SUB_EN3:  DEC	BIN_LED3
	  MOV	A,BIN_LED3
	  MOV	DPTR,#LED_CODE
	  MOVC	A,@A+DPTR
	  MOV	BUF_LED3,A
          LJMP	WAIT
SUB_LED4:
	   MOV	BUF_LED3,#6FH
	   MOV	A,BIN_LED4
	   CJNE	A,#00H,SUB_EN4
	   LJMP	SUB_LED5
SUB_EN4: DEC	BIN_LED4
	 MOV	A,BIN_LED4
	 MOV	DPTR,#LED_CODE
	 MOVC	A,@A+DPTR
	 MOV	BUF_LED4,A
         LJMP	WAIT
SUB_LED5:LJMP  MAIN

;定时器0，扫描数码管

TT0:		MOV		TH0,	#0FCH
		MOV		TL0,	#18H
		PUSH		ACC
		PUSH		PSW
		INC		BUFF_LP
		MOV		A,	BUFF_LP
		CJNE		A,	#04H,TT0_01
		MOV		BUFF_LP,#00H
TT0_01: 	MOV	A,	BUFF_LP
		RL		A
		MOV		DPTR,#LED_LOOP
		JMP		@A+DPTR
LED_LOOP:	AJMP		LED_L1
		AJMP		LED_L2
		AJMP		LED_L3
		AJMP		LED_L4
LED_L1:	       MOV P0,#11111110B
               SETB LATCH2
               CLR LATCH2
		MOV		P0,	BUF_LED4
                SETB LATCH1
                CLR LATCH1
		JMP		TT0_END
LED_L2:	       MOV P0,#11111101B
               SETB LATCH2
               CLR LATCH2
		MOV		P0,	BUF_LED3
                SETB LATCH1
                CLR LATCH1
		JMP		TT0_END
LED_L3:	       MOV P0,#11111011B
               SETB LATCH2
               CLR LATCH2
		MOV		P0,	BUF_LED2
                SETB LATCH1
                CLR LATCH1
		JMP		TT0_END
LED_L4:	       MOV P0,#11110111B
               SETB LATCH2
               CLR LATCH2
		MOV		P0,	BUF_LED1
                SETB LATCH1
                CLR LATCH1
		JMP		TT0_END
TT0_END:	INC		R2
		CJNE		R2,#100,TT0_END1
		MOV		R2,#00H
		SETB		SUB
TT0_END1:	POP		PSW
		POP      	ACC
		RETI
		NOP
		NOP
		LJMP	000H
DELAY:MOV R5,#0
D1:   MOV R6,#20
D2:   MOV R7,#248
      DJNZ R7,$
      DJNZ R6,D2
      DJNZ R5,D1
      RET

LED_CODE:      DB 3FH,06H,5BH,4FH,66H,6DH,7DH,07H,7FH,6FH


END
