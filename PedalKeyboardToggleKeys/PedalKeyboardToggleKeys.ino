#include <Bounce2.h>
#include <Keyboard.h>

const int pedalPin = 3;
const int keyArraySize = 2;
const char keyArray[keyArraySize] = "12";

int previousPedalState = HIGH;
int arrayPosition = 0;

Bounce pedalBouncer = Bounce();

void setup()
{
  pinMode(pedalPin, INPUT_PULLUP);
  pedalBouncer.attach(pedalPin); pedalBouncer.interval(50);
  Keyboard.begin();
}

void loop()
{
  pedalBouncer.update();

  int pedalVal = pedalBouncer.read();

  if (pedalVal == LOW && previousPedalState == HIGH)
  {
    //Press Keyboard Key(s) and toggle between
    Keyboard.print(keyArray[arrayPosition++]);

    //start at begining of array if end is met.
    if (arrayPosition == keyArraySize)
      arrayPosition = 0;
      
    previousPedalState = LOW;
  }
  if (pedalVal == HIGH && previousPedalState == LOW)
  {
    previousPedalState = HIGH;
  }
  delay(25);
}
