

#include "dataFilter.h";


Zumo32U4Motors motors;

dataFilter filter;


float convert = 16384;
static float obs= 0;
static float fus = 0;
static float bias = 0;

char report[120];

void setup()
{
  Serial.begin(115200);
  while (!Serial) {}
  filter.Init();
}

void loop()
{
  if (filter.calcAngle(bias, obs, fus)) {

    Serial.print(obs);
    Serial.print("\t");
    Serial.print(fus);
    Serial.print("\t");
    Serial.print(bias);
    Serial.println();
  }

}
