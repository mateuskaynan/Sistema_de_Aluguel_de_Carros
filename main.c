#include "sistema.c" 

int main() {
    Sistema sistema = {NULL, NULL};
    carrega_dados(&sistema);
    menu(&sistema);
    libera_memoria(&sistema);
    return 0;
}