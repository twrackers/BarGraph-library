#ifndef _BAR_GRAPH__H_
#define _BAR_GRAPH__H_
 
#include <Adafruit_NeoPixel.h>
 
#ifdef __AVR__
#include <avr/power.h>
#endif
 
class BarGraph
{
  private:
    Adafruit_NeoPixel& m_mtx;
    byte m_column;
    byte m_bright;
     
  public:
    BarGraph(
      Adafruit_NeoPixel& mtx, 
      const byte column,
      const byte bright = 255U
    );
    void setValue(const bool neg, const byte val);
    void setBrightness(const byte bright);
    
    
  private:
    byte x_scale(const byte val) const;
};
 
#endif
