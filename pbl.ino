#include <NewPing.h> // Including library for HC-SR84 sensor

#define TRIGGER_PIN 9
#define ECHO_PIN 10
#define BUZZER_PIN 11
#define LED_PIN 12
#define MAX_DISTANCE 200 // Max sensor range in cm
#define POSTURE_THRESHOLD 40 // Slouching limit in cm

// Starting the NewPing object with designated hardware pins
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

void setup() {
  pinMode(BUZZER_PIN, OUTPUT); // configure buzzer pin as output alert
  pinMode(LED_PIN, OUTPUT); // configure led pin as output alert
  Serial.begin(9600); // Starting Serial Monitor
}

void loop() {
  float distance = readDistance(); // getting current distance calculation
  checkPosture(distance); // seeing current distance vs posture boundaries
  delay(500); // wait half a sec before redoing the loop          
}

// Function 1: readDistance
// * Purpose: Trigger ultra sonic sensor and return distance in cm
// * Returns: float value representing distance

float readDistance() {

  float cm = sonar.ping_cm(); // fetch distance using library math
  
  // Output data to Serial Monitor for real-time tracking
  Serial.print("Distance: ");
  Serial.print(cm);
  Serial.println(" cm");
  
  return cm;
}

// Function 2: checkPosture
// Purpose: See if current distance info to trigger alerts if the user sits poorly
// Parameters: float currentDist = the latest reading from the sensor

void checkPosture(float currentDist) {
  if (currentDist > 0 && currentDist < POSTURE_THRESHOLD) {

// Too close (User is slouching foward)
    digitalWrite(LED_PIN, HIGH);
    digitalWrite(BUZZER_PIN, HIGH); 
    delay(100); 
    digitalWrite(BUZZER_PIN, LOW);

// Too far (User is leaning Back)
  } else if (currentDist >= 58 && currentDist <= 80) {

    digitalWrite(LED_PIN, HIGH);
    digitalWrite(BUZZER_PIN, HIGH);
    delay(100); 
    digitalWrite(BUZZER_PIN, LOW);

// SWEETTTT SPOTTT (User has perfect posture!)
  } else {

    digitalWrite(LED_PIN, LOW);
    digitalWrite(BUZZER_PIN, LOW);

  }
}