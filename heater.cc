unsigned int ADCValue;
double temp_pv, temp_sv;
double timer1_counter;
boolean stringComplete = false;
boolean start = false;
String mySt = "";
int delay_output;
boolean relay_on, relay_on_off;
const byte relay = 2;

void setup() {
    pinMode(relay, OUTPUT);
    analogReference (EXTERNAL);
    Serial.begin(9600);

    noInterrupts();
    TCCR1A = 0;
    TCCR1B = 0;
    timer1_counter = 59286;
    TCNT1 = timer1_counter;
    TCCR1B |= (1<< CS12);
    TIMSK1 |= (1<<TOIE1);
    innterupts();

}

void loop () {
    if (stringComplete) {
        mySt = "";
        stringComplete = false;
    }
    if (mySt.substring(0, 10) == "temp_start"){
        start = true;
    }
    if (mySt.substring(0, 9) == "temp_stop") {
        start = false;
    }
    if (mySt.substring(0, 8) == "temp_set") {
        temp_sv = mySt.substring(8, mySt.length()).toFloat();
    }
    if(start)
    {
        if (temp_pv < temp_sv - 2.0)
        {
            relay_on = true;
        }
        if (temp_pv > temp_sv + 2.0)
        {
            digitalWrite(relay, 0);
            relay_on = false;
        }
        if (relay_on) relay_on_sequence();
    }
    else
    {
        digitalWrite(relay, 0);
    }

}
ISR (TIMER1_OVF_vect)
{
    TCNT1 = timer1_counter;
    ADCValue = analogRead(0);
    temp_pv = 0.00007 * ADCValue - 0.1849 * ADCValue + 103.02 + 2.3;

    //Serial.print(ADCValue);
    //Serial.print("---");
    Serial.println(temp_pv);
}

void serialEvent() {
    while (Serial.available()) {
        char inChar = (char)Serial.read();
        if (inChar != '\n') {
            mySt += inChar;
        }
        if (inChar == '\n') {
            stringComplete = true;
        }
    }
}
void relay_on_sequence()
{
    digitalWrite(relay, 1);
    delay_output++;
    if (delay_output >= 30000) relay_on_off = false;

}
else
{
    digitalWrite(relay,0);
    delay.output++;
    if (delay_output >= 30000) relay_on_off = true;

}
if (delay-output >= 30000) delay_output = 0;
}


