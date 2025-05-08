#include <cstdio>

// gibt die #Zeilen einer Datei zurück:
int count_lines(FILE* file) {
  rewind(file);  // gehe zurück zum Anfang der Datei
  int lines = 0;
  char zeichen;
  while (!feof(file)) {  // solange nicht am Dateiende wiederhole
    zeichen = fgetc(file);
    if (zeichen == '\n') ++lines;  // falls zeichen ein newline ('\n')
  }
  rewind(file);
  return lines;
}
