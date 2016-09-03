#include <TimerOne.h>   // inclui biblioteca Timer1
#define triacApin 4 // Define que o Dimmer será comandado pelo pino 4
#define sirene 7
int frequencia = 60;
int stateTriacA = 0;
int power = 0;  //inicializa variavel que controla potencia na lampada com 0 (lampada apagada)
int aux;
int i = 0; //contador de ocorrencia de alarme
int alarme_state = 0;

void setup() {
  // initialize serial:
  Serial.begin(9600);
pinMode(triacApin, OUTPUT);
pinMode(sirene, OUTPUT);
digitalWrite(sirene,LOW); //Inicializa sirene desligada
digitalWrite(triacApin, LOW); // Triac inicializa desligado
// Initialize the interruption time Timer1
Timer1.initialize(); // Initialize TimerOne library for the freq we need
// interrupção no pino dois (interrupção zero) como detector de zero
attachInterrupt(0, zero_cross_detect, CHANGE);
// Interrupcao alarme pino 3 do arduino
attachInterrupt(1, alarme, RISING);  
}

void loop() {
}

//A cada evento do serial esta função é chamada no loop principal
void serialEvent() {
    char inChar = (char)Serial.read(); 
    
    aux = (int)inChar;
    aux = aux - 48;
 

    if(aux>= 0 && aux <= 5)
    {
      if (aux ==1)
        power = 20;
      else if (aux == 5)
      power = 95;
      else
      power = 18*aux;
    //Serial.println(power);
    }
   
    if (aux==7)
    {
alarme_state = 1;
    }
    
    if (aux == 8)
    {
alarme_state = 0;
digitalWrite(sirene,LOW);
    }
}

// FUNCOES CONTROLE POTENCIA

//Funcao chmada pela interrupcao 0 referente a deteccao de zero da senoide
void zero_cross_detect()
{
if(power > 0){
long dimtime = int(map(power,0,100,8000,150));  // calcula o tempo de delay para o disparo do TRIAC 7950,100
Timer1.attachInterrupt(gateTRIAC, dimtime);  //associa a funcao gateTRIAC com Interrupcao do TIMER1
Timer1.start();  // inicia contagem TIMER1
}else
{
digitalWrite(triacApin, LOW);   // mantem gate do TRIAC desativado.
Timer1.stop();
}
}

// Funcao chamada pela interrupcao do timer para disparo do triac
void gateTRIAC ()
{  // trata interrupcao do TIMER1 gerando pulso no gate do TRIAC
digitalWrite(triacApin, HIGH);  // dispara o Triac
delayMicroseconds(5);//aguarda 5 microsegundos para garantir //disparo do TRIAC
digitalWrite(triacApin, LOW);   // desabibilta gate do TRIAC
Timer1.stop();
}

//Funcao chamada pela interrupcao 1 referente ao alarme
void alarme()
{
  //se o alarme estiver ativo
 if(alarme_state==1)
 {
//comando enviado a porta serial para o código em python
Serial.write('R');
//liga a sirene
digitalWrite(sirene,HIGH);
}
}
