#include <stdio.h>
/* Nome_do_Aluno1: Charbel Janos Freitas Matricula: 2510373 Turma: 3WA        */
/* Nome_do_Aluno2: Davi Teixeira Mendes Almeida Matricula: 2510420 Turma: 3WA */

typedef enum {INT_PAR, PTR_PAR} TipoValor;
typedef enum {PARAM, FIX, IND} OrigemValor;

typedef struct {
   TipoValor    tipo_val;  /* indica o tipo do parametro (inteiro ou ponteiro) */
   OrigemValor  orig_val;  /* indica a origem do valor do parametro */
   union {
     int v_int;
     void* v_ptr;
   } valor;         /* define o valor ou endereço do valor do parametro (quando amarrado/indireto) */
} DescParam;

void cria_func (void* f, DescParam params[], int n, unsigned char codigo[]){

}

int main(){
    
    return 0;
}