#include <Arduino.h>
#include <Wire.h>
#include <MPU6050.h>

// Create an MPU6050 object
MPU6050 mpu;

// Variables to store accelerometer data
int16_t ax, ay, az;
int16_t gx, gy, gz;

void setup() {

  bool result = Wire.setPins(21,22);
  if (result)  {
    Serial.println("I2C pins successfully set!");
  } else {
    Serial.println("Failed to set I2C pins.");
    while (1); // Halt the program if the configuration fails
  }
  Wire.setClock(100000);
  Wire.begin();
  
  Serial.begin(9600);
//   while (!Serial); 

  // Initialize I2C communication
//   Wire.begin(21, 22); // SDA, SCL for ESP32

  // Initialize the MPU6050 sensor
  Serial.println("Initializing MPU6050...");
  mpu.initialize();

  // Check if MPU6050 is connected
  if (mpu.testConnection()) {
    Serial.println("MPU6050 is connected!");
  } else {
    Serial.println("MPU6050 connection failed!");
    while (1);  // Halt the program if the sensor is not connected
  }

}

void calculate_error(){
    

}

void loop() {
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  // acceleration data (raw units)
  Serial.print("Acceleration X: ");
  Serial.print(ax);
  Serial.print("\tY: ");
  Serial.print(ay);
  Serial.print("\tZ: ");
  Serial.println(az);

  Serial.print("Rotation X: ");
  Serial.print(gx);
  Serial.print("\tY: ");
  Serial.print(gy);
  Serial.print("\tZ: ");
  Serial.println(gz);

  delay(500);
}

