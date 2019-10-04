#include <IRremote.h>
#include <LiquidCrystal.h>

//Variables de manejo pantalla LCD
LiquidCrystal lcd(12,11,4,5,6,7);

/*Variables de activacion de sesion
const int boton = 8;
int estado = 0;*/

//Variables de sintonizacion
int pos=0,i;
String sintonia = "";
String canal;

// Variables de temporizacion 
byte cuenta = 0;
long reg_auxi = 0;
int segundo = 0;

//long seg_acum = 0;
long min_acum = 0;
long seg_acum =0;
byte minuto = 0;
int hora = 0;
//byte hora_L = 0;
//byte hora_H = 0;

void setup()
{
  Serial.begin(9600);
  //pinMode(boton,INPUT);
  lcd.begin(16,2);
  
  lcd.blink(); 
  delay(1500);
  lcd.noBlink(); 
  lcd.print("BIENVENIDO!!!!!!!!!"); 
  delay(4000);
  //lcd.clear();
  lcd.setCursor(0,1); // Seteamos la ubicacion texto 0 linea 1 que sera escrita sobre el LCD
  lcd.print("RATING CONTROL");
  delay(4000);
  lcd.clear(); 

  lcd.print("Por favor");
  lcd.setCursor(1,1);
  lcd.print("Inicie Sesion...");
  delay(8000);
  lcd.clear(); 

  lcd.blink(); 
  delay(5000);
  lcd.noBlink(); 
}

void loop() 
{
 


 //estado= digitalRead(boton);
 infrarrojo(); //Llamada a la funcion principal

 //Condicional de temporizacion
 if (millis() - reg_auxi >= 1000) {  
    segundo++; 
    //seg_acum++;
    reg_auxi = millis(); //millis transcurridos guardados en la variable auxiliar

    //Condicional para los segundos transcurridos
    if (segundo == 60){  
      minuto++;  
      min_acum++; 
      segundo=0;  
    }

    //Condicional para los minutos transcurridos
    if (minuto == 60){ 
      hora++;  
      minuto = 0;  
      segundo=0; 
    }

    /*//bandera de emision
    if (minuto == 1 && segundo == 0){
      Serial.print("!");
      }*/
  
  }
  cuenta++;
  delay(10);
}

void infrarrojo()
{
  IRsend ir;
  char dato;
  String grilla[19] = {"K","M","N","P","R","JJ","JL","JQ","KJ","KP","LI","LK","LO","LR","MJ","MN","MR","NI","NJ"};
  
  if((Serial.available()>0))
  { 
    dato = Serial.read();
    canal+= dato;
    if ((canal.charAt(canal.length() - 1) == 'H') || (canal.charAt(canal.length() - 1) == 'C')||(canal.charAt(canal.length() - 1) == 'D') ) {
        canal="";
    }
    delay (50);
    lcd.clear();
    lcd.print("RATING CONTROL");
    //delay(10000);
    lcd.setCursor(10,1);
    lcd.print ("CH");
    
    switch (dato)  
    {
        //PowerTV       
        case 'A':       
        {
          ir.sendNEC(0xFDC03F, 32);
          delay(50);
        }
        break;
        
        //Mute
        case 'B':
        {
          ir.sendNEC(0xFDA857, 32);
          delay(50);
        }
        break;
        
        //ChanelUp
        case 'C':
        {
          ir.sendNEC(0xFD28D7, 32);
          delay(50);
          if(pos<=18){
            pos=pos+1;
            sintonia = grilla[pos]; 
          }

          if (pos==19){
            sintonia = grilla[0];
            pos=0;   
          }  
          Serial.print(sintonia + "#");
          lcd.setCursor(13,1);
          lcd.print(sintonia);
        }
        break;
        
        //ChanelDown
        case 'D':
        {
          ir.sendNEC(0xFD18E7, 32);
          delay(50);

          if (pos>=0) {
            pos=pos-1;
            sintonia = grilla[pos]; 
          }
      
          if (pos==-1){
            sintonia = grilla[18];
            pos=18;    
          }
          Serial.print(sintonia + "#");
          lcd.setCursor(13,1);
          lcd.print(sintonia); 
        }
        break;
        
        //VolumenUp
         case 'E':
        {
          ir.sendNEC(0xFD6897, 32);
          delay(50);
        }
         break;
         
         //VolumenDown
         case 'F':
        {
          ir.sendNEC(0xFD58A7, 32);
          delay(50);
        }
         break;
         
         //Punto
         case 'G':
        {
          ir.sendNEC(0xFDF00F, 32);
          delay(50);
        }
         break;
         
         //Enter
         case 'H':
        {
          ir.sendNEC(0xFD827D, 32);
          delay(50);
        }
         break;
         
//TECLADO 0 AL 9
        //Num_0
         case 'I':
        {
          ir.sendNEC(0xFDB04F, 32);
          delay(50);
        }
         break;
         
         //Num_1
         case 'J':
        {
          ir.sendNEC(0xFD00FF, 32);
          delay(50);
        }
         break;
         
         //Num_2
         case 'K':
        {
          ir.sendNEC(0xFD807F, 32);
          delay(50);
        }
         break;
         
         //Num_3
         case 'L':
        {
          ir.sendNEC(0xFD40BF, 32);
          delay(50);
        }
         break;
         
         //Num_4
         case 'M':
        {
          ir.sendNEC(0xFD20DF, 32);
          delay(50);
        }
         break;
         
         //Num_5
         case 'N':
        {
          ir.sendNEC(0xFDA05F, 32);
          delay(50);
        }
         break;
         
         //Num_6
         case 'O':
        {
          ir.sendNEC(0xFD609F, 32);
          delay(50);
        }
         break;
         
         //Num_7
         case 'P':
        {
          ir.sendNEC(0xFD10EF, 32);
          delay(50);
        }
         break;
         
         //Num_8
         case 'Q':
        {
          ir.sendNEC(0xFD906F, 32);
          delay(50);
        }
         break;
         
         //Num_9
         case 'R':
        {
          ir.sendNEC(0xFD50AF, 32);
          delay(50);
        }
         break;

    }  // fin del switch 
//Serial.print (canal);
//Condicional para toma de datos
    for (i=0; i<=18; i++){
        
         if(canal == grilla[i]){
            sintonia= grilla[i];  
            Serial.print(sintonia + "#");
            lcd.setCursor(13,1);
            lcd.print(sintonia); 
            pos=i;  
          }
       }

//Condicional para reiniciar la temporizacion
 if ((canal == 'C') ||(canal == 'D') || (canal == 'H'))
    {
        //Impresion de duracion en un canal
        Serial.print(hora);
        Serial.print(":");
        Serial.print(minuto);
        Serial.print(":");
        Serial.print(segundo);
        Serial.print("%");
     
        delay(50);
        
        segundo=0;
        seg_acum=0;
        min_acum=0;
        minuto=0;
        hora=0;
    }
  } //fin del if
  
  /*else{
  lcd.setCursor(2,0);
  lcd.print ("BIENVENIDO!!!");
  delay(1000);
  lcd.clear();
    lcd.clear();
    lcd.print("Gracias por usar");
    lcd.print("el sistema...");
    delay(500);
    lcd.print("HASTA PRONTO!!!"); 
  }*/
}
