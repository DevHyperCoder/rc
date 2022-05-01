int main() {
    if (int m = analogRead() > 100)  {
        printf("[WARNING] Capacitor has: %d volts.",m);
        printf("Please discharge the capacitor or wait till I figure out mechanism to discharge it programmatically.\nABORT TEST");
        return 1;
    }
    return 0;
}

int analogRead() {
    /*return 0;*/
    return 200;
}
