#include "tinyexpr.h"

float x;
te_variable vars[] = {{"x", &x}}; 

void setup(){
  Serial.begin(9600);
  
}
//function jeda menunggu user menginput data via serial
void waitInput(){
   while(Serial.available() == 0){};
}

void loop(){
  //Input user via serial
  Serial.print("Masukkan fungsi f(x) = ");
  waitInput();
  String fx_str = Serial.readString();
  te_expr* fx = te_compile(fx_str.c_str(), vars, 2, 0);
  Serial.println(fx_str);
  
  Serial.print("Masukkan Nilai a = ");
  waitInput();
  String a_str = Serial.readString();
  float a = a_str.toFloat();
  Serial.println(a, 5);

  Serial.print("Masukkan Nilai b = ");
  waitInput();
  String b_str = Serial.readString();
  float b = b_str.toFloat();
  Serial.println(b, 5);

  Serial.print("Masukkan Nilai eps = ");
  waitInput();
  String eps_str = Serial.readString();
  float eps = eps_str.toFloat();
  Serial.println(eps, 5);

  delay(2000);

  //Menghitung nilai f(a) dan f(b)
  x = a;
  float fa  = te_eval(fx);
  x = b;
  float fb = te_eval(fx);

  //Mengecek hasil perkalian f(a).f(b)
  if(fa*fb < 0){
     //Lakukan Iterasi
     for(int i = 1; i <= 100; i++){
         float c = (a+b)/2;
         x = c;
         float fc = te_eval(fx);
         //Menentukan a dan b untuk iterasi selanjutnya
         if(fc*fa < 0){
            b = c;
            fb = fc;
         }
         else if (fc*fa > 0){
           a  = c;
           fa = fc;
         }
         else{ //fc*fa == 0
            break;
         }
          //Hitung nilai error
          float error = abs(b-a);
          //Cetak data setiap iterasi
          Serial.print("i = ");
          Serial.println(i);
          Serial.print("a = ");
          Serial.println(a, 5);
          Serial.print("b = ");
          Serial.println(b, 5);
          Serial.print("c = ");
          Serial.println(c, 5);
          Serial.print("f(a) = ");
          Serial.println(fa, 5);
          Serial.print("f(b) = ");
          Serial.println(fb, 5);
          Serial.print("f(c) = ");
          Serial.println(fc, 5);
          Serial.print("|b-a| = ");
          Serial.println(error, 5);
          Serial.println("-----------------------------");
         //cek saat kapan iterasi dihentikan
         if(error <= eps){
            Serial.print("Akar Fungsi = ");
            Serial.println(c, 5);
            Serial.print("Jumlah Iterasi = ");
            Serial.println(i);
            Serial.println("-----------------------------");
            break;
         }
        delay(100);
     }
  }
  else{
    Serial.println("\nTentukan interval [a,b] yang baru");
  }
 delay(2000); 
}

