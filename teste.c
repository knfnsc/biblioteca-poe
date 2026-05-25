#include "terminal_usuarios.h"
#include <stdio.h>
#include <stdlib.h>

Usuario * alocar_usuarios(){
    Usuario *usuario = calloc(100, sizeof(Usuario));

    if(usuario == NULL){
        printf("Falha no sistema.\n");
        exit(1);
    }

    return usuario;
}

int main(){

Usuario *u = alocar_usuarios();

terminal_usuarios(u);

return 0;

}
