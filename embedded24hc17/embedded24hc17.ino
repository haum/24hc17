namespace {
  const constexpr int led = 2;
  const constexpr int wait = 200;
  bool blink = true;
  int divider = 0;
}

void setup() {
  pinMode(led, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  blink = !blink;
  digitalWrite(led, blink);
  delay(wait);

  if (divider == 2000/wait) {
    divider = 0;
    Serial.println("Test");
  } else {
    divider++;
  }
}
