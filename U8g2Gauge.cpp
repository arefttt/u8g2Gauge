#include "U8g2Gauge.h"

U8g2Gauge::U8g2Gauge(U8G2* u8g2, int centerX, int centerY, int radius, GaugeType type) {
  this->u8g2 = u8g2;
  this->centerX = centerX;
  this->centerY = centerY;
  this->radius = radius;
  this->color = WHITE; // Default color
  this->data = 0; // Default data
  this->minVal = 0; // Default minimum value
  this->maxVal = 1023; // Default maximum value
  this->type = type;
  this->precision = 0; // Default precision
  this->pointerLength = radius - 2; // Default pointer length
  this->pointerThickness = 1; // Default pointer thickness
  this->numTicks = 10; // Default number of ticks on the scale
}

void U8g2Gauge::setColor(uint16_t color) {
  this->color = color;
}

void U8g2Gauge::setData(int data, int minVal, int maxVal) {
  this->data = data;
  this->minVal = minVal;
  this->maxVal = maxVal;

   // Add the data to the history
   history.push_back(data);

   // Limit the history size to the last 100 values
   if (history.size() > 100) {
     history.erase(history.begin());
   }
}

void U8g2Gauge::setPrecision(int precision) {
  this->precision = precision;
}

void U8g2Gauge::setPointer(int length, int thickness) {
  this->pointerLength = length;
  this->pointerThickness = thickness;
}

void U8g2Gauge::setScale(int numTicks) {
  this->numTicks = numTicks;
}

void U8g2Gauge::setThreshold(u8g2_uint_t threshold, uint16_t alertColor) {
   this->threshold = threshold;
   this->alertColor = alertColor;
}

void U8g2Gauge::draw() {
  
   u8g2->setColorIndex(color);
  
   switch (type) {
     case CIRCLE:
       // Draw the outer circle
       u8g2->drawCircle(centerX, centerY, radius);
       break;

     case BOX:
       // Draw the box
       u8g2->drawBox(centerX - radius, centerY - radius, radius * 2, radius * 2);
       break;

     case LINE:
       // Draw the line gauge
       u8g2->drawLine(centerX - radius, centerY, centerX + radius, centerY);
       break;
   }
  
   // Draw the label
   String label = String(data, precision);
   u8g2->drawStr(centerX - (u8g2->getStrWidth(label.c_str()) / 2), centerY - radius - 4, label.c_str());
  
   // Draw the gauge pointer
   int angle = map(data, minVal, maxVal, -90, 270); // Map the data to an angle
   float radian = DEG_TO_RAD * angle; // Convert the angle to radian
  
   switch (type) {
     case CIRCLE:
       {
         int x = round(centerX + (pointerLength * cos(radian)));
         int y = round(centerY + (pointerLength * sin(radian)));
         u8g2->drawLine(centerX, centerY, x, y);
       }
       break;

     case BOX:
     case LINE:
       {
         int x = round(centerX + (pointerLength * cos(radian)));
         u8g2->drawLine(centerX - radius, centerY + (radius / 4), x, centerY + (radius / 4));
       }
       break;
   }

   // Draw the scale ticks
   for (int i = 0; i < numTicks; i++) {
     float tickRadian = DEG_TO_RAD * map(i, 0, numTicks - 1, -90, 270);
     int innerTickX = round(centerX + ((radius - pointerThickness) * cos(tickRadian)));
     int innerTickY = round(centerY + ((radius - pointerThickness) * sin(tickRadian)));
     int outerTickX = round(centerX + (radius * cos(tickRadian)));
     int outerTickY = round(centerY + (radius * sin(tickRadian)));
     u8g2->drawLine(innerTickX, innerTickY, outerTickX, outerTickY);
   }

   // Check if the data exceeds the threshold
   if (data > threshold) {
     u8g2->setColorIndex(alertColor);
     u8g2->drawStr(centerX - (u8g2->getStrWidth("ALERT") / 2), centerY + radius + 10, "ALERT");
   }
}
