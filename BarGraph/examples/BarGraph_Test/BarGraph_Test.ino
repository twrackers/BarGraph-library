#include <StateMachine.h>
#include <math.h>

#include "BarGraph.h"

class SineWave : public StateMachine
{
  private:
    double m_ampl;
    double m_freq;
    double m_phase;
    
  public:
    SineWave(double a, double f, double ph) :
      StateMachine(10, true),
      m_ampl(a), 
      m_freq(2.0 * M_PI * f), 
      m_phase(ph * M_PI / 180.0)
    {
    }

    virtual bool update()
    {
      return StateMachine::update();
    }

    int getValue() const
    {
      double t = (double) millis() / 1000.0;
      double y = m_ampl * sin(m_freq * t + m_phase);
      return (int) (y * 255.0);
    }
};

#define NEO_PIN 6

Adafruit_NeoPixel mtx = Adafruit_NeoPixel(64, NEO_PIN, NEO_GRB + NEO_KHZ800);
BarGraph* bars[8];
SineWave* sws[8];

void setup() 
{
  mtx.begin();
  for (byte c = 0; c < 8; ++c) {
    bars[c] = new BarGraph(mtx, c);
    sws[c] = new SineWave(1.0, 1.0 / 8.0, c * 22.5);
  }
  mtx.show();
}

void loop() 
{
  for (byte c = 0; c < 8; ++c) {
    if (sws[c]->update()) {
      int val = sws[c]->getValue();
      bool neg = false;
      if (val < 0) {
        neg = true;
        val = -val;
      }
      bars[c]->setValue(neg, (byte) val);
    }
  }
  mtx.show();
}
