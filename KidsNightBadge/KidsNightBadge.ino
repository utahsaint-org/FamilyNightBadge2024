#include <avr/io.h>
#include <util/delay.h>

int MaxCycles=20;

// Define delay constants
#define DELAY_SHORT 250
#define DELAY_MEDIUM 500
#define DELAY_LONG 1000

#define DOT_DURATION 300
#define DASH_DURATION 900
#define GAP_DURATION 200
#define CHAR_GAP_DURATION 1000
#define WORD_GAP_DURATION 3000

// Morse code representation for A-Z and 0-9
const char morse_code[36][5] = {
    "01", "1000", "1010", "1000", "0", "0010", "1100", "0000", "00", "0111",
    "1010", "0100", "11", "10", "111", "0110", "1101", "010", "000", "1",
    "001", "0001", "011", "1001", "1011", "1100", "0000", "1000", "0001", "010",
    "1100", "0110"
};

// Convert character to Morse code index
int char_to_index(char c) {
    if (c >= 'A' && c <= 'Z') return c - 'A';
    if (c >= '0' && c <= '9') return c - '0' + 26;
    return -1; // Unsupported character
}

// Blink LED based on Morse code
void blink_morse(const char* morse) {
    delay(1000);
    while (*morse) {
        if (*morse == '0') {
            PORTB=0x07; // Turn LED on
            _delay_ms(DOT_DURATION); // Dot duration
        } else if (*morse == '1') {
            PORTB=0x07; // Turn LED on
            _delay_ms(DASH_DURATION); // Dash duration
        }
        PORTB=0x00; // Turn LED off
        _delay_ms(GAP_DURATION); // Intra-character gap
        morse++;
    }
}


void setup() {
  DDRB |= (1 << PB0) | (1 << PB1) | (1 << PB2);
}


void loop() {
  MorseCode("SECRET MESSAGE");
  BinaryCount();
  RandomBlink();
  KnightRider();
  FastBlinker();
  FasterBlink();
  Alternation();
}

void Alternation() {
  for (int cycles=0; cycles < MaxCycles*5; cycles++) {
    delay(100);
    PORTB = 5;
    delay(100);
    PORTB = 2;
  }
}

void BinaryCount() {
  for (int cycles=0; cycles < 4; cycles++){
  for (int led=0; led < 8; led++){
  PORTB = led;
  delay(500);
}
  }
  PORTB = 0x00;
}

void RandomBlink() {
  for (int cycles=0; cycles < MaxCycles*10; cycles++) {
    int random = rand() % 8;
    PORTB = random;
    delay(50);
  }
}

void KnightRider() {
  for (int cycles=0; cycles < MaxCycles; cycles++) {
    int RiderDelay = 75;
    PORTB=1; delay(RiderDelay); PORTB=2; delay(RiderDelay); PORTB=4; delay(RiderDelay+100); PORTB=0; delay(RiderDelay/2);
    PORTB=4; delay(RiderDelay); PORTB=2; delay(RiderDelay); PORTB=1; delay(RiderDelay+100); PORTB=0; delay(RiderDelay/2);
  }
}

void FastBlinker() {
  for (int cycles=0; cycles < MaxCycles*2; cycles++) {
    int random = (rand() % 3 == 0) ? 1 : (rand() % 3 == 1) ? 2 : 4;
    PORTB = random;
    delay(20);
    PORTB=0;
    delay(200);
  }
}

void FasterBlink() {
  for (int cycles=0; cycles < MaxCycles*4; cycles++) {
    int random = rand() % 8;
    PORTB = random;
    delay(20);
    PORTB=0;
    delay(70);
  }
}

// Morse Code Function
void MorseCode(const char* message) {
    while (*message) {
        int index = char_to_index(*message);
        if (index != -1) { // Valid character
            blink_morse(morse_code[index]);
            _delay_ms(CHAR_GAP_DURATION); // Inter-character gap
        }
        message++;
    }
    _delay_ms(WORD_GAP_DURATION); // Inter-word gap
}
