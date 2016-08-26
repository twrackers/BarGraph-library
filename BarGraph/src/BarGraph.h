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
     
  public:
    BarGraph(Adafruit_NeoPixel& mtx, const byte column);
    void setValue(const bool neg, const byte val);
};
 
#endif
