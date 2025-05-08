#include <cstdio>

// gib die Wurzel von x zurück (Heron-Verfahren):
float heron(float x) {
  float a = x;
  float b = 1;

  // setze wiederholend a auf das arithmetische Mittel von a und b
  // (und b so, dass a*b=x bleibt) -- maximal 100 Wiederholungen und
  // bis die Genauigkeit von .00001 erreicht ist:
  int zaehler = 0;  // Zaehler fuer die #Wiederholungen
  while ((a - b) > .00001 && zaehler < 100) {
    a = (a + b) / 2;  // arithmetische Mittel
    b = x / a;        // setze b so, dass a*x==b bleibt
    ++zaehler;
  }
  return a;
}

int main() {
  float x = 23194514;
  printf("Die Quadratwurzel von %f ist %f\n", x, heron(x));
}
