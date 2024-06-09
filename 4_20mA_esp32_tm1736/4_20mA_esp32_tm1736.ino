#include <Wire.h>             // ไลบรารีสำหรับการสื่อสาร I2C
#include <Adafruit_ADS1015.h> // ไลบรารีสำหรับ ADC ADS1115
#include <TM1637Display.h>    // ไลบรารีสำหรับ TM1637

// กำหนดขาสำหรับการเชื่อมต่อกับ TM1637 Display
#define CLK 19 // ขา CLK สำหรับ Display
#define DIO 18 // ขา DIO สำหรับ Display

// สร้างออบเจ็กต์สำหรับ TM1637 Display
TM1637Display display(DIO, CLK);

// สร้างออบเจ็กต์สำหรับ ADC ADS1115
Adafruit_ADS1115 ads(0x48);

void setup()
{
    Serial.begin(115200); // เริ่มต้นการสื่อสาร Serial
    Wire.begin();         // เริ่มต้นการสื่อสาร I2C

    // ตั้งค่าความสว่างของ Display
    display.setBrightness(0x0f);

    // เริ่มต้นการทำงานของ ADC
    ads.begin();
}

void loop()
{
    int16_t adc0;  // ตัวแปรสำหรับเก็บค่า ADC ที่อ่านได้
    float voltage; // ตัวแปรสำหรับเก็บค่าแรงดันที่อ่านได้
    float current; // ตัวแปรสำหรับเก็บค่ากระแสที่คำนวณได้

    // อ่านค่า ADC จากช่อง A0
    adc0 = ads.readADC_SingleEnded(0);

    // แปลงค่า ADC เป็นแรงดัน (ADS1115 มีความละเอียด 16-bit และ Vref = 4.096V)
    voltage = adc0 * (4.096 / 32767.0);

    // คำนวณค่ากระแสจากแรงดัน (4-20mA -> 1-4V)
    current = (voltage - 1.0) * (16.0 / 3.0) + 4.0;

    // แสดงค่าดีบัคบน Serial Monitor
    Serial.print("ADC Value: ");
    Serial.print(adc0);
    Serial.print("  Voltage: ");
    Serial.print(voltage, 4);
    Serial.print(" V  Current: ");
    Serial.print(current, 4);
    Serial.println(" mA");

    // ตรวจสอบแรงดัน หากน้อยกว่า 0.8V ให้แสดง "F01"
    if (voltage < 0.8)
    {
        display.showNumberDec(0xF01, false);
    }
    else
    {
        // แสดงค่ากระแสบน 7-Segment Display (แสดงเฉพาะหลัก 1, 2, และ 3)
        int displayValue = (int)current;
        display.showNumberDec(displayValue, false, 3, 1);
    }

    // หน่วงเวลา 1 วินาที
    delay(1000);
}
