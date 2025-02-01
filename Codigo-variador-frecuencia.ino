#include "esp_timer.h" // Biblioteca de temporizadores de ESP32

// Definición de pines
int q1 = 12, q4 = 13, q3 = 14, q6 = 27, q5 = 26, q2 = 25;
int pulsador1 = 32, pulsador2 = 33;

// Variables de conteo
int cnt = 0, cnt2 = 0, sPeriodo = 83;
int cnt_2 = 0, cnt2_2 = 3;
int cnt_3 = 0, cnt2_3 = 6;

float x[9] = {12.8, 24.4, 33.7, 39.6, 41.6, 39.6, 33.7, 24.4, 12.8}; // 60Hz

// Estados
int estado1 = 0, estado1_2 = 0, estado1_3 = 0;

// Manejador del timer
esp_timer_handle_t timer;

// Declaración de funciones
void pwm_generador(void *param);
void spwm1();
void spwm2();
void spwm3();

void setup() {
  Serial.begin(115200);

  // Configuración de pines de salida
  pinMode(q1, OUTPUT); pinMode(q2, OUTPUT);
  pinMode(q3, OUTPUT); pinMode(q4, OUTPUT);
  pinMode(q5, OUTPUT); pinMode(q6, OUTPUT);

  // Configuración de pulsadores
  pinMode(pulsador1, INPUT_PULLUP);
  pinMode(pulsador2, INPUT_PULLUP);

  // Configuración del temporizador usando esp_timer
  const esp_timer_create_args_t timer_args = {
      .callback = &pwm_generador, // Función que se llama periódicamente
      .arg = NULL,
      .dispatch_method = ESP_TIMER_TASK, // Ejecuta la función en una tarea
      .name = "spwm_timer"};

  // Crear y arrancar el temporizador (10us)
  esp_timer_create(&timer_args, &timer);
  esp_timer_start_periodic(timer, 10); // 10us
}

void loop() {
  // Leer el estado de los pulsadores (sin lógica adicional)
  int p1 = digitalRead(pulsador1);
  int p2 = digitalRead(pulsador2);
}

// Función llamada periódicamente por el temporizador
void pwm_generador(void *param) {
  spwm1();
  spwm2();
  spwm3();
}

// Funciones SPWM
void spwm3() {
  if (cnt_3 < sPeriodo) {
    cnt_3++;
    if (cnt_3 < x[cnt2_3]) {
      digitalWrite(estado1_3 == 0 ? q5 : q2, HIGH);
    } else {
      digitalWrite(estado1_3 == 0 ? q5 : q2, LOW);
    }
  } else {
    cnt_3 = 0;
    cnt2_3 = (cnt2_3 < 8) ? cnt2_3 + 1 : 0;
    estado1_3 = (cnt2_3 == 0) ? !estado1_3 : estado1_3;
    digitalWrite(q5, LOW);
    digitalWrite(q2, LOW);
  }
}

void spwm2() {
  if (cnt_2 < sPeriodo) {
    cnt_2++;
    if (cnt_2 < x[cnt2_2]) {
      digitalWrite(estado1_2 == 0 ? q6 : q3, HIGH);
    } else {
      digitalWrite(estado1_2 == 0 ? q6 : q3, LOW);
    }
  } else {
    cnt_2 = 0;
    cnt2_2 = (cnt2_2 < 8) ? cnt2_2 + 1 : 0;
    estado1_2 = (cnt2_2 == 0) ? !estado1_2 : estado1_2;
    digitalWrite(q6, LOW);
    digitalWrite(q3, LOW);
  }
}

void spwm1() {
  if (cnt < sPeriodo) {
    cnt++;
    if (cnt < x[cnt2]) {
      digitalWrite(estado1 == 0 ? q1 : q4, HIGH);
    } else {
      digitalWrite(estado1 == 0 ? q1 : q4, LOW);
    }
  } else {
    cnt = 0;
    cnt2 = (cnt2 < 8) ? cnt2 + 1 : 0;
    estado1 = (cnt2 == 0) ? !estado1 : estado1;
    digitalWrite(q1, LOW);
    digitalWrite(q4, LOW);
  }
}