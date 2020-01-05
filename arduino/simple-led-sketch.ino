typedef struct {
  String name;
  int yellow_led_pin;
  int red_led_pin;
} k8s_node;

# define NODE_ARRAY_SIZE 5
k8s_node nodes[NODE_ARRAY_SIZE] = {
  { "k8s-node-master-1", 3, 9 },
  { "k8s-node-worker-1", 4, 10 },
  { "k8s-node-worker-2", 5, 11 },
  { "k8s-node-worker-3", 6, 12 },
};

void setup() {
  Serial.begin(9600);

  for (int i=0; i < NODE_ARRAY_SIZE; i++) {
    k8s_node node = nodes[i];

    Serial.println("Setup node: " + node.name);
    Serial.println("Yellow LED pin " + String(node.yellow_led_pin) + " Red LED pin " + String(node.red_led_pin));

    pinMode(node.yellow_led_pin, OUTPUT);
    pinMode(node.red_led_pin, OUTPUT);
  }
}

void loop() {
  for (int i=0; i < NODE_ARRAY_SIZE; i++) {
    digitalWrite(nodes[i].yellow_led_pin, HIGH);
    digitalWrite(nodes[i].red_led_pin, LOW);
  }
  delay(1000);

  for (int i=0; i < NODE_ARRAY_SIZE; i++) {
    digitalWrite(nodes[i].yellow_led_pin, LOW);
    digitalWrite(nodes[i].red_led_pin, HIGH);
  }
  delay(1000);
}
