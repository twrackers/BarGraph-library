# BarGraph-library
This library allows an [Adafruit 8x8 NeoPixel NeoMatrix](https://www.adafruit.com/products/1487) to serve as an 8-channel two-color bar graph display.

The BarGraph class defines an object which can display a numeric value (-255 to 255) on one of the eight columns of a NeoMatrix.  An Arduino sketch can define up to eight BarGraph objects per NeoMatrix unit, one BarGraph per column.

A BarGraph's level is set by passing the magnitude (0-255) of the desired value and the value's sign.  Shading of the highest illuminated pixel in a BarGraph's pixel column allows the full resolution of 256 levels to be rendered with only 8 NeoPixels.

A pixel column which is attached to a BarGraph object will mix in a dim green background with the red or blue bar color, which will differentiate columns which are in use from those which are not when a zero value is displayed.

The BarGraph class is used to create a power-output display for my Arduino-based model railroad throttle project.  More information on this project can be found in my blog at [https://modelrailroadelectronics.blog/throttles-implementation/#power-monitor-unit](https://modelrailroadelectronics.blog/throttles-implementation/#power-monitor-unit).
