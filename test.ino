void setup()
{
     
}

int sensor;
float past[1000]; 
int idx = 0;

void loop()
{
    sensor = analogRead(A0);

    past[idx] = sensor;

    idx++;
    if (idx == 1000)
        idx = 0;

    float threshold = calcAvg(past);
}