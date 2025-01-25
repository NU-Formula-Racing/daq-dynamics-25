#include <Arduino.h>
#include <Wire.h>
#include <MPU6050.h>
#include <vector>

// Create an MPU6050 object
MPU6050 mpu;

// Variables to store accelerometer data
int16_t ax, ay, az;
int16_t gx, gy, gz;

float AccX, AccY, AccZ, GyroX, GyroY, GyroZ;
float AccErrorX, AccErrorY, AccErrorZ, GyroErrorX, GyroErrorY, GyroErrorZ;


float velocity;

std::vector<float> acceleration = {0,0,0,0,0,0,0,0,0};

void integrate_acceleration();

void calculate_error();

void setup() 
{


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

  calculate_error();

}
int t = 0;

void loop() 
{
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  AccX = (9.81 * ((float) ax / 16384.0 - AccErrorX));
  AccY = (9.81 * ((float) ay / 16384.0 - AccErrorY));
  AccZ = (9.81 * ((float) az / 16384.0 - AccErrorZ)) - 9.81;

  GyroX = ((float) gx / 131.0) - GyroErrorX;
  GyroY = ((float) gy / 131.0) - GyroErrorY;
  GyroZ = ((float) gz / 131.0) - GyroErrorZ;

  acceleration[t] = sqrt(pow((cos(GyroX) * AccX),2) + pow((cos(GyroY) * AccY),2) + pow((sin(GyroZ) * AccZ),2));

  Serial.print("velocity: ");
  Serial.println(velocity);

  t++;

  if (8 == t)
  {
    integrate_acceleration();
    t = 0;
  }

  delay(500);
}


// calculating the initial error for all acceleration and gyroscope values

void calculate_error() {
  int i = 0;

  AccErrorX = 0;
  AccErrorY = 0;
  GyroErrorX = 0;
  GyroErrorY = 0;
  GyroErrorZ = 0;

  AccX = 0;
  AccY = 0;
  AccZ = 0;

  while (i < 200) {
    // Read raw accelerometer data
    mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

    // Convert raw accelerometer data to g (1g = 16384 LSB)
    AccErrorX += (ax / 16384.0);
    AccErrorY += (ay / 16384.0);
    AccErrorZ += (az / 16384.0);


    //pitch
    // AccErrorX = AccErrorX + ((atan((AccY) / sqrt(pow((AccX), 2) + pow((AccZ), 2))) * 180 / PI)); 
    //roll
    // AccErrorY = AccErrorY + ((atan(-1 * (AccX) / sqrt(pow((AccY), 2) + pow((AccZ), 2))) * 180 / PI));

    GyroErrorX = GyroErrorX + (gx / 131.0);
    GyroErrorY = GyroErrorY + (gy / 131.0);
    GyroErrorZ = GyroErrorZ + (gz / 131.0);
    i++;
  }

  AccErrorX /= 200;
  AccErrorY /= 200;
  AccErrorZ = 0;

  GyroErrorX = GyroErrorX / 200;
  GyroErrorY = GyroErrorY / 200;
  GyroErrorZ = GyroErrorZ / 200;

}


//
// Using Simpson's Rule 
// Calculating velocity only with acceleration every 9 data points
//
void integrate_acceleration() 
{
  float velocity_holder = acceleration[0] + acceleration [8];
  for (int jj = 1; jj < 7 ; jj++)
  {
    if (jj % 2 == 1)
    {
      velocity_holder += 4 * acceleration[jj];
    }
    else
    {
      velocity_holder += 2 * acceleration[jj];
    }
  }
  velocity += (9/3) * velocity_holder;
}
