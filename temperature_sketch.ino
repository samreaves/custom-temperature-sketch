/**
 * @name Sam's Custom Temperature Sketch
 * @file temperature_sketch.ino
 * @description Custom temperature sketch for Arduino Uno
 * @author Sam Reaves
 * @date December 20th, 2015
 
 Forked from Scott Fitzgerald's Love-O-Meter from Chapter 3 
 of Arduino Starter Kit http://arduino.cc/starterKit

 Parts required:
 1 TMP36 temperature sensor
 3 red LEDs
 3 220 ohm resistors

 */


/* Global variables */
// Temperature sensor pin can be any analog pin. Scott chose A0.
const int temperatureSensorPin = A0;

// Set up constants for pins connected to LEDs. You can change pins here if you'd like
const int LED_pins[3] = {2, 3, 4};
    
// Establish placeholder integer variable for base temperature
float baseTemperature;



/* Custom methods */


/**
 * @name convertSensorValueToVoltage
 * @description Converts TMP 36's sensor value to voltage
 *
 * @param {int} [sensorValue] Insert the TMP36 sensor analog value here in integer form
 * @returns {float} [voltage] Returns float voltage for us to use later
 *
 * @author Sam Reaves
 * @date December 20th, 2015
 */
float convertSensorValueToVoltage(int sensorValue) {
  
  // Log sensor value parameter
  //Serial.print("TMP36 Sensor Value: ");
  //Serial.println(sensorValue);
  
  // Calculate voltage by converting ADC reading against 5 volts, and specify it to be a float
  float voltage =  (sensorValue / 1024.0) * 5.0;
  
  // Ship voltage onto the next
  return voltage;
    
}



/**
 * @name convertVoltageToTemperature
 * @description Converts TMP36 sensor's voltage to degrees Celsius
 *
 * @param {float} [voltage] Insert the temperature sensor's voltage here in float form
 * @returns {float} [temperature] Returns float temperature for us to use later
 *
 * @author Sam Reaves
 * @date December 20th, 2015
 */
float convertVoltageToTemperature(float voltage) {
  
  // Log voltage parameter
  //Serial.print("TMP36 Voltage: ");
  //Serial.println(voltage);
  
  /*
   * TMP36 sensor changes 10 mV (millivolts) per degree
   * Datasheet says there's a 500 mV offset
   * ((voltage - 500mV) times 100)
   */

  // Convert voltage to temperature in Celsius. Specify it as a float.
  float temperature = (voltage - 0.5) * 100;
  
  // Log conversion value
  //Serial.print("Current temperature: ");
  //Serial.println(temperature);
  
  // Ship temperature to the next
  return temperature;
}


/**
 * @name getTemperatureFromSensor
 * @description Grabs temperature from sensor
 *
 * @param {int} [sensor] Insert the TMP36 sensor pointer here in integer form
 * @returns {float} [temperature] Returns float temperature for us to use later
 *
 * @author Sam Reaves
 * @date December 20th, 2015
 */
float getTemperatureFromSensor(int sensorPin) {
  
  // Cache sensor reading  
  int sensorValue = analogRead(sensorPin);
  
  // Grab voltage from sensor value
  float voltage = convertSensorValueToVoltage(sensorValue);
  
  // Grab temperature from voltage
  float temperature = convertVoltageToTemperature(voltage);
  
  // Return temperature
  return temperature;
}



/* Arduino Methods */

/**
 * @name setup
 * @description Initializes Arduino component by grabbing initial temperature, setting ports and initalizing logger
 * @author Sam Reaves
 * @date December 20th, 2015
 */
void setup() {
  
   // Open a serial connection to Arduino IDE for logging
   Serial.begin(9600);
  
   // We have 3 LEDs connected to 3 pins. For each pin... 
   for (int pin = 0; pin < 3; pin++) {
        
      // Cache pin
      int currentPin = LED_pins[pin];
      
      // Set pin mode as OUTPUT 
      pinMode(currentPin, OUTPUT);
      
      // Initialize them as off
      digitalWrite(currentPin, LOW);
   }
  
  // Grab initial temperature from sensor pin
  baseTemperature = getTemperatureFromSensor(temperatureSensorPin);
  
  // Give temperature sensor time to read
  delay(1);
  
  Serial.print("Base temperature: ");
  Serial.println(baseTemperature);
}


/**
 * @name loop
 * @description Continuous runtime loop similar to C's int main(); In this case, light up LEDs if temperature increases above base temperature
 * @author Sam Reaves
 * @date December 20th, 2015
 */
void loop() {
  
  // Cache current temperature
  float currentTemperature = getTemperatureFromSensor(temperatureSensorPin);
  
  Serial.print("Base Temperature: ");
  Serial.println(baseTemperature);
  Serial.print("Current Temperature: ");
  Serial.println(currentTemperature);
  
  
  // If current temperature is less than base temperature
  if (currentTemperature < baseTemperature) {
 
    Serial.println("Temperature below base temperature. Turning LEDs off");
    
    // Turn off all LEDs
    digitalWrite(LED_pins[0], LOW);
    digitalWrite(LED_pins[1], LOW);
    digitalWrite(LED_pins[2], LOW);
  }
  // If current temperature rises 2-4 degrees above base temperature, turn first LED on
  else if (currentTemperature >= baseTemperature + 2 && currentTemperature < baseTemperature + 4) {
    
    Serial.println("Current temperature higher than 2 degrees above base temperature. Turning first LED on");
    
    // Turn on first LED
    digitalWrite(LED_pins[0], HIGH);
    digitalWrite(LED_pins[1], LOW);
    digitalWrite(LED_pins[2], LOW);
  } 
  // If current temperature rises 4-6 degrees above base temperature, turn a second LED on
  else if (currentTemperature >= baseTemperature + 4 && currentTemperature < baseTemperature + 6) {
    
    Serial.println("Current temperature higher than 4 degrees above base temperature. Turning first two LEDs on");
    
    // Turn first 2 LEDs on
    digitalWrite(LED_pins[0], HIGH);
    digitalWrite(LED_pins[1], HIGH);
    digitalWrite(LED_pins[2], LOW);
  } 
  // If current temperature rises 6 degrees above base temperature, turn all LEDs on
  else if (currentTemperature >= baseTemperature + 6) {
    
    Serial.println("Current temperature higher than 6 degrees above base temperature. Turning all LEDs on");
    
    // Turn all LEDs on
    digitalWrite(LED_pins[0], HIGH);
    digitalWrite(LED_pins[1], HIGH);
    digitalWrite(LED_pins[2], HIGH);
  }
  
  // The temperature sensor needs a break. Give it one millisecond of a breather.
  delay(1);
}
