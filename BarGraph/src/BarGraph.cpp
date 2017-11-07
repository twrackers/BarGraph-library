#include "BarGraph.h"
 
static byte green_bkgd = 7;

static byte scale(const byte val, const byte sc)
{
  return (byte) ((unsigned int) val * sc / 255U);
}
 
BarGraph::BarGraph(
  Adafruit_NeoPixel& mtx, 
  const byte column,
  const byte bright
) :
  m_mtx(mtx), m_column(column % 8), m_bright(bright)
{
  for (byte i = 0; i < 8; ++i) {
    m_mtx.setPixelColor(
      m_column * 8 + i, 
      mtx.Color(0, x_scale(green_bkgd), 0)
    );
  }
}
 
void BarGraph::setValue(const bool neg, const byte val)
{
  byte w = (val >> 5);
  byte f = (val & 0x1F) << 3;
  byte r = m_column << 3;
  byte fg1 = x_scale(255);
  byte fg2 = x_scale(f); 
  byte bg = x_scale(green_bkgd);
  uint32_t c1 = neg
    ? m_mtx.Color(fg1, bg, 0) 
    : m_mtx.Color(0, bg, fg1);
  uint32_t c2 = neg
    ? m_mtx.Color(fg2, bg, 0)
    : m_mtx.Color(0, bg, fg2);
  for (int i = 0; i < w; ++i) {
    m_mtx.setPixelColor(r + i, c1);
  }
  m_mtx.setPixelColor(r + w, c2);
  for (int i = (w + 1); i < 8; ++i) {
    m_mtx.setPixelColor(r + i, m_mtx.Color(0, bg, 0));
  }
}

void BarGraph::setBrightness(const byte bright)
{
  m_bright = bright;
}

byte BarGraph::x_scale(const byte val) const
{
  return (byte) ((unsigned int) val * m_bright / 255U);
}