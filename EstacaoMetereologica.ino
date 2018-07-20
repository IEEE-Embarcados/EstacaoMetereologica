#include <LiquidCrystal.h>   //Biblioteca do LCD.
#include <DHT.h>   //Biblioteca do DHT.

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);   //Definição de portas do display.
DHT dht(A5, DHT11);   //Definição de porta analógica e tipo do sensor DHT.
float temperatura, humidade;
int luminosidade;


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
  lcd.print("Humidade: ");
  lcd.setCursor(17, 1);
  lcd.print("%");
  lcd.setCursor(1, 2);
  lcd.print("Luminosidade: ");
}

void loop()
{
  temperatura = dht.readTemperature();
  humidade = dht.readHumidity();
  luminosidade = 0;   //MUDAR P/ LEITURA DO SENSOR DE LUMINOSIDADE E APAGAR COMENTÁRIO.

  if (isnan(temperatura) || isnan(humidade)) {
    Serial.println("Falha na leitura do sensor!");
  } else {
    //Impressão de temperatura no monitor serial:
    Serial.print("Temperatura: ");
    Serial.print(temperatura, 1);
    Serial.println("ºC");
    //Impressão de temperatura no display:
    lcd.setCursor(14, 0);
    lcd.print(temperatura, 1);
    
    //Impressão de humidade no monitor serial:
    Serial.print("Humidade: ");
    Serial.print(humidade, 1);
    Serial.println("%");
    //Impressão de humidade no display:
    lcd.setCursor(12, 1);
    lcd.print(humidade, 1);

    //Impressão de luminosidade no monitor serial:
    Serial.print("Luminosidade: ");
    Serial.println(luminosidade);
    //Impressão de luminosidade no display:
    lcd.setCursor(15, 2);
    lcd.print(luminosidade);
  }
  delay(5000);   //Intervalo de leitura a cada 5s.
}
