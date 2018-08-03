#include <LiquidCrystal.h>   //Biblioteca do LCD.
#include <DHT.h>   //Biblioteca do DHT.

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);   //Definição de portas do display.
DHT dht(A5, DHT11);   //Definição de porta analógica e tipo do sensor DHT.
float temperatura, umidade;
int luminosidade, LDR = A4, lux = 0;


void setup()
{
  dht.begin();   //Inicialização do sensor.
  Serial.begin(9600);   //Inicialização da comunicação serial.
  lcd.begin(20, 4);   //Inicialização do display e definição de colunas e linhas.
  lcd.clear();   //Limpeza do display.
  //Impressçao de apresentação inicial do projeto:
  lcd.setCursor(6, 0);
  lcd.print("Estacao");
  lcd.setCursor(3, 1);
  lcd.print("Metereologica");
  lcd.setCursor(4, 3);
  lcd.print("IEEE - UEFS");
  delay(5000);   //Intervalo de 5s.
  lcd.clear();   //Limpeza do display.
  
  //Impressão de informações fixas na tela:
  lcd.setCursor(1, 0);
  lcd.print("Temperatura: ");
  lcd.setCursor(18, 0);
  lcd.print("C");
  lcd.setCursor(2, 1);
  lcd.print("Umidade: ");
  lcd.setCursor(17, 1);
  lcd.print("%");
  lcd.setCursor(1, 2);
  lcd.print("Luminosidade: ");
}

void loop()
{
  temperatura = dht.readTemperature();
  umidade = dht.readHumidity();
  luminosidade = analogRead(LDR);   //Lê valor (0 ~ 1023).
  lux = map(luminosidade, 0, 1023, 0, 100);

  if (isnan(temperatura) || isnan(umidade)) {
    Serial.println("Falha na leitura do sensor!");
  } else {
    //Impressão de temperatura no monitor serial:
    Serial.print("Temperatura: ");
    Serial.print(temperatura, 1);
    Serial.println("ºC");
    //Impressão de temperatura no display:
    lcd.setCursor(14, 0);
    lcd.print(temperatura, 1);
    
    //Impressão de umidade no monitor serial:
    Serial.print("Umidade: ");
    Serial.print(umidade, 1);
    Serial.println("%");
    //Impressão de humidade no display:
    lcd.setCursor(12, 1);
    lcd.print(umidade, 1);

    //Impressão de luminosidade no monitor serial:
    Serial.print("Luminosidade: ");
    Serial.println(lux);
    //Impressão de luminosidade no display:
    lcd.setCursor(15, 2);
    lcd.print(lux);
  }
  delay(1000);   //Intervalo de leitura a cada 5s.
}
