

#include "filter.h";


Zumo32U4Motors motors;

Filter filter;

char report[120];

static float bias = 0;
static float obs = 0;
static float fus = 0;

float CONVERSION = 16384;

void setup()
{
  Serial.begin(115200);
  while (!Serial) {}
  filter.Init();
}



void loop()
{
  if (filter.calcAngle(obs, fus, bias)) {
    Serial.print(millis());
    Serial.print("\t");
    Serial.print(obs);
    Serial.print("\t");
    Serial.print(fus);
    Serial.print("\t");
    Serial.print(bias);
    Serial.println();
  }

}
