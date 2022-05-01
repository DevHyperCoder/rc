const int capMeasurePin = A5;
const int capTriggerPin = 2;

void setup() {
    pinMode(capMeasurePin,INPUT);
    pinMode(capTriggerPin,OUTPUT);

    digitalWrite(capTriggerPin,HIGH);

    Serial.begin(9600);
}

void loop() {
    if (Serial.available() > 0) {
        auto c = Serial.read();
        handleData(c);
    }
}

void handleData(char c) {
    switch(c) {
    case 's':
    {
        int intitalCapMeasure = analogRead(capMeasurePin);
        if (intitalCapMeasure > 100)  {
            Serial.print("[WARNING] Capacitor has: ");
            Serial.println(analogReadToVoltage(m));
            Serial.println("Please discharge the capacitor or wait till I figure out mechanism to discharge it programmatically.\nABORT TEST");
            return;
        }
        digitalWrite(capTriggerPin, LOW);

        int capMeasure = analogRead(capMeasurePin);

        unsigned long startTime = millis();

        // 1T = 63% of charging voltage
        while (analogReadToVoltage(analogRead(capMeasurePin)) < (5 * 0.63)) {
            continue;
        }

        unsigned long elapsed = millis() - startTime;

        Serial.print("Voltage: ");
        Serial.println(analogReadToVoltage(analogRead(capMeasurePin)));

        Serial.print("Time (ms): ");
        Serial.println(elapsed);

        digitalWrite(capTriggerPin, HIGH);
        break;
    }
    case 'h':
    {
        Serial.println("Press 's' to start the test");
        break;
    }
    case 'v':
    {
        Serial.println(analogReadToVoltage(analogRead(capMeasurePin)));
        break;
    }
    }
}


float analogReadToVoltage(int measure) {
    return  measure * (5.0 / 1023.0);
}
