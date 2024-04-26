char ingang;
bool isActief = false;
int knopStd; // knopStd staat voor knop stand

const int rels[] = {3,4,5};
bool relStds[] = {false,false,false}; // relStd staat voor relais standen
const int knopjes[] = {11,10,9,8,12};
int hrkKnopStds[] = {LOW,LOW,LOW,LOW,LOW}; // hrkKnopStds staat voor laatst herkende knop standen

unsigned long vrgMilis = 0;
const long interval = 5000; // Interval voor inactiefCon()
bool verzenden = true;

void setup() {
  for (int i = 0; i < 5; i++) {
    pinMode(knopjes[i], OUTPUT); // what the fuck? ingangen moesten toch niet als OUTPUT gedeclareerd zijn???
  }

  for (int i = 0; i < 3; i++) {
    pinMode(rels[i], OUTPUT);
  }

  for (int i = 0; i < 3; i++) {
    digitalWrite(rels[i], relStds[i]); // initiële relaisstatus instellen
  }

  Serial.begin(9600);
}

void loop() {
  buttonHandler();
  if (verzenden) {
    inactiefCon();
  }

  if (Serial.available() > 0) {
    char ingang = Serial.read();
    cliHandler(ingang);
  }
}

void inactiefCon() {
  unsigned long hdgMilis = millis();

  if (hdgMilis - vrgMilis >= interval) {
    vrgMilis = hdgMilis;
    Serial.println("AAN HET WACHTEN VOOR ACTIVITEIT, DRUK OP H VOOR HULPMENU OF ERGENS OM DEZE BERICHTEN TE DOVEN");
  }
}

void buttonHandler() {
  int hdgKnopStd[5];

  for (int i = 0; i < 5; i++) {
    hdgKnopStd[i] = digitalRead(knopjes[i]);
  }

  if (hdgKnopStd[0] != hrkKnopStds[0]) {             // check of de knop stand verandert is (induwen van knop1)
    if (hdgKnopStd[0] == HIGH) {                     // schakel de relais in of uit op de moment de knop ingeduwt word (HIGH)
      Serial.println("S1");                          // geef aan in het opdrachtregel dat er een buttonHandler geduwt is
      relStds[0] = !relStds[0];                      // schakel de stand van de relai
      blink();
      digitalWrite(rels[0], relStds[0]);             // stel de relai in als behoort
      if (relStds[0]) {
        Serial.println("\033[32;49m[S1] E1 AAN");    // als E1 aangezet werd, geef het door aan de opdrachtregel
        rdy();
      } else {
        Serial.println("\033[31;49m[S1] E1 UIT");    // als E1 uitgezet werd, geef het door aan de opdrachtregel
        rdy();
      }
    }
  }

  hrkKnopStds[0] = hdgKnopStd[0]; // slaag de huidige status op als de laatste status voor de volgende keer

  if (hdgKnopStd[1] != hrkKnopStds[1]) {
    if (hdgKnopStd[1] == HIGH) {
      Serial.println("S2");
      relStds[1] = !relStds[1];
      digitalWrite(rels[1], relStds[1]);
      blink();
      if (relStds[1]) {
        Serial.println("\033[32;49m[S2] E2 AAN");
        rdy();
      } else {
        Serial.println("\033[31;49m[S2] E2 UIT");
        rdy();
      }
    }
  }

  hrkKnopStds[1] = hdgKnopStd[1];

  if (hdgKnopStd[2] != hrkKnopStds[2]) {
    if (hdgKnopStd[2] == HIGH) {
      Serial.println("S3");
      relStds[2] = !relStds[2];
      digitalWrite(rels[2], relStds[2]);
      blink();
      if (relStds[2] == HIGH) {
        Serial.println("\033[32;49m[S3] E3 AAN");
        rdy();
      } else {
        Serial.println("\033[31;49m[S3] E3 UIT");
        rdy();
      }
    }
  }
  hrkKnopStds[2] = hdgKnopStd[2];

  if (!isActief && hdgKnopStd[3] != hrkKnopStds[3] && (relStds[0] == HIGH || relStds[1] == HIGH || relStds[2] == HIGH)) {
    isActief = true;
    if (hdgKnopStd[3] == HIGH) {
      Serial.println("S4");
      relStds[0] = LOW;
      relStds[2] = LOW;
      relStds[1] = LOW;
      digitalWrite(rels[0], LOW);
      digitalWrite(rels[1], LOW);
      digitalWrite(rels[2], LOW);
      Serial.println("\033[31;49m[S4] Alle lampen UIT");
      rdy();
      blink();
    }
    hrkKnopStds[3] = hdgKnopStd[3];
    isActief = false;
  }
  if (!isActief && hdgKnopStd[4] != hrkKnopStds[4] && (relStds[0] == LOW || relStds[1] == LOW || relStds[2] == LOW)) {
    isActief = true;
    if (hdgKnopStd[4] == HIGH) {
      Serial.println("S5");
      relStds[0] = HIGH;
      relStds[1] = HIGH;
      relStds[2] = HIGH;
      digitalWrite(rels[0], HIGH);
      digitalWrite(rels[1], HIGH);
      digitalWrite(rels[2], HIGH);
      Serial.println("\033[32;49m[S5] Alle lampen AAN");
      rdy();
      blink();
    }
    hrkKnopStds[4] = hdgKnopStd[4];
    isActief = false;
  }
}

void cliHandler(char ingang) {
  if (ingang == '1') {
    Serial.println(ingang);
    relStds[0] = !relStds[0];
    digitalWrite(rels[0], relStds[0]);
    if (relStds[0]) {
      Serial.println("\033[32;49m[1] E1 AAN");
      rdy();
    } else {
      Serial.println("\033[31;49m[1] E1 UIT");
      rdy();
    }
  }

  if (ingang == '2') {
    Serial.println(ingang);
    relStds[1] = !relStds[1];
    digitalWrite(rels[1], relStds[1]);
    if (relStds[1]) {
      Serial.println("\033[32;49m[2] E2 AAN");
      rdy();
    } else {
      Serial.println("\033[31;49m[2] E2 UIT");
      rdy();
    }
  }

  if (ingang == '3') {
    Serial.println(ingang);
    relStds[2] = !relStds[2];
    digitalWrite(rels[2], relStds[2]);
    if (relStds[2]) {
      Serial.println("\033[32;49m[3] E3 AAN");
      rdy();
    } else {
      Serial.println("\033[31;49m[3] E3 UIT");
      rdy();
    }
  }

  if (ingang == '4' || ingang == '0') {
    Serial.println(ingang);
    relStds[0] = LOW;
    relStds[2] = LOW;
    relStds[1] = LOW;
    digitalWrite(rels[0], LOW);
    digitalWrite(rels[1], LOW);
    digitalWrite(rels[2], LOW);
    Serial.println("\033[31;49m[0 / 4] Alle lampen UIT");
    rdy();
  }

  if (ingang == '5') {
    Serial.println(ingang);
    relStds[0] = HIGH;
    relStds[1] = HIGH;
    relStds[2] = HIGH;
    digitalWrite(rels[0], HIGH);
    digitalWrite(rels[1], HIGH);
    digitalWrite(rels[2], HIGH);
    Serial.println("\033[32;49m[5] Alle lampen AAN");
    rdy();
    blink();
  }

  if (ingang == 'h' || ingang == 'H') {
    verzenden = false;
    Serial.println(ingang);
    Serial.println("\033[91;49m========== HELPMENU ==========");
    Serial.println("");
    Serial.println("\033[91;49m==== ALGEMENE BEDIENINGEN ====");
    Serial.println("\033[0m[1] \033[32;49mE1 AAN \033[0m/\033[31;49m UIT");
    Serial.println("\033[0m[2] \033[32;49mE2 AAN \033[0m/\033[31;49m UIT");
    Serial.println("\033[0m[3] \033[32;49mE3 AAN \033[0m/\033[31;49m UIT");
    Serial.println("\033[0m[0 / 4] \033[31;49mAlle lampen UIT");
    Serial.println("\033[0m[5] \033[32;49mAlle lampen AAN");
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
    Serial.println("\033[39;49mLights Out V3");
    Serial.println("CLI versie 3");
    Serial.println("\033[39;49mGemaakt door \033[34;49;1m17\033[36;49;1mnct \033[0m@ 2024");
    rdy();
  }

  if ((ingang == 'x' || 'X') && verzenden == true) { /* de OR operator dient niet zo gebruikt te worden, doe je het toch? Hij zal dan niet alleen op x of X reageren maar op alles. */
    killmsg();
  }
}

void blink() {
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
  Serial.print("\033[39;49m>");
}
