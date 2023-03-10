int microphone1Pin = A0;
int microphone2Pin = A1; 
int microphone3Pin = A2;
int microphone4Pin = A3;

const int numReadings = 10;

int micreadings1[numReadings];
int micreadings2[numReadings];
int micreadings3[numReadings];
int micreadings4[numReadings];

int targetValue = 0;
int validResponse = 0;
long readIndex = 0;

long total1 = 0;
long total2 = 0;
long total3 = 0;
long total4 = 0;

int interval = 2000;
long processedSensorValue;

unsigned long startTime, motorVibrate;
bool isMotorVibrating = false;

// How to get this? Emperically
float currentThreshold = 550;
float sensorPastAverage;

void setup() {
  Serial.begin(9600);
  pinMode(microphone1Pin, INPUT);
  pinMode(microphone2Pin, INPUT);
  pinMode(microphone3Pin, INPUT);
  pinMode(microphone4Pin, INPUT);
  startTime = millis();
  motorVibrate = 0;
}



void loop()
{
  // Get clean sensor value
  processedSensorValue = smooth();
  
  // Set threshold dynamically
  // we constantly update the dynamic threshold. If we see that the baseline
  // average increases over a period of time, we update our current threshold
  // by dynamic threshold
  
  { // 
    updateSensorPastAverage(processedSensorValue);
    if (hasCurrentThresholdDeviated())
    { 
        currentThreshold = sensorPastAverage;
    }
  }
 
  

  // what is this plotting. What is the response of the change.
  Serial.println(processedSensorValue); 

  // Check threshold and vibrate motor
  if (processedSensorValue > currentThreshold)
  {
    if (isMotorVibrating && (millis() - motorVibrate > 1000))
    {
        digitalWrite(13, LOW);
        isMotorVibrating = false;
        // stop the motor
    } else {
        digitalWrite(13, HIGH);
        isMotorVibrating = true;
        // start the motor
    }
  }
}

bool hasCurrentThresholdDeviated()
{

}

void updateSensorPastAverage(unsigned long sensorValue)
{
    // Keep taking average
    
}

long smooth()
{
 	long totaverage;
	long average1;
	long average2;
	long average3;
	long average4;

    total1 = total1 - micreadings1[readIndex];
	total2 = total2 - micreadings2[readIndex];
	total3 = total3 - micreadings3[readIndex];
	total4 = total4 - micreadings4[readIndex];

    micreadings1[readIndex] = analogRead(microphone1Pin);
	micreadings2[readIndex] = analogRead(microphone2Pin);
	micreadings3[readIndex] = analogRead(microphone3Pin);
	micreadings4[readIndex] = analogRead(microphone4Pin);

    total1 = total1 + micreadings1[readIndex];
	total2 = total2 + micreadings2[readIndex];
	total3 = total3 + micreadings3[readIndex];
	total4 = total4 + micreadings4[readIndex];

    readIndex = readIndex + 1;

 	if (readIndex >= numReadings) {
 			readIndex = 0;
 	}

 	average1 = total1 / numReadings;
	average2 = total2 / numReadings;
	average3 = total3 / numReadings;
	average4 = total4 / numReadings;

	totaverage = (average1 + average2 + average3 + average4) / 4;

    return totaverage;
}
