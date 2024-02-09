#include <Key.h>
#include <Keypad.h>
#include <LiquidCrystal.h>

const byte numLinhas = 4;   //Quantidade de linhas do teclado
const byte numColunas = 4;  //Quantidade de colunas do teclado

float f_vlr1 = 0;
float f_vlr2 = 0;
float f_res = 0;
String s_vlr1 = "";
String s_vlr2 = "";
String s_res = "";
String s_temp = "";
char opr = "";

//Matriz de caracteres referente aos botões do teclado
char teclasMatriz[numLinhas][numColunas] = {
  { '1', '2', '3', '+' },
  { '4', '5', '6', '-' },
  { '7', '8', '9', 'x' },
  { '=', '0', '.', '/' }
};

byte pinosLinhas[numLinhas] = { 9, 8, 7, 6 };      //Pinos das linhas
byte pinosColunas[numColunas] = { 10, 11, 12, 13 };  //Pinos das Colunas

//pinagem LCD
#define V0   5 //Contraste Controlado PWM
#define RS   4
#define RW   3
#define E    2
#define D4   14
#define D5   15
#define D6   16
#define D7   17

//Cria um objeto do tipo Keypad
Keypad meuteclado = Keypad(makeKeymap(teclasMatriz), pinosLinhas,
                           pinosColunas, numLinhas, numColunas);
//inicializa LCD
LiquidCrystal lcd(RS, RW, E, D4, D5, D6, D7);

void setup() {
  Serial.begin(9600);                    //Inicia a comunicação serial
  Serial.println("Aperte um botão...");  //Imprime mensagem no monitor serial
  lcd.begin(16, 2);//Colunas, linhas. Use 16,2 para display LCD 16x2
  pinMode(V0, OUTPUT);
  analogWrite(V0, 350);// Liga backlight. Testar valor de melhor contraste.
  lcd.display();// Liga Display:
  lcd.clear();
  lcd.setCursor(15,1);
  lcd.print('0');
}

void loop() {
  char pressionado = meuteclado.getKey();  ///Verifica se alguma tecla foi pressionada
  if (pressionado) {                       //Se alguma tecla foi pressionada
    Serial.print("Botão pressionado: ");   //Imprime mensagem no monitor serial
    Serial.println(pressionado);           //Imprime tecla pressionada

    switch (pressionado) {
      case '+':
        {
          opr = pressionado;
          f_vlr1 = s_temp.toFloat();
          s_vlr1 = s_temp;
          s_temp = "";
          Serial.println(String(f_vlr1));
          lcd.clear();
          lcd.setCursor(16-s_vlr1.length(), 0);
          lcd.print(s_vlr1);
          lcd.setCursor(15, 1);
          lcd.print("+");
          break;
        }
      case '-':
        {
          opr = pressionado;
          f_vlr1 = s_temp.toFloat();
          s_vlr1 = s_temp;
          s_temp = "";
          Serial.println(String(f_vlr1));
          lcd.clear();
          lcd.setCursor(16-s_vlr1.length(), 0);
          lcd.print(s_vlr1);
          lcd.setCursor(15, 1);
          lcd.print("-");      
          break;
        }
      case 'x':
        {
          opr = pressionado;
          f_vlr1 = s_temp.toFloat();
          s_vlr1 = s_temp;
          s_temp = "";
          Serial.println(String(f_vlr1));
          lcd.clear();
          lcd.setCursor(15-s_vlr1.length(), 0);
          lcd.print(s_vlr1);
          lcd.setCursor(15, 1);
          lcd.print("x");          
          break;
        }
      case '/':
        {
          opr = pressionado;
          f_vlr1 = s_temp.toFloat();
          s_vlr1 = s_temp;
          s_temp = "";
          Serial.println(String(f_vlr1));
          lcd.clear();
          lcd.setCursor(16-s_vlr1.length(), 0);
          lcd.print(s_vlr1);
          lcd.setCursor(15, 1);
          lcd.print("/");
          break;
        }
      case '=':
        {
          f_vlr2 = s_temp.toFloat();
          s_vlr2 = s_temp;
          s_temp = "";
          s_res = "";
          Serial.print("Valor 2: ");
          Serial.println(String(f_vlr2));
          switch (opr) {
            case '+':
              {
                f_res = f_vlr1 + f_vlr2;
                s_res = String(f_res);
                Serial.println(s_res);
                lcd.clear();
                lcd.setCursor(16-s_res.length(), 1);
                lcd.print(s_res);
                break;
              }
            case '-':
              {
                f_res = f_vlr1 - f_vlr2;
                s_res = String(f_res);
                Serial.println(s_res);
                lcd.clear();
                lcd.setCursor(16-s_res.length(), 1);
                lcd.print(s_res);
                break;
              }
            case 'x':
              {
                f_res = f_vlr1 * f_vlr2;
                s_res = String(f_res);
                Serial.println(s_res);
                lcd.clear();
                lcd.setCursor(16-s_res.length(), 1);
                lcd.print(s_res);              
                break;
              }
            case '/':
              {
                if(f_vlr2 == 0) return;
                f_res = f_vlr1 / f_vlr2;
                s_res = String(f_res);
                Serial.println(s_res);
                lcd.clear();
                lcd.setCursor(16-s_res.length(), 1);
                lcd.print(s_res);               
                break;
              }
          }
          break;
        }
      default:
        {
          //s_temp = pressionado;
          s_temp.concat(pressionado);
          Serial.println(s_temp);
          lcd.clear();
          lcd.setCursor(16-s_temp.length(), 1);
          lcd.print(s_temp);
          break;
        }
    }
  }
}
