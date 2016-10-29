#ifndef __TOUCH_H__
#define __TOUCH_H__


void Touch ();

void Show_Touch(unsigned int x,unsigned int y,unsigned int Color);

void   ADS7846_Initial(void);


unsigned int Read_ADS7846_x(void);


unsigned int Read_ADS7846_y(void);


void   Write_ADS7846(unsigned char x);


int  GUI_TOUCH_X_MeasureX(void) ;

int  GUI_TOUCH_X_MeasureY(void) ;

#endif

