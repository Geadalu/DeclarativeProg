#include <stdio.h>
#include <SWI-Prolog.h>

foreign_t pl_sum_num(term_t n1, term_t n2, term_t result){
	int num1, num2 = 0;

	if (!PL_get_integer(n1, &num1))
		PL_fail;
	if (!PL_get_integer(n2, &num2))
		PL_fail;
	term_t res = PL_new_term_ref();

	PL_put_integer(res, num1 + num2);

	return PL_unify(res, result);
}

install_t install() {
	PL_register_foreign("sum_num", 3, pl_sum_num, 0);
}

//swipl-ld -c  ejemplo.c --> compilar librería
//swipl-ld -shared -o library.so ejemplo.o --> pasar librería a PL
//load_foreign_library(library). --> en la interfaz de prolog para cargar librería
//Ahora se usa lo que has puesto en el install ("sum_num")

//En general, un programa de estos:
//1. Pasar de terminos Prolog a cosas en C
//2. Hacer las operaciones en C
//3. Pasar cosas en C a cosas en Prolog
