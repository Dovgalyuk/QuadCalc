#define PIN_RS 21
#define PIN_RW 20
#define PIN_E  19
#define PIN_RST 18
#define PIN_DB0 37
#define PIN_DB1 36
#define PIN_DB2 35
#define PIN_DB3 34
#define PIN_DB4 33
#define PIN_DB5 32
#define PIN_DB6 31
#define PIN_DB7 30
#define PIN_CS1 22
#define PIN_CS2 23
#define PIN_CS3 24

#define PIN_KEYBOARD_COL 38
#define PIN_KEYBOARD_ROW 46

enum Keys
{
  K_B0, K_B1,
  K_O0, K_O1, K_O2, K_O3, K_O4, K_O5, K_O6, K_O7,
  K_D0, K_D1, K_D2, K_D3, K_D4, K_D5, K_D6, K_D7, K_D8, K_D9,
  K_H0, K_H1, K_H2, K_H3, K_H4, K_H5, K_H6, K_H7, K_H8, K_H9, K_HA, K_HB, K_HC, K_HD, K_HE, K_HF,
  K_Bd, K_Od, K_Dd, K_Hd, // delete
  K_ADD, K_SUB, K_MUL, K_DIV, K_AND, K_OR, K_XOR, K_OK,
  K_NOT, K_NEG, K_LSH, K_RSH,
};

static const uint8_t keymap[] PROGMEM = {
  K_B0, K_B1, K_D8, K_D9, K_Dd, K_Hd, K_Bd, K_Od,
  K_O0, K_O1, K_O2, K_O3, K_O4, K_O5, K_O6, K_O7,
  K_D0, K_D1, K_D2, K_D3, K_D4, K_D5, K_D6, K_D7,
  K_H0, K_H1, K_H2, K_H3, K_H4, K_H5, K_H6, K_H7,
  K_H8, K_H9, K_HA, K_HB, K_HC, K_HD, K_HE, K_HF,
  K_ADD, K_SUB, K_MUL, K_DIV, K_AND, K_OR, K_XOR, K_OK,
  K_NOT, K_NEG, K_LSH, K_RSH,
};


void sendCommand(uint8_t part, uint8_t b)
{
//  DDRC = 0xff;
//  PORTD &= ~5;
//  PORTC = b;
//  PORTD |= 4;
//  DDRC = 0x00;

  for (int i = 0 ; i < 8 ; ++i)
    pinMode(PIN_DB0 - i, OUTPUT);

  digitalWrite(PIN_CS1 + part, LOW);

  digitalWrite(PIN_RS, LOW);
  digitalWrite(PIN_RW, LOW);
  for (int i = 0 ; i < 8 ; ++i)
    digitalWrite(PIN_DB0 - i, ((b >> i) & 1));
  digitalWrite(PIN_E, LOW);
  delayMicroseconds(1);
  digitalWrite(PIN_E, HIGH);
  delayMicroseconds(1);
  digitalWrite(PIN_E, LOW);
  delayMicroseconds(1);

  digitalWrite(PIN_CS1 + part, HIGH);
}

void sendData(uint8_t part, uint8_t b)
{
//  PORTD |= 1;
//  DDRC = 0xff;
//  PORTD &= ~4;
//  PORTC = b;
//  PORTD |= 4;
//  DDRC = 0x00;

  digitalWrite(PIN_CS1 + part, LOW);

  for (int i = 0 ; i < 8 ; ++i)
    pinMode(PIN_DB0 - i, OUTPUT);

  digitalWrite(PIN_RS, HIGH);
  digitalWrite(PIN_RW, LOW);
  for (int i = 0 ; i < 8 ; ++i)
    digitalWrite(PIN_DB0 - i, ((b >> i) & 1));
  digitalWrite(PIN_E, LOW);
  delayMicroseconds(1);
  digitalWrite(PIN_E, HIGH);
  delayMicroseconds(1);
  digitalWrite(PIN_E, LOW);
  delayMicroseconds(1);

  digitalWrite(PIN_CS1 + part, HIGH);
}

uint8_t readStatus()
{
//  DDRC = 0;
//  PORTD |= 2;
//  PORTD &= ~4;
//  uint8_t res = PORTC;
//  PORTD | 4;
//  return res;
  uint8_t res = 0;
  digitalWrite(PIN_RS, LOW);
  digitalWrite(PIN_RW, HIGH);

  for (int i = 0 ; i < 8 ; ++i)
    pinMode(PIN_DB0 - i, INPUT);
  
  digitalWrite(PIN_E, LOW);
  delayMicroseconds(1);
  digitalWrite(PIN_E, HIGH);
  delayMicroseconds(1);
  for (int i = 0 ; i < 7 ; ++i)
    res |= digitalRead(PIN_DB0 - i) << i;
  digitalWrite(PIN_E, LOW);
  delayMicroseconds(4500);
}

void setup() {
//  // put your setup code here, to run once:
//  // PORTC - data bus line
//  DDRC = 0x0;
//  // PORTD
//  //  0 RS
//  //  1 R/W
//  //  2 E
//  //  3 RST
//  DDRD = 0x0f;
//  PORTD = 0x0c;
//  // PORTA
//  //  0-2 CS1-3
//  DDRA = 0x07;
//  PORTA = 0;
//
  //Serial.begin(9600);
  //while (!Serial) {}
//
  //Serial.println("Test\n");
//
//  sendCommand(0x1f);
//
//  uint8_t d = readData();
//  Serial.println(d, HEX);
//  
//  //for (int i = 0 ; i < 64 ; ++i)
//  //  sendData(0xff);
//
//  d = readData();
//  Serial.println(d, HEX);

  pinMode(PIN_RS, OUTPUT);
  pinMode(PIN_RW, OUTPUT);
  pinMode(PIN_E, OUTPUT);
  pinMode(PIN_RST, OUTPUT);

  for (int i = 0 ; i < 8 ; ++i)
    pinMode(PIN_DB0 - i, OUTPUT);
  pinMode(PIN_CS1, OUTPUT);
  pinMode(PIN_CS2, OUTPUT);
  pinMode(PIN_CS3, OUTPUT);

  for (int i = 0 ; i < 8 ; ++i)
  {
    pinMode(PIN_KEYBOARD_ROW + i, OUTPUT);
    digitalWrite(PIN_KEYBOARD_ROW + i, HIGH);
    pinMode(PIN_KEYBOARD_COL + i, INPUT_PULLUP);
  }

  digitalWrite(PIN_CS1, HIGH);
  digitalWrite(PIN_CS2, HIGH);
  digitalWrite(PIN_CS3, HIGH);

  digitalWrite(PIN_RST, LOW);

  delay(1000);

  digitalWrite(PIN_RST, HIGH);

  delay(1000);

  //Serial.println(readStatus());

  // on command
  sendCommand(0, 0x3f);
  sendCommand(1, 0x3f);
  sendCommand(2, 0x3f);

  //Serial.println(readStatus());

  //Serial.println(readStatus());

  // off command
  //sendCommand(1, 0x3e);
  
  //Serial.println(readStatus());

//  digitalWrite(PIN_RST, LOW);
//  delayMicroseconds(5);
//  Serial.println(readStatus());

  //sendCommand(0x40);
  //sendCommand(0xb8);
  //sendCommand(0xc0);

  // clear screen
  for (int part = 0 ; part < 3 ; ++part)
    for (int p = 0 ; p < 8 ; ++p)
    {
      sendCommand(part, 0xb8 + p);
      for (int i = 0 ; i < 64 ; ++i)
        sendData(part, 0x00);
    }

}

// 2: 192 / 32 = 6
// 8: 192 / 11 = 17
// 10: 192 / 11 = 17
// 16: 192 / 8 = 24

// upper bits down
#define PART_W 64

#define FONT_W 5
const uint8_t font[] PROGMEM = {
  B01111100,
  B10000010,
  B10000010,
  B01111100,
  B00000000,

  B00000000,
  B00000100,
  B11111110,
  B00000000,
  B00000000,

  B11000100,
  B10100010,
  B10010010,
  B10001100,
  B00000000,

  B01000010,
  B10010010,
  B10011010,
  B01100110,
  B00000000,

  B00011110,
  B00010000,
  B00010000,
  B11111110,
  B00000000,

  B01001110,
  B10001010,
  B10001010,
  B01110010,
  B00000000,

  B01111100,
  B10010010,
  B10010010,
  B01100000,
  B00000000,

  B00000010,
  B00000010,
  B11111010,
  B00000110,
  B00000000,

  B01101100,
  B10010010,
  B10010010,
  B01101100,
  B00000000,

  B00001100,
  B10010010,
  B10010010,
  B01111100,
  B00000000,

  B11111100,
  B00010010,
  B00010010,
  B11111100,
  B00000000,

  B11111110,
  B10010010,
  B10010010,
  B01101100,
  B00000000,

  B01111100,
  B10000010,
  B10000010,
  B01000100,
  B00000000,

  B11111110,
  B10000010,
  B10000010,
  B01111100,
  B00000000,

  B11111110,
  B10010010,
  B10010010,
  B10000010,
  B00000000,

  B11111110, // 0f
  B00010010,
  B00010010,
  B00000010,
  B00000000,

  B00000000, // 10
  B00000000,
  B00000000,
  B00000000,
  B00000000,

  B00010000, // 11
  B00010000,
  B11111110,
  B00010000,
  B00010000,

  B00010000, // 12
  B00010000,
  B00010000,
  B00010000,
  B00010000,

  B01000100, // 13
  B00101000,
  B00010000,
  B00101000,
  B01000100,

  B01000000, // 14
  B00100000,
  B00010000,
  B00001000,
  B00000100,

  B01101100, // 15
  B10010010,
  B10110010,
  B01001100,
  B10100000,

  B00000000, // 16
  B00000000,
  B11111110,
  B00000000,
  B00000000,

  B00001000, // 17
  B00000100,
  B00000010,
  B00000100,
  B00001000,
};

static int lineX;
static uint8_t lineSeg;

static void lineSend(uint8_t b)
{
  sendData(lineSeg, b);
  ++lineX;
  if (lineX == PART_W)
  {
    lineX = 0;
    lineSeg = (lineSeg + 1) % 3;
  }
}

static void drawChar(uint8_t c)
{
    for (int j = 0 ; j < FONT_W ; ++j)
    {
      uint8_t b = pgm_read_byte(font + c * FONT_W + j);
      lineSend(b);
    }
}

static void setupPage(uint8_t page)
{
  uint8_t part;
  for (part = 0 ; part < 3 ; ++part)
  {
    sendCommand(part, 0xb8 + page);
    // y = 0
    sendCommand(part, 0x40 + 0);
  }
}

static void drawBin(uint8_t page, uint32_t v)
{
  setupPage(page);
  lineSeg = 0;
  lineX = 0;
  uint32_t mask = 0x80000000;
  for (int i = 0 ; i < 32 ; ++i, mask >>= 1)
  {
    uint8_t c = 0;
    if (v & mask)
      c = 1;
    drawChar(c);
    //lineSend(c);
    if ((i & 3) == 3)
    {
      lineSend(0);
      lineSend(0);
      lineSend(0);
    }
  }
}

static void drawOct(uint8_t page, uint32_t v)
{
  setupPage(page);
  lineSeg = 0;
  lineX = 0;
  int shift = 30;
  for (int i = 0 ; i < 11 ; ++i, shift -= 3)
  {
    uint8_t c = (v >> shift) & 7;
    drawChar(c);
  }
}

static void drawDec(uint8_t page, uint32_t v)
{
  setupPage(page);
  lineSeg = 0;
  lineX = 0;
  int8_t d[10];
  for (int8_t i = 0 ; i < 10 ; ++i)
  {
    d[i] = v % 10;
    v = v / 10;
  }
  for (int8_t i = 9 ; i >= 0 ; --i)
    drawChar(d[i]);
}

static void drawHex(uint8_t page, uint32_t v)
{
  setupPage(page);
  lineSeg = 0;
  lineX = 0;
  int shift = 28;
  for (int i = 0 ; i < 8 ; ++i, shift -= 4)
  {
    uint8_t c = (v >> shift) & 0xf;
    drawChar(c);
  }
}

static uint32_t completeOp(int8_t op, uint32_t acc, uint32_t v)
{
  switch (op)
  {
  case K_ADD:
    return acc + v;
  case K_SUB:
    return acc - v;
  case K_MUL:
    return acc * v;
  case K_DIV:
    return v ? acc / v : 0;
  case K_AND:
    return acc & v;
  case K_OR:
    return acc | v;
  case K_XOR:
    return acc ^ v;
  default:
    return v;
  }  
}

static uint8_t getOpChar(int8_t op)
{
  switch (op)
  {
  case K_ADD:
    return 0x11;
  case K_SUB:
    return 0x12;
  case K_MUL:
    return 0x13;
  case K_DIV:
    return 0x14;
  case K_AND:
    return 0x15;
  case K_OR:
    return 0x16;
  case K_XOR:
    return 0x17;
  default:
    return 0x10;
  }
}

void loop()
{
  uint32_t v = 0;
  uint32_t acc = 0;
  int8_t op = -1;
  while (true)
  {
    drawBin(0, v);
    drawOct(1, v);
    drawDec(2, v);
    drawHex(3, v);
    drawBin(4, acc);
    drawChar(getOpChar(op));
    drawOct(5, acc);
    drawDec(6, acc);
    drawHex(7, acc);

    uint32_t lastKey = millis();
    while (lastKey + 200 > millis())
      ;
    while (true)
    {
      int8_t key = -1;
      for (int i = 0 ; i < 8 ; ++i)
      {
        digitalWrite(PIN_KEYBOARD_ROW + i, LOW);
        for (int j = 0 ; j < 8 ; ++j)
          if (!digitalRead(PIN_KEYBOARD_COL + j))
            key = i * 8 + j;
        digitalWrite(PIN_KEYBOARD_ROW + i, HIGH);
      }
      if (key >= 0)
      {
        key = pgm_read_byte(keymap + key);
        switch (key)
        {
        case K_B0...K_B1:
          v = v * 2 + key - K_B0;
          break;
        case K_O0...K_O7:
          v = v * 8 + key - K_O0;
          break;
        case K_D0...K_D9:
          v = v * 10 + key - K_D0;
          break;
        case K_H0...K_HF:
          v = v * 16 + key - K_H0;
          break;
        case K_Bd:
          v = v / 2;
          break;
        case K_Od:
          v = v / 8;
          break;
        case K_Dd:
          v = v / 10;
          break;
        case K_Hd:
          v = v / 16;
          break;
        case K_ADD:
        case K_SUB:
        case K_MUL:
        case K_DIV:
        case K_AND:
        case K_OR:
        case K_XOR:
          acc = completeOp(op, acc, v);
          v = 0;
          op = key;
          break;
        case K_OK:
          v = acc = completeOp(op, acc, v);
          op = -1;
          break;
        case K_NOT:
          v = ~v;
          break;
        case K_NEG:
          v = -v;
          break;
        case K_LSH:
          v <<= 1;
          break;
        case K_RSH:
          v >>= 1;
          break;
        }
        break;
      }
    }
  }
}
