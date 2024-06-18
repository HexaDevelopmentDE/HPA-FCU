/**
 * @copyright     (c) 2024 the author
 * @author        Konstantin Koark <hexa.airsoft@gmail.com>
 *
 * Custom FCU for Airsoft HPA Engines
 *
 * planned featueres:
 * - adjustable valve opening time
 * - adjustable fire rate
 * - binary trigger
 * - webinterface for configuration
 **/

float valve_open_time = 0.1;
float rate_of_fire = 30;
bool binary = false;
int selectedFireMode = 2;
const char* firemodes[][3] = {{"safe", "semi", "full"},{"safe", "semi", "safe"},{"safe", "semi", "semi"}};


void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);

  //print out loaded konfiguration
  Serial.println("Valve Opening Time: " + String(valve_open_time));
  Serial.println("Rate of Fire: " + String(rate_of_fire));
  Serial.println("Binary Trigger enabled: " + String(binary));
  Serial.println("Selected Firemode Konfiguration: " + String(selectedFireMode) + " (" + String(firemodes[selectedFireMode][0]) + ", " + String(firemodes[selectedFireMode][1]) + ", " + String(firemodes[selectedFireMode][2]) + ")");
}

void loop() {
  digitalWrite(LED_BUILTIN, LOW);
  delay(500);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(500);
}

//triggers a shot
void cycle() {}

void startWebServer() {}

void endWebServer() {}

void enterDebugMode() {}

void leaveDebugMode() {}

//flashcodes for diagnosis
void flashcode() {}