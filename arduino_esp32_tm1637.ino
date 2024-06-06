#include <Wire.h>             // ไลบรารีสำหรับการสื่อสาร I2C
#include <Adafruit_ADS1X15.h> // ไลบรารีสำหรับการใช้งาน ADS1115
#include <TM1637Display.h>    // ไลบรารีสำหรับการควบคุม TM1637

// กำหนดขาสำหรับการเชื่อมต่อกับ TM1637 Display
#define CLK1 25 // ขา CLK สำหรับ Display ตัวที่ 1
#define DIO1 26 // ขา DIO สำหรับ Display ตัวที่ 1

#define CLK2 27 // ขา CLK สำหรับ Display ตัวที่ 2
#define DIO2 14 // ขา DIO สำหรับ Display ตัวที่ 2

#define CLK3 12 // ขา CLK สำหรับ Display ตัวที่ 3
#define DIO3 13 // ขา DIO สำหรับ Display ตัวที่ 3

// สร้างออบเจ็กต์สำหรับ TM1637 Display ทั้ง 3 ตัว
TM1637Display display1(CLK1, DIO1);
TM1637Display display2(CLK2, DIO2);
TM1637Display display3(CLK3, DIO3);

// สร้างออบเจ็กต์สำหรับ ADS1115
Adafruit_ADS1115 ads;

void setup()
{
    // เริ่มต้นการสื่อสารกับ TM1637 Display
    display1.setBrightness(0x0f); // ตั้งความสว่างของ Display ตัวที่ 1
    display2.setBrightness(0x0f); // ตั้งความสว่างของ Display ตัวที่ 2
    display3.setBrightness(0x0f); // ตั้งความสว่างของ Display ตัวที่ 3

    // เริ่มต้นการสื่อสาร I2C กับ ADS1115
    Wire.begin();
    ads.begin();
}

void loop()
{
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
