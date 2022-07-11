/*
 * Project IoT_Timer
 * Description: Timer for Capstone
 * Author: Aiden K
 * Date: 7/8/22
 */

#include "oled-wing-adafruit.h"
#include <blynk.h>

SYSTEM_THREAD(ENABLED);
SYSTEM_MODE(MANUAL);

OledWingAdafruit display;

int timer;

unsigned long time0;
unsigned long time1;
int time2;
int time3;
int time4;
int time5;

int buzz = 0;

#define BUZZER D5

/*
BLYNK_WRITE(V0)
{
  if (param.asInt() == 1)
  {
    timer = 0;
    buzz = 0;
  }
}*/

void setup()
{
  //Blynk.begin("AgpJ0l5zuN9rrmXhaTP0SSHYthleTkPV", IPAddress(167, 172, 234, 162), 8080);

  pinMode(BUZZER, OUTPUT);

  display.setup();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.display();
}

void loop()
{

  display.loop();
  //Blynk.run();

  if (display.pressedA())
  {
    timer = timer + 60000;
    buzz = 1;
  }
  else if (display.pressedB())
  {
    timer = timer + 300000;
    buzz = 1;
  }
  else if (display.pressedC())
  {
    timer = timer + 600000;
    buzz = 1;
  }

  time0 = time1;
  time1 = millis();
  time2 = time1 - time0;

  timer = timer - time2;

  if (timer < 1)
  {
    if (buzz == 1)
    {
          tone(BUZZER, 1000, 3000);
          buzz = 0;
    }

    timer = 0;
  }

  display.setCursor(0, 0);
  display.clearDisplay();

  time3 = int(timer) / 1000;
  time4 = time3 % 60;
  time5 = floor(time3 / 60);
  display.println("Timer:");
  display.print(time5);
  display.print(":");
  display.println(time4);
  display.display();
}