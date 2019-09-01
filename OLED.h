#ifndef OLED_H
#define OLED_h
#include<Arduino.h>

#ifdef OLED_AFX_H
#error "Only oled or oled_afx can be used"
#endif

#define  WIDTH 128
#define HEIGHT 64

#define SCL D1
#define SDA D2

#define OLED_RESET -1 

class OLED
{
    
    public:
    OLED();
    void SetUp();
    void Loop();
    void Clear();
    void DisplayText(String text, bool isClear);
    void DisplayScrollText(String text, bool isClear);
    void  getDisplay(){return;} // It should return display class object


};


#endif