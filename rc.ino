const int capMeasurePin = A0;
const int capTriggerPin = A1;

void setup() {
    pinMode(capMeasurePin,INPUT);
    pinMode(capTriggerPin,OUTPUT);

    digitalWrite(capTriggerPin,LOW);

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
            doTest();
                break;
    }
    case 'a':
    {
        unsigned long times[] = [0,0,0,0,0];

        for (int i = 0; i < 5; i ++) {
            times[i] = doTest();
        }

        unsigned long total = 0;
        for (int i =0; i < 5; i ++) {
            total += times[i];
        }

        Serial.print("AVG TIME: ");
        Serial.println(total/5);


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

unsigned long doTest() {
        Serial.println("TEST START");
        int intitalCapMeasure = analogRead(capMeasurePin);
        if (intitalCapMeasure > 100)  {
            Serial.print("[WARNING] Capacitor has: ");
            Serial.println(analogReadToVoltage(intitalCapMeasure));
            Serial.println("Please discharge the capacitor or wait till I figure out mechanism to discharge it programmatically.\nABORT TEST");
            return;
        }
        digitalWrite(capTriggerPin, HIGH);

        int capMeasure = analogRead(capMeasurePin);

        unsigned long startTime =micros();

        // 1T = 63% of charging voltage
        while (analogReadToVoltage(analogRead(capMeasurePin)) < (5 * 0.63)) {
            continue;
        }

        unsigned long elapsed = micros() - startTime;

        Serial.print("Voltage: ");
        Serial.println(analogReadToVoltage(analogRead(capMeasurePin)));

        Serial.print("Time (ms): ");
        Serial.println(elapsed);

        digitalWrite(capTriggerPin, LOW);

        capMeasure = analogRead(capMeasurePin);

        startTime =micros();

        // 1T = 63% of charging voltage
        while (analogReadToVoltage(analogRead(capMeasurePin)) < (5 * 0.63)) {
            continue;
        }

        unsigned long elapsed2 = micros() - startTime;

        Serial.print("Voltage: ");
        Serial.println(analogReadToVoltage(analogRead(capMeasurePin)));

        Serial.print("Time (ms): ");
        Serial.println(elapsed2);

        return ( elapsed + elapsed2 ) / 2
}


float analogReadToVoltage(int measure) {
    return  measure * (5.0 / 1023.0);
}
