#include <Bounce2.h>
#include <Keyboard.h>
#include <Joystick.h>

const int pedalPin = 3;
const int buttonPin = 4;

const int gamepadButton = 31;

int previousPedalState = HIGH;
int previousButtonState = HIGH;

bool useGamePad = true;  //Default to gamepad

Bounce pedalBouncer = Bounce();
Bounce buttonBouncer = Bounce();

Joystick_ Joystick;

void setup()
{
  pinMode(pedalPin, INPUT_PULLUP);
  pinMode(buttonPin, INPUT_PULLUP);

  pedalBouncer.attach(pedalPin); pedalBouncer.interval(50);
  buttonBouncer.attach(buttonPin); pedalBouncer.interval(50);

  Joystick.begin();
  Keyboard.begin();
}

void loop()
{
  pedalBouncer.update();
  buttonBouncer.update();

  int pedalVal = pedalBouncer.read();
  int buttonVal = buttonBouncer.read();

  //Toggle device to use.
  if (buttonVal == LOW)
  {
    if (previousButtonState == HIGH)
    {
      if (useGamePad)
      {
        useGamePad = false;
        //Release Gamepad Button
        Joystick.releaseButton(gamepadButton);
      }
      else
      {
        useGamePad = true;
        //Release Keyboard Button
        Keyboard.releaseAll();
      }
      previousButtonState = LOW;
    }
    
  }
  if (buttonVal == HIGH)
  {
    if (previousButtonState == LOW)
    {
      previousButtonState = HIGH;
    }
  }
  
  if (pedalVal == LOW)
  {
    if (previousPedalState == HIGH)
    {
      if (useGamePad)
      {
        //Press Gamepad Button
        Joystick.pressButton(gamepadButton);
      }
      else
      {
        //Press Keyboard Key(s)
        Keyboard.press(KEY_F9);
      }
      previousPedalState = LOW;
    }
  }
  if (pedalVal == HIGH)
  {
    if (previousPedalState == LOW)
    {
      if (useGamePad)
      {
        //Release Gamepad Button
        Joystick.releaseButton(gamepadButton);
      }
      else
      {
        //Release Keyboard Button
        Keyboard.releaseAll();
      }

      previousPedalState = HIGH;
    }
  }
  delay(25);
}
