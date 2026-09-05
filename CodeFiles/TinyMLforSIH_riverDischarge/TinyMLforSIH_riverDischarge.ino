#include "model_data.h" // Includes model_data and model_data_len
#include <tflm_esp32.h>
#include <eloquent_tinyml.h>
#define NUMBER_OF_INPUTS 1   // Sensor features (e.g., Temp, Humidity, Pressure)
#define NUMBER_OF_OUTPUTS 1  // Single classification output
#define TENSOR_ARENA_SIZE 8 * 1024 // 8KB RAM reserved for TFLite execution

Eloquent::TF::Sequential<NUMBER_OF_OUTPUTS, TENSOR_ARENA_SIZE> tf;
const int sensor = 33;
void setup() 
{
  Serial.begin(115200);
  delay(3000);
  tf.setNumInputs(NUMBER_OF_INPUTS);
  tf.setNumInputs(NUMBER_OF_OUTPUTS);
  // Initialize the TFLite model array
  if (!tf.begin(model_data)) {
    Serial.println("Failed to initialize model!");
    while (1);
  }
  Serial.println("Model loaded into ESP32 successfully!");
  pinMode(sensor, OUTPUT);
}

void loop() {
  // Replace these with actual live sensor readings (e.g., analogRead or I2C sensor)
  float sensor_temp = analogRead(sensor);
//  float sensor_humidity = 65.0;
//  float sensor_pressure = 1013.2;

  float input[NUMBER_OF_INPUTS] = {sensor_temp};

  // Perform inference
  float prediction = tf.predict(input);

  Serial.print("Model Output Probability: ");
  Serial.println(prediction);

  if (prediction > 0.5) {
    Serial.println("Class: Detected (1)");
  } else {
    Serial.println("Class: Normal (0)");
  }
  Serial.print("It takes ");
  Serial.print(tf.benchmark.microseconds());
  Serial.println("us for a single prediction");
  delay(2000);
}
