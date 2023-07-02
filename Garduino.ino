#define SENSOR_READ_DELAY 86400000   //This is the loop delay for sensor reading. Its in milli seconds. set it to 86400000 for once a day.

#define FULL_MOISTURE_READING1 207
#define NO_MOISTURE_READING1 495

#define FULL_MOISTURE_READING2 215
#define NO_MOISTURE_READING2 502

#define FULL_MOISTURE_READING3 205
#define NO_MOISTURE_READING3 507

#define CUT_OFF_MOISTURE_PERCENATGE 30

#define WATERING_TIME 7000  //This is millis


int pumpPin=2;
int pump2Pin=3;

int inputSensorPin1=A0;
int inputSensorPin2=A1;
int inputSensorPin3=A2;

void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(pumpPin,OUTPUT);
  pinMode(pump2Pin,OUTPUT);
  digitalWrite(pumpPin,HIGH);
  
}

bool getMoisturePercentageAndWaterIt(int sensorValue, int outPinNo, int wateringTime, int sensornum)
{
  int moisturePercentage;

  if (sensornum == 1) {
  sensorValue = constrain(sensorValue ,FULL_MOISTURE_READING1, NO_MOISTURE_READING1); 
  moisturePercentage = map(sensorValue, FULL_MOISTURE_READING1, NO_MOISTURE_READING1, 100, 0);
  } else if (sensornum == 2) {
  sensorValue = constrain(sensorValue ,FULL_MOISTURE_READING2, NO_MOISTURE_READING2); 
  moisturePercentage = map(sensorValue, FULL_MOISTURE_READING2, NO_MOISTURE_READING2, 100, 0);
  } else if (sensornum == 3) {
  sensorValue = constrain(sensorValue ,FULL_MOISTURE_READING3, NO_MOISTURE_READING3); 
  moisturePercentage = map(sensorValue, FULL_MOISTURE_READING3, NO_MOISTURE_READING3, 100, 0);
  }
  
  if (moisturePercentage < CUT_OFF_MOISTURE_PERCENATGE)
  {
    digitalWrite(outPinNo, LOW);
    delay(wateringTime);
    digitalWrite(outPinNo, HIGH);
    return true;
  }
  return false;
}


void loop() 
{
  // put your main code here, to run repeatedly:
  digitalWrite(pump2Pin, HIGH);

  int inputSensorPin1Value = analogRead(inputSensorPin1);
  int inputSensorPin2Value = analogRead(inputSensorPin2);
  int inputSensorPin3Value = analogRead(inputSensorPin3);

  if(!getMoisturePercentageAndWaterIt(inputSensorPin1Value, pumpPin, WATERING_TIME, 1)) {
    if(!getMoisturePercentageAndWaterIt(inputSensorPin2Value, pumpPin, WATERING_TIME, 2))
      getMoisturePercentageAndWaterIt(inputSensorPin3Value, pumpPin, WATERING_TIME, 3);
  }

  delay(SENSOR_READ_DELAY);
}