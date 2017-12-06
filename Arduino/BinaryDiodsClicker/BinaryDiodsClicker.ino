int number = 0;

int ledPin1 = 2;
int ledPin2 = 3;
int ledPin3 = 4;
int ledPin4 = 5;

int buttonPin = 12;   // choose the input pin (for a pushbutton)
int buttonState = LOW;
int prevButtonState = LOW;
int counting = 0;

long startTime;
byte hasError;

void setup() {
	Serial.begin(9600);

	pinMode(ledPin1, OUTPUT);  // declare LED as output
	pinMode(ledPin2, OUTPUT);  // declare LED as output
	pinMode(ledPin3, OUTPUT);  // declare LED as output
	pinMode(ledPin4, OUTPUT);  // declare LED as output
	pinMode(buttonPin, INPUT_PULLUP);    // declare pushbutton as input
}

void loop() {

	buttonState = digitalRead(buttonPin);

	// check if the pushbutton is pressed. If it is, the buttonState is HIGH:
	if (buttonState == HIGH && prevButtonState == LOW) {

		prevButtonState = HIGH;

		// Generate new random number
		if (counting == 0) {
			hasError = 0;
			startTime = millis();
			number = random(1, 15);
			printNumber(number);
			displayBinary(number);
		}

		// Check if 2 seconds have passed between two clicks.
		if (millis() - startTime > 2000) {
			Serial.println("Error");
			hasError = 1;
		}

		// Check click numbers
		if (counting == number - 1) {
			Serial.println("Success");
			counting = 0;
		}
		else {
			if (hasError == 0) {
				counting++;
				startTime = millis();
				Serial.println(counting);
			}
			else {
				counting = 0;
			}
		}
	}

	// Set previous button state so we can count clicks and not state changes.
	if (buttonState == LOW && prevButtonState == HIGH) {
		prevButtonState = LOW;
	}
}


void displayBinary(byte number) {

	int binary[4];
	convertToBinary(number, binary);

	digitalWrite(ledPin1, binary[0]);
	digitalWrite(ledPin2, binary[1]);
	digitalWrite(ledPin3, binary[2]);
	digitalWrite(ledPin4, binary[3]);

}

void convertToBinary(byte number, int binary[4]) {

	for (int i = 0; i <= 3; i++) {
		if (bitRead(number, i) == 1) {
			binary[i] = 1;
		}
		else {
			binary[i] = 0;
		}
	}

}

void printNumber(int number) {
	Serial.println();
	Serial.println("--------------------------");
	Serial.print("Random number: ");
	Serial.print(number);
	Serial.println();
	Serial.println("--------------------------");
}