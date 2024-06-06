#include <TM1637Display.h>  // ไลบรารีสำหรับการควบคุม TM1637

// กำหนดขาสำหรับการเชื่อมต่อกับ TM1637 Display
#define CLK1 25    // ขา CLK สำหรับ Display ตัวที่ 1
#define DIO1 26    // ขา DIO สำหรับ Display ตัวที่ 1

// สร้างออบเจ็กต์สำหรับ TM1637 Display
TM1637Display display1(CLK1, DIO1);

void setup() {
  // เริ่มต้นการสื่อสารกับ TM1637 Display
  display1.setBrightness(0x0f);  // ตั้งความสว่างของ Display ตัวที่ 1
}

void loop() {
  static float counter = 0.0;  // ตัวแปรสำหรับเก็บค่าที่จะนับ

  // แสดงผล counter บน 7-Segment Display โดยแสดงทศนิยม 1 ตำแหน่ง
  display1.showNumberDecEx((int)(counter * 10), 0x40, true, 4, 0);

  counter += 0.1;  // เพิ่มค่า counter ทีละ 0.1
  if (counter >= 100) {  // รีเซ็ต counter เมื่อถึง 100.0
    counter = 0;
  }

  delay(500);  // รอ 0.5 วินาที ก่อนที่จะอัพเดทค่าใหม่
}
