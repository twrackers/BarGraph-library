#include "BarGraph.h"
 
static byte green_bkgd = 7;
 
BarGraph::BarGraph(Adafruit_NeoPixel& mtx, const byte column) :
  m_mtx(mtx), m_column(column % 8)
{
  for (byte i = 0; i < 8; ++i) {
    m_mtx.setPixelColor(
      m_column * 8 + i, 
      mtx.Color(0, green_bkgd, 0)
    );
  }
}
 
void BarGraph::setValue(const bool neg, const byte val)
{
  byte w = (val >> 5);
  byte f = (val & 0x1F) << 3;
  byte r = m_column << 3;
  uint32_t c1 = neg
    ? m_mtx.Color(255, green_bkgd, 0) 
    : m_mtx.Color(0, green_bkgd, 255);
  uint32_t c2 = neg
    ? m_mtx.Color(f, green_bkgd, 0)
    : m_mtx.Color(0, green_bkgd, f);
  for (int i = 0; i < w; ++i) {
    m_mtx.setPixelColor(r + i, c1);
  }
  m_mtx.setPixelColor(r + w, c2);
  for (int i = (w + 1); i < 8; ++i) {
    m_mtx.setPixelColor(r + i, m_mtx.Color(0, green_bkgd, 0));
  }
}
