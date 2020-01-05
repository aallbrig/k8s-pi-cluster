typedef struct {
  int pin;
  int state;
} k8s_button;

# define BUTTON_ARRAY_SIZE 2
k8s_button buttons[BUTTON_ARRAY_SIZE] = {
  { 3, LOW },
  { 4, LOW }
};

void setup() {
  Serial.begin(9600);

  for (int i=0; i < BUTTON_ARRAY_SIZE; i++) {
    k8s_button btn = buttons[i];

    Serial.println("Setup button pin " + btn.pin);
    pinMode(btn.pin, INPUT);
  }
}

void loop() {
  for (int i=0; i < BUTTON_ARRAY_SIZE; i++) {
    k8s_button btn = buttons[i];
    int state_read = digitalRead(btn.pin);
    if (btn.state != state_read) {
      btn.state = state_read;
      Serial.println("button (" + String(btn.pin) + ") state " + String(btn.state));
    }
  }
}
