#include "BarGraph.h"

// Brightness of green background
static const byte s_greenBkgd = 7;

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
  // Set all 8 pixels in specified column to background green.
  uint32_t c = mtx.Color(0, x_scale(s_greenBkgd), 0);
  for (byte i = 0; i < 8; ++i) {
    m_mtx.setPixelColor(m_column * 8 + i, c);
  }
}
 
void BarGraph::setValue(const byte val, const bool neg)
{
  // Scale value to floating range [0, 256).
  // New value will be split into whole and fractional parts.
  byte w = (val >> 5);        // whole part, 0 to 7
  byte f = (val & 0x1F) << 3; // fractional part, 0 to 31
  // Calculate the index of the first pixel in the bar (0, 8, 16, ..., 56)
  byte r = m_column << 3;
  // Calculate the full-brightness and antialiased intensities.
  byte fg1 = x_scale(255);
  byte fg2 = x_scale(f);
  // Calculate the background intensity.
  byte bg = x_scale(s_greenBkgd);
  // Calculate the full-brightness and antialiased colors.  Background component
  // is mixed in at this point.
  uint32_t c1 = neg
    ? m_mtx.Color(fg1, bg, 0) 
    : m_mtx.Color(0, bg, fg1);
  uint32_t c2 = neg
    ? m_mtx.Color(fg2, bg, 0)
    : m_mtx.Color(0, bg, fg2);
  // Calculate the background color.
  uint32_t b = m_mtx.Color(0, bg, 0);
  // Set the pixels below the antialiased one to full brightness.
  for (int i = 0; i < w; ++i) {
    m_mtx.setPixelColor(r + i, c1);
  }
  // Set the antialiased pixel.
  m_mtx.setPixelColor(r + w, c2);
  // Set the remaining pixels to background color only.
  for (int i = (w + 1); i < 8; ++i) {
    m_mtx.setPixelColor(r + i, b);
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