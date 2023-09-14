# U8g2Gauge Library

## Introduction

The U8g2Gauge library is a versatile and easy-to-use library for creating gauges on displays supported by the U8g2 library. It provides a simple way to draw gauges of different types (circle, box, line), customize their appearance, and update their data.

This library is built on top of the [U8g2](https://github.com/olikraus/u8g2) library, a well-established graphics library for monochrome displays. U8g2 supports a wide variety of LCD, OLED and eInk displays, and provides a unified API for display control, making it an excellent choice for any project that requires a display.

## Features

- **Versatile**: Supports circle, box, and line gauges.
- **Customizable**: Allows customization of gauge color, pointer length and thickness, scale ticks, and more.
- **Alerts**: Supports setting a threshold for alerts. When the data exceeds the threshold, an alert is displayed.
- **History**: Keeps a history of the last 100 data values.

## Usage

To use the U8g2Gauge library, you need to include the `U8g2Gauge.h` header file in your sketch:

```cpp
#include <U8g2Gauge.h>
```

Then you can create a `U8g2Gauge` object with your desired center point and radius:

```cpp
U8g2Gauge gauge(&u8g2, 64, 32, 30, CIRCLE);
```

The `setColor`, `setData`, `setPrecision`, `setPointer`, `setScale`, and `setThreshold` methods allow you to customize the gauge:

```cpp
gauge.setColor(WHITE);
gauge.setData(analogRead(A0), 0, 1023);
gauge.setPrecision(0);
gauge.setPointer(28, 1);
gauge.setScale(10);
gauge.setThreshold(900, RED);
```

The `draw` method draws the gauge on the display:

```cpp
u8g2.firstPage();
do {
  gauge.draw();
} while (u8g2.nextPage());
```

Please make sure to adjust the parameters according to your display and application.

## Installation

To install the U8g2Gauge library, you need to create a new folder in your Arduino libraries directory named `U8g2Gauge`, and place the `U8g2Gauge.h` and `U8g2Gauge.cpp` files inside that folder. Then you can include this library in your sketches using `#include <U8g2Gauge.h>`.

For more information on how to install and use Arduino libraries, please refer to the [Arduino Libraries Guide](https://www.arduino.cc/en/guide/libraries).

## Conclusion

The U8g2Gauge library provides a simple and flexible way to add gauges to your Arduino projects. Whether you're building a dashboard for your car, a weather station, or any other project that requires displaying data in an intuitive way, this library has got you covered. Give it a try!
