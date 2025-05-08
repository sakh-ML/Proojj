#include <cstdio>

#include "io.hpp"
#include "printall.hpp"

// gibt Position des Minimums in array[j,length-1] zurück:
template <typename T>
int min_pos(T array[], int length, int j) {
  int min_pos_so_far = j;  // position of smallest elt. seen so far
  for (int i = j + 1; i < length; ++i) {
    if (array[i] < array[min_pos_so_far]) min_pos_so_far = i;
  }
  return min_pos_so_far;
}

// sortiere das Array - das gleiche wie x_th_smallest(array, length, n),
// nur ohne Rückgabewert (dies heißt "selection sort" - Sortieren durch
// Auswahl):
template <typename T>
void sort(T array[], int length) {
  for (int i = 0; i < length; ++i) {
    // find minimum in array[i,length-1]:
    int j = min_pos(array, length, i);

    // swap array[i] with array[j]
    T tmp = array[i];     // sichere den Wert array[i] vor dem Überschreiben
    array[i] = array[j];  // überschreibt den Wert array[i] mit array[j]
    array[j] = tmp;  // schreibe den ursprünglichen Wert array[i] nach array[j]
  }
}

// entscheide, ob x im AUFSTEIGEND SORTIERTEN array[0,length-1] vorkommt (binäre
// Suche):
template <typename T, typename U>
bool find_faster(T const array[], int length, U x) {
  // left/right: linke/rechte Grenze im noch zu durchsuchenden Array:
  int left = 0, right = length - 1;  // initialisiere

  while (right >= left) {  // solange das Suchintervall noch nicht leer ist
    int middle = (left + right) / 2;  // Mitte des noch durchsuchenden Arrays
    if (x == array[middle]) return true;
    if (x < array[middle])
      right = middle -
              1;  // falls x vorhanden, muss es in array[left,middle-1] sein
    else
      left = middle +
             1;  // falls x vorhanden, muss es in array[middle+1,right] sein
  }
  return false;  // x nicht gefunden => return false
}

int main() {
  float noten[] = {2.7, 1.0, 1.0, 4.0, 5.0};
  sort(noten, 5);
  print_all(noten, 5);
  if (find_faster(noten, 5, 4))
    printf("die Note 4.0 wurde gefunden\n");
  else
    printf("die Note 4.0 wurde NICHT gefunden\n");
}
