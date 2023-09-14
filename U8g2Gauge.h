#ifndef Gauge_h
#define Gauge_h

#include <U8g2lib.h>

enum GaugeType {
  CIRCLE,
  BOX,
  LINE
};

class Gauge {
  private:
    U8G2* u8g2;
    int centerX, centerY, radius;
    uint16_t color;
    int data, minVal, maxVal;
    GaugeType type;
    int precision; // Number of decimal places for the label
    int pointerLength; // Length of the pointer
    int pointerThickness; // Thickness of the pointer
    int numTicks; // Number of ticks on the scale
    u8g2_uint_t threshold; // Threshold for alerts
    uint16_t alertColor; // Color for alerts
    std::vector<int> history; // History of data values

  public:
    Gauge(U8G2* u8g2, int centerX, int centerY, int radius, GaugeType type);
    void setColor(uint16_t color);
    void setData(int data, int minVal, int maxVal);
    void setPrecision(int precision);
    void setPointer(int length, int thickness);
    void setScale(int numTicks);
    void setThreshold(u8g2_uint_t threshold, uint16_t alertColor);
    void draw();
};

#endif
