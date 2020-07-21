//Photoresistor must be on "A0" PIN.
const int PIN_MOTOR_FOR_OPENING = 8;
const int PIN_MOTOR_FOR_CLOSING = 9;
const int PIN_UP_HALL_EFFECT_SENSOR = 10;
const int PIN_DOWN_HALL_EFFECT_SENSOR = 11;
const int PIN_THE_BUTTON_TO_CLOSE = 18; //must be a pin that handles interruption. For Arduino Mega 2,3,18,19,20,21.

const float MINI_ANALOG_VALUE_FROM_PHOTORESISTOR_FOR_DAYTIME = 100; //Value found by empirical method...

float analogValueFromPhotoresistor = 0;

void closingTheDoor()
{
  static boolean theDoorIsClosed = false;
  while (theDoorIsClosed == false)
  {
    if (digitalRead(PIN_DOWN_HALL_EFFECT_SENSOR) == LOW)
    {
      digitalWrite(PIN_MOTOR_FOR_CLOSING, HIGH);
      delay(2000);
    }else
    {
      theDoorIsClosed = true;
    }
  }
  
  //To compensate the water evaporation.
  digitalWrite(PIN_MOTOR_FOR_CLOSING, HIGH);
  delay(2000);
}

void openingOfTheDoor()
{
  static boolean theDoorIsOpen = false;
  while (theDoorIsOpen == false)
  {
    if (digitalRead(PIN_UP_HALL_EFFECT_SENSOR) == LOW)
    {
      digitalWrite(PIN_MOTOR_FOR_OPENING, HIGH);
      delay(2000);
    }else
    {
      theDoorIsOpen = true;
    }
  }
}

void setup()
{
   pinMode(PIN_MOTOR_FOR_OPENING,OUTPUT);
   pinMode(PIN_MOTOR_FOR_CLOSING,OUTPUT);
   pinMode(PIN_UP_HALL_EFFECT_SENSOR,INPUT);
   pinMode(PIN_DOWN_HALL_EFFECT_SENSOR,INPUT);
   pinMode(PIN_THE_BUTTON_TO_CLOSE,INPUT);
   
   attachInterrupt(digitalPinToInterrupt(PIN_THE_BUTTON_TO_CLOSE), closingTheDoor, RISING);
}


void loop()
{
  analogValueFromPhotoresistor = analogRead(A0);
  if (analogValueFromPhotoresistor > MINI_ANALOG_VALUE_FROM_PHOTORESISTOR_FOR_DAYTIME)
  {
    openingOfTheDoor();
  }
}
