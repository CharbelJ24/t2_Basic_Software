/* Davi Teixeira 2510420 3WA */
/* Charbel Janos 2510373 3WA */

#include <stdio.h>

typedef enum {INT_PAR, PTR_PAR} TipoValor;
typedef enum {PARAM, FIX, IND} OrigemValor;

typedef struct {
   TipoValor tipo_val;
   OrigemValor orig_val;
   union {
     int v_int;
     void* v_ptr;
   } valor;
} DescParam;

void cria_func (void* f, DescParam params[], int n, unsigned char codigo[]){

  for(int i = 0; i < n; i++){
    if(params[i] == orig_valor.FIX){
      codigo = {
        
      }
    }
    else if(params[i] == orig_valor.IND){
      codigo = {
        
      }
    }
  }

  return codigo;
}

int main(){
    
    return 0;
}