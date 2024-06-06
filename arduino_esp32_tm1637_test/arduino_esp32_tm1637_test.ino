#include <TM1637Display.h> // ไลบรารีสำหรับการควบคุม TM1637

// กำหนดขาสำหรับการเชื่อมต่อกับ TM1637 Display
#define CLK1 25 // ขา CLK สำหรับ Display ตัวที่ 1
#define DIO1 26 // ขา DIO สำหรับ Display ตัวที่ 1

#define CLK2 27 // ขา CLK สำหรับ Display ตัวที่ 2
#define DIO2 14 // ขา DIO สำหรับ Display ตัวที่ 2

#define CLK3 32 // ขา CLK สำหรับ Display ตัวที่ 3
#define DIO3 33 // ขา DIO สำหรับ Display ตัวที่ 3

// สร้างออบเจ็กต์สำหรับ TM1637 Display ทั้ง 3 ตัว
TM1637Display display1(CLK1, DIO1);
TM1637Display display2(CLK2, DIO2);
TM1637Display display3(CLK3, DIO3);

void setup()
{
  // เริ่มต้นการสื่อสารกับ TM1637 Display
  display1.setBrightness(0x0f); // ตั้งความสว่างของ Display ตัวที่ 1
  display2.setBrightness(0x0f); // ตั้งความสว่างของ Display ตัวที่ 2
  display3.setBrightness(0x0f); // ตั้งความสว่างของ Display ตัวที่ 3
}

void loop()
{
  static float counter1 = 0.0; // ตัวแปรสำหรับเก็บค่าที่จะนับสำหรับ Display 1
  static int counter2 = 0;     // ตัวแปรสำหรับเก็บค่าที่จะนับสำหรับ Display 2
  static int counter3 = 0;     // ตัวแปรสำหรับเก็บค่าที่จะนับสำหรับ Display 3
  static unsigned long lastMillis1 = 0;
  static unsigned long lastMillis2 = 0;
  static unsigned long lastMillis3 = 0;

  unsigned long currentMillis = millis();

  // นับทีละ 0.1 ทุกๆ 0.5 วินาทีสำหรับ Display 1
  if (currentMillis - lastMillis1 >= 500)
  {
    lastMillis1 = currentMillis;
    display1.showNumberDecEx((int)(counter1 * 10), 0x40, true, 4, 0);
    counter1 += 0.1;
    if (counter1 >= 100)
    {
      counter1 = 0;
    }
  }

  // นับทีละ 1 ทุกๆ 0.1 วินาทีสำหรับ Display 2
  if (currentMillis - lastMillis2 >= 100)
  {
    lastMillis2 = currentMillis;
    display2.showNumberDec(counter2, true, 4, 0);
    counter2++;
    if (counter2 >= 10000)
    {
      counter2 = 0;
    }
  }

  // นับทีละ 1 ทุกๆ 2 วินาทีสำหรับ Display 3
  if (currentMillis - lastMillis3 >= 2000)
  {
    lastMillis3 = currentMillis;
    display3.showNumberDec(counter3, true, 4, 0);
    counter3++;
    if (counter3 >= 10000)
    {
      counter3 = 0;
    }
  }
}
