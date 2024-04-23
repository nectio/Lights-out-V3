// Pin definitions
const int rel1 = 3; // the number of the LED pin
const int rel2 = 4;
const int rel3 = 5;
char ingang;
const int knop1 = 11;
const int knop2 = 10;
const int knop3 = 9;
const int knop4 = 8;
// Variables will change:
bool ledState1 = false; // variable to store the LED state
bool ledState2 = false;
bool ledState3 = false;
bool ledState4 = false;
// variable to store the LED state
int buttonState; // variable to read the pushbutton status
int lastButtonState1 = LOW;
int lastButtonState2 = LOW;
int lastButtonState3 = LOW;
int lastButtonState4 = LOW;

unsigned long vrgMilis = 0;
const long interval = 5000; // Interval voor inactiefCon()
bool verzenden = true;


void setup() {
  pinMode(knop1, OUTPUT);
  pinMode(rel1, OUTPUT);
  pinMode(knop2, OUTPUT);
  pinMode(rel2, OUTPUT);
  pinMode(knop3, OUTPUT);
  pinMode(rel3, OUTPUT);
  pinMode(knop4, OUTPUT); // initialize the LED pin as an output
  Serial.begin(9600); // initialize serial communication at 9600 bits per second
  digitalWrite(rel1, ledState1);
  digitalWrite(rel2, ledState2);
  digitalWrite(rel3, ledState3); // set initial LED state
}

void loop() {
drukknop();
  if (verzenden) {
    inactiefCon();
  }

  if (Serial.available() > 0) {
    char ingang = Serial.read();
    software(ingang);
    
  }
}

void inactiefCon() {
  unsigned long hdgMilis = millis();

  if (hdgMilis - vrgMilis >= interval) {
    vrgMilis = hdgMilis;
    Serial.println("AAN HET WACHTEN VOOR ACTIVITEIT, DRUK OP H VOOR HULPMENU OF ERGENS OM DEZE BERICHTEN TE DOVEN");
  }
}



void drukknop() {

  int currentButtonState1 = digitalRead(knop1);
  int currentButtonState2 = digitalRead(knop2);
  int currentButtonState3 = digitalRead(knop3);
  int currentButtonState4 = digitalRead(knop4);
  // check if button state changed from high to low (button press)
  if (currentButtonState1 != lastButtonState1) {
    // only toggle the LED if the new button state is LOW
    if (currentButtonState1 == LOW) {
      Serial.println("S1");
      ledState1 = !ledState1; // toggle the state of the LED
      digitalWrite(rel1, ledState1); // set the LED accordingly

      if (ledState1) {
        Serial.println("\033[32;49m[S1] E1 AAN");
        rdy();
      } else {
        Serial.println("\033[31;49m[S1] E1 UIT");
        rdy();
      }
    }
  }
  lastButtonState1 = currentButtonState1;

  if (currentButtonState2 != lastButtonState2) {
    // only toggle the LED if the new button state is LOW
    if (currentButtonState2 == LOW) {
 Serial.println("S2");
      ledState2 = !ledState2; // toggle the state of the LED
      digitalWrite(rel2, ledState2); // set the LED accordingly
      if (ledState2) {
        Serial.println("\033[32;49m[S2] E2 AAN");
        rdy();
      } else {
        Serial.println("\033[31;49m[S2] E2 UIT");
        rdy();
      }
    }
  }

  lastButtonState2 = currentButtonState2;

  if (currentButtonState3 != lastButtonState3) {
    // only toggle the LED if the new button state is LOW
    if (currentButtonState3 == LOW) {
       Serial.println("S3");
      ledState3 = !ledState3; // toggle the state of the LED
      digitalWrite(rel3, ledState3); // set the LED accordingly
      if (ledState3 == HIGH) {
        Serial.println("\033[32;49m[S3] E3 AAN");
        rdy();
      } 
      else {
        Serial.println("\033[31;49m[S3] E3 UIT");
        rdy();
      }
    }
  }
  lastButtonState3 = currentButtonState3;
  // save the current state as the last state, for next time through the loop

  if (currentButtonState4 != lastButtonState4 && ledState1 == HIGH || ledState2 == HIGH || ledState3 == HIGH ) {
    // only toggle the LED if the new button state is LOW
    if (currentButtonState4 == HIGH) {
       Serial.println("S4");
      // only toggle the LED if the new button state is LOW
   ledState3 = LOW;
    ledState2 = LOW;
    ledState1 = LOW;
      digitalWrite(rel1, LOW);
      digitalWrite(rel2, LOW);
      digitalWrite(rel3, LOW);
      Serial.println("\033[31;49m[S4] Alle lampen UIT");
        rdy();

    }
    lastButtonState4 = currentButtonState4;
  }


}
void software(char ingang) {
  if (ingang == '1') { // if '1' is received
  Serial.println(ingang);
    ledState1 = !ledState1; // toggle the state of the LED
    digitalWrite(rel1, ledState1);
    if (ledState1) {
      Serial.println("\033[32;49m[1] E1 AAN");
      rdy();
    } else {
      Serial.println("\033[31;49m[1] E1 UIT");
      rdy();
    }
  }

  if (ingang == '2') { // if '1' is received
  Serial.println(ingang);
    ledState2 = !ledState2; // toggle the state of the LED
    digitalWrite(rel2, ledState2); // set the LED accordingly
    if (ledState2) {
      Serial.println("\033[32;49m[2] E2 AAN");
      rdy();
    } else {
      Serial.println("\033[31;49m[2] E2 UIT");
      rdy();
    }
  }

  if (ingang == '3') { // if '1' is received
  Serial.println(ingang);
      
    ledState3 = !ledState3; // toggle the state of the LED
    digitalWrite(rel3, ledState3);
    if (ledState3) {
      Serial.println("\033[32;49m[3] E3 AAN");
      rdy();
    } else {
      Serial.println("\033[31;49m[3] E3 UIT");
       rdy();
    }
  }

  if (ingang == '4' || ingang == '0') { // if '1' is received
  Serial.println(ingang);
    ledState3 = LOW;
    ledState2 = LOW;
    ledState1 = LOW;
    digitalWrite(rel1, LOW);
    digitalWrite(rel2, LOW);
    digitalWrite(rel3, LOW); // set the LED accordingly
    Serial.println("\033[31;49m[0 / 4] Alle lampen UIT");
    rdy();
  }

    if (ingang == 'h' || ingang == 'H') {
    verzenden = false;
    Serial.println(ingang);
    Serial.println("\033[91;49m========== HELPMENU ==========");
    Serial.println("");
    Serial.println("\033[91;49m==== ALGEMENE BEDIENINGEN ====");
    Serial.println("\033[32;49m[1] E1 AAN");
    Serial.println("\033[32;49m[2] E2 AAN");
    Serial.println("\033[32;49m[3] E3 AAN");
    Serial.println("\033[31;49m[0 / 4] Alle lampen UIT");
    Serial.println("");
    Serial.println("\033[91;49m==== OPDRACHTREGELINTERFACE BEDIENINGEN ====");
    Serial.println("\033[0m[C] Opdrachtregelinterface wissen");
    Serial.println("[H] Toon deze hulpmenu");
    Serial.println("[I] Informatie");
    rdy();
  }

  if (ingang == 'c' || ingang == 'C') {
    Serial.print("[\033[2J\033[H");
    verzenden = false;
    rdy();
  }
  if (ingang == 'i' || ingang == 'I') {
    Serial.println(ingang);
    Serial.println("\033[39;49mLights Out V2");
    Serial.println("CLI versie 3");
    Serial.println("\033[39;49mGemaakt door \033[34;49;1m17\033[36;49;1mnct \033[0m@ 2024");
    rdy();
  }
  if ((ingang == 'x' || 'X') && verzenden == true) {
    /* de OR operator dient niet zo gebruikt te worden, doe je het toch? Hij zal dan niet alleen op x of X reageren maar op alles. */
    killmsg();
  }
}

void knipperLED() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(50);
  digitalWrite(LED_BUILTIN, LOW);
}

void killmsg() {
  verzenden = false;
  Serial.println("BERICHTEN GEDOOFD.");
  Serial.print("\033[39;49m>");
}

void rdy() {
  verzenden = false;
  Serial.print("\033[39;49m>");
}
