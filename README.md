# arduino_esp32_tm1637
 
ได้เลยครับ นี่คือไฟล์ `README.md` ที่อธิบายโค้ดและมีตัวอย่างโค้ดพร้อมอิโมจิ:

```markdown
# 📟 ESP32 ADC to 7-Segment Display Project

โปรเจคนี้เป็นการใช้งาน ESP32 เพื่ออ่านค่า ADC จาก IC ADS1115 และแสดงผลบน 4-Digit 7-Segment Displays ที่ควบคุมผ่าน IC TM1637

## 📋 คุณสมบัติ

- อ่านค่า ADC จาก 3 ช่องของ ADS1115
- แสดงผลแรงดันไฟฟ้าบน 4-Digit 7-Segment Display สามตัว
- การแปลงค่า 4-20mA เป็น 0.5-3.3VDC

## 📁 การเชื่อมต่อฮาร์ดแวร์

### 📌 การเชื่อมต่อ TM1637 Displays
- **Display 1:**
  - CLK: GPIO 25
  - DIO: GPIO 26
- **Display 2:**
  - CLK: GPIO 27
  - DIO: GPIO 14
- **Display 3:**
  - CLK: GPIO 12
  - DIO: GPIO 13

### 📌 การเชื่อมต่อ ADS1115
- SDA: GPIO 21
- SCL: GPIO 22
- อินพุตอนาล็อก: A0, A1, A2

## 💻 การเขียนโปรแกรม

### 🧩 ไลบรารีที่ใช้
- `Wire.h` สำหรับการสื่อสาร I2C
- `Adafruit_ADS1X15.h` สำหรับการใช้งาน ADS1115
- `TM1637Display.h` สำหรับการควบคุม TM1637

### 🔧 โค้ดตัวอย่าง
```cpp
#include <Wire.h>              // ไลบรารีสำหรับการสื่อสาร I2C
#include <Adafruit_ADS1X15.h>  // ไลบรารีสำหรับการใช้งาน ADS1115
#include <TM1637Display.h>     // ไลบรารีสำหรับการควบคุม TM1637

// กำหนดขาสำหรับการเชื่อมต่อกับ TM1637 Display
#define CLK1 25    // ขา CLK สำหรับ Display ตัวที่ 1
#define DIO1 26    // ขา DIO สำหรับ Display ตัวที่ 1

#define CLK2 27    // ขา CLK สำหรับ Display ตัวที่ 2
#define DIO2 14    // ขา DIO สำหรับ Display ตัวที่ 2

#define CLK3 12    // ขา CLK สำหรับ Display ตัวที่ 3
#define DIO3 13    // ขา DIO สำหรับ Display ตัวที่ 3

// สร้างออบเจ็กต์สำหรับ TM1637 Display ทั้ง 3 ตัว
TM1637Display display1(CLK1, DIO1);
TM1637Display display2(CLK2, DIO2);
TM1637Display display3(CLK3, DIO3);

// สร้างออบเจ็กต์สำหรับ ADS1115
Adafruit_ADS1115 ads;

void setup() {
  // เริ่มต้นการสื่อสารกับ TM1637 Display
  display1.setBrightness(0x0f);  // ตั้งความสว่างของ Display ตัวที่ 1
  display2.setBrightness(0x0f);  // ตั้งความสว่างของ Display ตัวที่ 2
  display3.setBrightness(0x0f);  // ตั้งความสว่างของ Display ตัวที่ 3
  
  // เริ่มต้นการสื่อสาร I2C กับ ADS1115
  Wire.begin();
  ads.begin();
}

void loop() {
  // อ่านค่า ADC จาก ADS1115 (แต่ละช่องจะมีตัวเลขที่ต่างกันไป)
  int16_t adc0, adc1, adc2;
  adc0 = ads.readADC_SingleEnded(0); // อ่านค่า ADC ช่อง 0
  adc1 = ads.readADC_SingleEnded(1); // อ่านค่า ADC ช่อง 1
  adc2 = ads.readADC_SingleEnded(2); // อ่านค่า ADC ช่อง 2

  // แปลงค่า ADC เป็นแรงดันไฟฟ้า (หน่วย mV)
  // ค่าการแปลงขึ้นอยู่กับการตั้งค่า gain ที่เป็นค่าเริ่มต้น (GAIN_TWOTHIRDS)
  float voltage0 = (adc0 * 0.1875) / 1000.0; // แปลงค่า ADC ช่อง 0 เป็นแรงดัน
  float voltage1 = (adc1 * 0.1875) / 1000.0; // แปลงค่า ADC ช่อง 1 เป็นแรงดัน
  float voltage2 = (adc2 * 0.1875) / 1000.0; // แปลงค่า ADC ช่อง 2 เป็นแรงดัน

  // แสดงผลแรงดันไฟฟ้าบน 4-Digit 7-Segment Display โดยแสดงทศนิยม 1 ตำแหน่ง
  display1.showNumberDecEx((int)(voltage0 * 10), 0x40, true, 4, 0); // แสดงแรงดันที่ Display ตัวที่ 1
  display2.showNumberDecEx((int)(voltage1 * 10), 0x40, true, 4, 0); // แสดงแรงดันที่ Display ตัวที่ 2
  display3.showNumberDecEx((int)(voltage2 * 10), 0x40, true, 4, 0); // แสดงแรงดันที่ Display ตัวที่ 3

  delay(1000); // รอ 1 วินาที ก่อนที่จะอ่านค่าใหม่
}
```

### 📝 อธิบายโค้ด
1. **รวมไลบรารีที่จำเป็น:**
   ```cpp
   #include <Wire.h>
   #include <Adafruit_ADS1X15.h>
   #include <TM1637Display.h>
   ```

2. **กำหนดขาเชื่อมต่อของ TM1637 Display:**
   ```cpp
   #define CLK1 25
   #define DIO1 26
   #define CLK2 27
   #define DIO2 14
   #define CLK3 12
   #define DIO3 13
   ```

3. **สร้างออบเจ็กต์สำหรับ TM1637 Display และ ADS1115:**
   ```cpp
   TM1637Display display1(CLK1, DIO1);
   TM1637Display display2(CLK2, DIO2);
   TM1637Display display3(CLK3, DIO3);
   Adafruit_ADS1115 ads;
   ```

4. **ตั้งค่าในฟังก์ชัน `setup`:**
   - เริ่มต้นการสื่อสารกับ TM1637 Display และตั้งค่าความสว่าง
   - เริ่มต้นการสื่อสาร I2C กับ ADS1115
   ```cpp
   void setup() {
     display1.setBrightness(0x0f);
     display2.setBrightness(0x0f);
     display3.setBrightness(0x0f);
     Wire.begin();
     ads.begin();
   }
   ```

5. **ฟังก์ชัน `loop`:**
   - อ่านค่า ADC จาก ADS1115
   - แปลงค่า ADC เป็นแรงดันไฟฟ้า
   - แสดงผลแรงดันไฟฟ้าบน 4-Digit 7-Segment Display
   - รอ 1 วินาที ก่อนที่จะอ่านค่าใหม่
   ```cpp
   void loop() {
     int16_t adc0, adc1, adc2;
     adc0 = ads.readADC_SingleEnded(0);
     adc1 = ads.readADC_SingleEnded(1);
     adc2 = ads.readADC_SingleEnded(2);
     float voltage0 = (adc0 * 0.1875) / 1000.0;
     float voltage1 = (adc1 * 0.1875) / 1000.0;
     float voltage2 = (adc2 * 0.1875) / 1000.0;
     display1.showNumberDecEx((int)(voltage0 * 10), 0x40, true, 4, 0);
     display2.showNumberDecEx((int)(voltage1 * 10), 0x40, true, 4, 0);
     display3.showNumberDecEx((int)(voltage2 * 10), 0x40, true, 4, 0);
     delay(1000);
   }
   ```

## 📚 อ้างอิง
- [Random Nerd Tutorials](https://randomnerdtutorials.com/esp32-pinout-reference/)
- [Microcontrollers Lab](https://microcontrollerslab.com/esp32-pinout-gpio/)

```

โค้ดนี้จะช่วยให้ผู้ที่ไม่เคยเขียนโปรแกรมมาก่อนสามารถเข้าใจได้ง่ายขึ้น โดยมีคอมเม้นอธิบายทุกส่วนของโค้ดและการเชื่อมต่อฮาร์ดแวร์อย่างละเอียดครับ