#include <Mouse.h>
#include <HID.h>
#include <Keyboard.h>

int horzPin = A1;  // Analog output of horizontal joystick pin
int vertPin = A0;  // Analog output of vertical joystick pin
int selPin = 5;  // select button pin of joystick
int key1Pin = 9;
int key2Pin = 8;
int vertZero, horzZero;  // Stores the initial value of each axis, usually around 512
int vertValue, horzValue;  // Stores current analog output of each axis
const int sensitivity = 250;  // Higher sensitivity value = slower mouse, should be <= about 500
int mouseClickFlag = 0;
float mash = 0.001;
void setup()
{
  pinMode(key1Pin, INPUT);
  pinMode(key2Pin, INPUT);
  pinMode(horzPin, INPUT);  // Set both analog pins as inputs
  pinMode(vertPin, INPUT);
  pinMode(selPin, INPUT);  // set button select pin as input
  digitalWrite(selPin, HIGH);  // Pull button select pin high
  delay(1000);  // short delay to let outputs settle
  vertZero = analogRead(vertPin);  // get the initial values
  horzZero = analogRead(horzPin);  // Joystick should be in neutral position when reading these
  Keyboard.begin();
}

void loop()
{
  vertValue = analogRead(vertPin) - vertZero;  // read vertical offset
  horzValue = analogRead(horzPin) - horzZero;  // read horizontal offset
  if (digitalRead(key1Pin) == 0)
  {
    Mouse.press(MOUSE_LEFT);
    Mouse.release(MOUSE_LEFT);
    delay(100);
  }
  if (digitalRead(key2Pin) == LOW)
  {
    Mouse.press(MOUSE_RIGHT);
    Mouse.release(MOUSE_RIGHT);
    delay(100);
  }
  if (vertValue != 0)
    Mouse.move(0, vertValue/sensitivity, 0);  // move mouse on y axis
  if (horzValue != 0)
    Mouse.move(-horzValue/sensitivity, 0, 0);  // move mouse on x axis
    
  if ((digitalRead(selPin) == 0) && (!mouseClickFlag))  // if the joystick button is pressed
  {
    mouseClickFlag = 1;
    Mouse.press(MOUSE_LEFT);  // click the left button down
  }
  else if ((digitalRead(selPin))&&(mouseClickFlag)) // if the joystick button is not pressed
  {
    mouseClickFlag = 0;
    Mouse.release(MOUSE_LEFT);  // release the left button
  }
}
