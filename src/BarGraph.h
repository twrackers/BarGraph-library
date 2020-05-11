#ifndef _BAR_GRAPH__H_
#define _BAR_GRAPH__H_
 
#include <Adafruit_NeoPixel.h>
 
#ifdef __AVR__
#include <avr/power.h>
#endif

/** \headerfile BarGraph.h
 *  \class BarGraph
 *  \brief Arduino class to use an Adafruit NeoMatrix as a multi-channel 
 *  bargraph.
 *  \author Thomas W. Rackers, Ph.D.
 *  \version 1.0.0
 *  
 *  This class allows an Arduino sketch to display a value (-255 to 255) on a 
 *  single column of an
 *  <a href="https://www.adafruit.com/product/1487">Adafruit NeoMatrix</a>,
 *  an 8x8 grid of NeoPixel RGB LEDs.
 *  
 *  This class was written to provide a single channel display of the power
 *  settings of one of eight channels for a model train throttle built upon an 
 *  Arduino Uno and one or two 
 *  <a href="https://www.adafruit.com/product/1438">Adafruit Motor Shields</a>.
 *  To create a multichannel display, an array of BarGraph objects is used, one 
 *  BarGraph per column.
 *  
 *  More information on this project can be found at
 *  <a 
 *  href="https://modelrailroadelectronics.blog/throttles-implementation/#power-monitor-unit">
 *  modelrailroadelectronics.blog</a>.
 */
class BarGraph
{
  private:
    Adafruit_NeoPixel& m_mtx; //!< reference to NeoPixel object
    byte m_column;            //!< column
    byte m_bright;            //!< max brightness
    
    /**
     *  \brief Scales a channel value by the max brightness.
     *  
     *  This private method takes a value, 0 to 255, and scales it relative to
     *  the current max brightness value.  If #m_bright is 255 (its maximum
     *  possible value), the returned value will be the input value unscaled.
     *  If m_bright is less than 255, the returned value will be the input 
     *  scaled by m_bright/255.
     *  
     *  \param [in] val Value to be scaled, 0 to 255
     *  \return Scaled value
     *  
     *  \details The max brightness can be set by the constructor (default is
     *  255), and changed by setBrightness().
     *  \sa setBrightness()
     */
    byte x_scale(const byte val) const;
     
  public:
    /**
     *  \brief Constructor
     *  
     *  The constructor creates an instance of a BarGraph object, assigning it
     *  to a specific column (0 to 7) of a NeoMatrix, referenced by an
     *  Adafruit_NeoPixel object.  The constructor has an optional parameter to
     *  set the maximum brightness of the pixels, 1 to 255 (default 255 for full
     *  brightness).  
     *  
     *  \note Setting the brightness setting to zero, either via 
     *  the constructor or with the setBrightness() method, will 
     *  effectively disable the BarGraph; it will always be completely dark.
     *  
     *  \param [in] mtx Reference to Adafruit_NeoPixel object
     *  \param [in] column Column number (0 to 7) assigned to BarGraph object
     *  \param [in] bright Maximum brightness (optional, default 255)
     */
    BarGraph(
      Adafruit_NeoPixel& mtx, 
      const byte column,
      const byte bright = 255U
    );
    
    /**
     *  \brief Sets value to be displayed
     *  
     *  This method sets the value to be displayed on the BarGraph.
     *  The value is specified by its magnitude (0 to 255) and sign, positive
     *  or negative.  Positive values are displayed in red, and negative in
     *  blue.  All pixels in the bar have a dim green component added in, to
     *  distinguish active bars which may be showing a zero value, from an
     *  inactive bar.
     *  
     *  Antialiasing is used to allow a full range of values to be rendered
     *  with only 8 pixels; the top illuminated pixel will be dimmed to show
     *  values within subranges of full scale (0-31, 32-63, etc.).
     *  
     *  \param [in] val Magnitude (0 to 255)
     *  \param [in] neg False for positive values, true for negative (optional,
     *  default false)
     */
    void setValue(const byte val, const bool neg = false);
    
    /**
     *  \brief Sets overall brightness
     *  
     *  This method sets the maximum brightness to be used when the bar is 
     *  displayed.
     *  
     *  If the brightness is set to less than 255, the resolution of the 
     *  anti-aliasing effect will be reduced, as a single pixel only has 256
     *  available brightness levels per color.
     *  
     *  \note the dim green background color is affected by the brightness 
     *  setting too.  If the brightness is set too low, the background will 
     *  be black.  It's recommended that the brightness be set in the range 
     *  128 to 255.
     *  
     *  \param [in] bright Maximum brightness, 0 to 255
     */
    void setBrightness(const byte bright);
};
 
#endif
