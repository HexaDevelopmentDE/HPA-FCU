/**
 * @copyright     (c) 2024 the author
 * @author        Konstantin Koark <hexa.airsoft@gmail.com>
 *
 * Custom FCU for Airsoft HPA Engines with 1 valve
 *
 * planned featueres:
 * - adjustable valve opening time
 * - adjustable fire rate
 * - binary trigger
 * - webinterface for configuration
 * - fire selector
 **/

#define BUTTON_TRIGGER D8
#define BUTTON_FIRESELECTOR D1
#define BUTTON_TRANSISTOR D6

int prev_trigger_state;
int prev_selector_state;
int trigger_state;
int selector_state;

float valve_open_time = 60;
float rate_of_fire = 40;
bool binary = false;
int selectedFireModeConfig = 0;
const char* firemodes[][3] = {{"safe", "semi", "full"},{"safe", "semi", "safe"},{"safe", "semi", "semi"}};
int currentFireMode = 0;


void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);

  pinMode(BUTTON_FIRESELECTOR, INPUT);
  prev_selector_state = 0;
  pinMode(BUTTON_TRIGGER, INPUT);
  prev_trigger_state = 0;

  pinMode(BUTTON_TRANSISTOR, OUTPUT);
  digitalWrite(BUTTON_TRANSISTOR, LOW);

  //manually set fire mode
  firemodes[selectedFireModeConfig][currentFireMode] = "semi";

  //print out loaded konfiguration
  Serial.println("Valve Opening Time: " + String(valve_open_time));
  Serial.println("Rate of Fire: " + String(rate_of_fire));
  Serial.println("Binary Trigger enabled: " + String(binary));
  Serial.println("Selected Firemode Konfiguration: " + String(selectedFireModeConfig) + " (" + String(firemodes[selectedFireModeConfig][0]) + ", " + String(firemodes[selectedFireModeConfig][1]) + ", " + String(firemodes[selectedFireModeConfig][2]) + ")");
  Serial.println("Current Fire Mode: " + String(firemodes[selectedFireModeConfig][currentFireMode]));

  //Ready Up Signal
  flashcode("ready", 1);
}

void loop() {
  //switchFireMode();
  delay(10);
  cycle();
}

//triggers a shot
void cycle() {
  trigger_state = digitalRead(BUTTON_TRIGGER);

  if(firemodes[selectedFireModeConfig][currentFireMode] == "safe") {
    if (trigger_state == LOW && prev_trigger_state == HIGH) {
      Serial.println("nothing happens, it's on safe");
    }
  }

  if(firemodes[selectedFireModeConfig][currentFireMode] == "semi") {
    //Serial.println(String(trigger_state) + " == 1 && " + String(prev_trigger_state) + " == 0");

    if (trigger_state == HIGH && prev_trigger_state == LOW) {
      flashcode("shot", 1);

      digitalWrite(BUTTON_TRANSISTOR, HIGH);
      delay(valve_open_time);
      digitalWrite(BUTTON_TRANSISTOR, LOW);
    }
  }

  if(firemodes[selectedFireModeConfig][currentFireMode] == "full") {
    if (trigger_state == HIGH && prev_trigger_state == LOW) {
      while(trigger_state == HIGH) {
        flashcode("shot", 1);

        digitalWrite(BUTTON_TRANSISTOR, HIGH);
        delay(valve_open_time);
        digitalWrite(BUTTON_TRANSISTOR, LOW);

        trigger_state = digitalRead(BUTTON_TRIGGER);

        delay((1000/rate_of_fire));
      }
    }
  }

  prev_trigger_state = trigger_state;  
}

void startWebServer() {}

void endWebServer() {}

void enterDebugMode() {}

void leaveDebugMode() {}

//flashcodes for diagnosis
void flashcode(String code, int amount) {
  for (int i=0; i < amount; i++){
    if(code == "firemode") {
      digitalWrite(LED_BUILTIN, LOW);
      delay(50);
      digitalWrite(LED_BUILTIN, HIGH);
      delay(50);
    }

    if(code == "shot") {
      digitalWrite(LED_BUILTIN, LOW);
      delay(10);
      digitalWrite(LED_BUILTIN, HIGH);
      Serial.println("triggered");
    }

    if(code == "ready") {
      digitalWrite(LED_BUILTIN, LOW);
      delay(10);
      digitalWrite(LED_BUILTIN, HIGH);
      delay(2);
      digitalWrite(LED_BUILTIN, LOW);
      delay(10);
      digitalWrite(LED_BUILTIN, HIGH);
      delay(2);
    }
  }
}

void switchFireMode() {
  selector_state = digitalRead(BUTTON_FIRESELECTOR);
  int oldFireMode = currentFireMode;

  if (selector_state == LOW && prev_selector_state == HIGH) {
    switch(currentFireMode) {
      case 0:
        currentFireMode = currentFireMode + 1;
        flashcode("firemode", 2);
        break;
      case 1:
        currentFireMode = currentFireMode + 1;
        flashcode("firemode", 3);
        break;
      case 2:
        currentFireMode = 0;
        flashcode("firemode", 1);
        break;
    }
    Serial.println("switch fire mode from "  + String(firemodes[selectedFireModeConfig][oldFireMode]) + " to  " + String(firemodes[selectedFireModeConfig][(currentFireMode)]));
  }

  prev_selector_state = digitalRead(BUTTON_FIRESELECTOR);
}
