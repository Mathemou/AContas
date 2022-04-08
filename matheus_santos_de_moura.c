#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "arv.h"

int main(void) {
  leEntradaEPrintaSaida();
  return 0;
}

//valgrind --leak-check=full --show-leak-kinds=all ./main