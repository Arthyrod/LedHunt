#include <LiquidCrystal.h>
#define SER A1 // data 1
#define RCLK A2 // latch 1
#define SRCLK A3 // clk 1
#define clk2 A5 // latch 2
#define latch2 A4 // clk 2
#define BuzzerPin 3
// pino 2 o do botao                                                                                                                                                      
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

unsigned long millis1 = millis();
unsigned long millis2 = millis();

int aux = 0;
int vetor[6] = {80,200,60,150,100,50};
int velocidade = 350;
int hit = 0;
int jogadas = 0;
int acertos = 0;
int contador_lcd = 0;

byte numb1 = 0x01;
byte numb2 = 0x01;
int botao_ativar = 0;

void pulso(byte pino){
  digitalWrite(pino,1);
  digitalWrite(pino,0);
}

void interrupcao(){
  jogadas++;
  botao_ativar = 1;
  aux = 0;
  desloca_led(0x01);
  numb1 = 0x01;
  lcd.setCursor(0,0);
  lcd.print("Jogadas: ");
  lcd.print(jogadas);
}
void desloca_led(byte x){
  for(int i=0;i<8;i++){
    digitalWrite(SER,(x<<i)&0x80);
    pulso(SRCLK);}
  pulso(RCLK);
}

void desloca_led2(byte x){
  for(int i=0;i<8;i++){
    digitalWrite(SER,(x<<i)&0x80);
    pulso(clk2);}
  pulso(latch2);
}

void setup() {

  //Set pin as outputs
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0,0);
  randomSeed(analogRead(0));
  //lcd.print("A");
  pinMode(SER, OUTPUT);
  pinMode(RCLK, OUTPUT);
  pinMode(SRCLK, OUTPUT);
  pinMode(clk2,1);
  pinMode(latch2,1);
  pinMode(3,1);
  digitalWrite(BuzzerPin,0);
  attachInterrupt(0,interrupcao,FALLING);
  digitalWrite(RCLK, LOW);
  digitalWrite(SRCLK, LOW);
  digitalWrite(clk2, LOW);
  digitalWrite(latch2, LOW);
  lcd.setCursor(0,0);
  lcd.print("Jogadas: ");
  lcd.print(jogadas);
  lcd.setCursor(0,1);
  lcd.print("Acertos: ");
  lcd.print(acertos);
}

void loop(){
  if (velocidade < 50){
    velocidade = 0;}
  if (((millis() - millis1) > velocidade) && !hit){  // VERDE
    desloca_led2(numb2);
    numb2= numb2<<1;
    millis1 = millis();
  }
  
  else if(((millis() - millis2) > 100) && botao_ativar){ //VERMELHO
    desloca_led(numb1);
    numb1= numb1<<1;
    millis2 = millis();
  }
  if ((numb1 == 0x80 && numb2 == 0x08) && aux == 0){
     //Serial.println("Acertou");
     hit = 1;
     velocidade = vetor[random(0, 6)];
     aux = 1;
  }
  if (hit){
    acertos++;
    desloca_led2(0xFF);
    desloca_led(0x00);
    delay(1000);
    desloca_led2(0x00);
    delay(1000);
    //desloca_led(numb1);
    desloca_led2(numb2);
    hit = 0;
    tone(BuzzerPin,100,400);
    tone(BuzzerPin,600,200);
    lcd.setCursor(0,1);
    lcd.print("Acertos: ");
    lcd.print(acertos);
  }
  if (numb2 == 0x80){
    numb2 = 0x01;
  }
}
