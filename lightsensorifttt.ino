#include "BH1750.h"

BH1750 sensor(0x23, Wire);

int lightLevel;

String result;

void setup()
{
    lightLevel = 0;
    
    sensor.begin();
    
    sensor.set_sensor_mode(BH1750::forced_mode_high_res2);
    
    Serial.begin();
}

void loop()
{
    sensor.make_forced_measurement();
    
    Serial.println(String::format("%f", sensor.get_light_level()));
    
    if (lightLevel != 1 && sensor.get_light_level() < 1000)
    {
        result = "Dark";
        
        Particle.publish("dark", result, PRIVATE);
        
        lightLevel = 1;
    }
    
    if (lightLevel != 2 && sensor.get_light_level() >= 1000 && sensor.get_light_level() <= 2500)
    {
        result = "Shade";
        
        Particle.publish("shade", result, PRIVATE);
        
        lightLevel = 2;
    }
    
    if (lightLevel != 3 && sensor.get_light_level() > 2500)
    {
        result = "Light";
        
        Particle.publish("light", result, PRIVATE);
        
        lightLevel = 3;
    }
    
    delay(5000);
}
