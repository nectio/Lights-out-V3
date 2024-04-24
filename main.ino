char ingang;

const int rel1 = 3;
const int rel2 = 4;
const int rel3 = 5;

const int knop1 = 11;
const int knop2 = 10;
const int knop3 = 9;
const int knop4 = 8;
const int knop5 = 12;

bool relStd1 = false; // relStd staat voor relai stand
bool relStd2 = false;
bool relStd3 = false;

int knopStd; // knopStd staat voor knop stand
int hrkKnopStd1 = LOW; // hrkKnopStd1 staat voor laatst herkende knop stand
int hrkKnopStd2 = LOW;
int hrkKnopStd3 = LOW;
int hrkKnopStd4 = LOW;
int hrkKnopStd5 = LOW;

unsigned long vrgMilis = 0;
const long interval = 5000; // Interval voor inactiefCon()
bool verzenden = true;

void setup() {
  pinMode(knop1, OUTPUT); // what the fuck? ingangen moesten toch niet als OUTPUT gedeclareerd zijn???
  pinMode(knop2, OUTPUT);
  pinMode(knop3, OUTPUT);
  pinMode(knop4, OUTPUT);
  pinMode(knop5, OUTPUT); 

  pinMode(rel1, OUTPUT);
  pinMode(rel2, OUTPUT);
  pinMode(rel3, OUTPUT);
  digitalWrite(rel1, relStd1); // initiële relaisstatus instellen
  digitalWrite(rel2, relStd2);
  digitalWrite(rel3, relStd3);

  Serial.begin(9600);
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

  int hdgKnopStd1 = digitalRead(knop1);
  int hdgKnopStd2 = digitalRead(knop2);
  int hdgKnopStd3 = digitalRead(knop3);
  int hdgKnopStd4 = digitalRead(knop4);
  int hdgKnopStd5 = digitalRead(knop5);

  if (hdgKnopStd1 != hrkKnopStd1) {               // check of de knop stand verandert is van laag naar hoog (induwen van knop1)
    if (hdgKnopStd1 == HIGH) {                    // schakel de relais in of uit op de moment de knop ingeduwt word (HIGH)
      Serial.println("S1");                       // geef aan in het opdrachtregel dat er een drukknop geduwt is
      relStd1 = !relStd1;                         // schakel de stand van de relai
      digitalWrite(rel1, relStd1);                // stel de relai in als behoort
      if (relStd1) {
        Serial.println("\033[32;49m[S1] E1 AAN"); // als E1 aangezet werd, geef het door aan de opdrachtregel
        rdy();
      } else {
        Serial.println("\033[31;49m[S1] E1 UIT"); // als E1 uitgezet werd, geef het door aan de opdrachtregel
        rdy();
      }
    }
  }

  hrkKnopStd1 = hdgKnopStd1; // slaag de huidige status op als de laatste status voor de volgende keer

  if (hdgKnopStd2 != hrkKnopStd2) {
    if (hdgKnopStd2 == HIGH) {
      Serial.println("S2");
      relStd2 = !relStd2; 
      digitalWrite(rel2, relStd2);
      if (relStd2) {
        Serial.println("\033[32;49m[S2] E2 AAN");
        rdy();
      } else {
        Serial.println("\033[31;49m[S2] E2 UIT");
        rdy();
      }
    }
  }

  hrkKnopStd2 = hdgKnopStd2;

  if (hdgKnopStd3 != hrkKnopStd3) {
    if (hdgKnopStd3 == HIGH) {
      Serial.println("S3");
      relStd3 = !relStd3;
      digitalWrite(rel3, relStd3);
      if (relStd3 == HIGH) {
        Serial.println("\033[32;49m[S3] E3 AAN");
        rdy();
      } else {
        Serial.println("\033[31;49m[S3] E3 UIT");
        rdy();
      }
    }
  }
  hrkKnopStd3 = hdgKnopStd3;

  if (hdgKnopStd4 != hrkKnopStd4 && relStd1 == HIGH || relStd2 == HIGH || relStd3 == HIGH) {
    if (hdgKnopStd4 == HIGH) {
      Serial.println("S4");
      relStd3 = LOW;
      relStd2 = LOW;
      relStd1 = LOW;
      digitalWrite(rel1, LOW);
      digitalWrite(rel2, LOW);
      digitalWrite(rel3, LOW);
      Serial.println("\033[31;49m[S4] Alle lampen UIT");
      rdy();
    }
    hrkKnopStd4 = hdgKnopStd4;
  }
  if (hdgKnopStd5 != hrkKnopStd5 && relStd1 == LOW || relStd2 == LOW || relStd3 == LOW) {
    if (hdgKnopStd5 == HIGH) {
      Serial.println("S5");
      relStd3 = HIGH;
      relStd2 = HIGH;
      relStd1 = HIGH;
      digitalWrite(rel1, HIGH);
      digitalWrite(rel2, HIGH);
      digitalWrite(rel3, HIGH);
      Serial.println("\033[31;49m[S5] Alle lampen AAN");
      rdy();
    }
    hrkKnopStd5 = hdgKnopStd5;
  }
}
void software(char ingang) {
  if (ingang == '1') {
    Serial.println(ingang);
    relStd1 = !relStd1;
    digitalWrite(rel1, relStd1);
    if (relStd1) {
      Serial.println("\033[32;49m[1] E1 AAN");
      rdy();
    } else {
      Serial.println("\033[31;49m[1] E1 UIT");
      rdy();
    }
  }

  if (ingang == '2') {
    Serial.println(ingang);
    relStd2 = !relStd2;
    digitalWrite(rel2, relStd2);
    if (relStd2) {
      Serial.println("\033[32;49m[2] E2 AAN");
      rdy();
    } else {
      Serial.println("\033[31;49m[2] E2 UIT");
      rdy();
    }
  }

  if (ingang == '3') { 
    Serial.println(ingang);
    relStd3 = !relStd3;
    digitalWrite(rel3, relStd3);
    if (relStd3) {
      Serial.println("\033[32;49m[3] E3 AAN");
      rdy();
    } else {
      Serial.println("\033[31;49m[3] E3 UIT");
      rdy();
    }
  }

  if (ingang == '4' || ingang == '0') { 
    Serial.println(ingang);
    relStd3 = LOW;
    relStd2 = LOW;
    relStd1 = LOW;
    digitalWrite(rel1, LOW);
    digitalWrite(rel2, LOW);
    digitalWrite(rel3, LOW); 
    Serial.println("\033[31;49m[0 / 4] Alle lampen UIT");
    rdy();
  }

  if (ingang == '5') { 
    Serial.println(ingang);
    relStd3 = HIGH;
    relStd2 = HIGH;
    relStd1 = HIGH;
    digitalWrite(rel1, HIGH);
    digitalWrite(rel2, HIGH);
    digitalWrite(rel3, HIGH); 
    Serial.println("\033[31;49m[5] Alle lampen AAN");
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
    Serial.println("\033[31;49m[5] Alle lampen AAN");
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
