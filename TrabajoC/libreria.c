#include <stdio.h>
#include <SWI-Prolog.h>

typedef struct {
  int rows;
	int columns;
	double* matrix;
	
}Matrix_C;

//Inicializamos el espacio de memoria necesario para la matriz
Matrix_C* createMatrix(int rows, int columns){
	Matrix_C* matrix = calloc(1, sizeof(Matrix_C));
	matrix->rows = rows;
	matrix->columns = columns;
	matrix->matrix = calloc(rows*columns, sizeof(double));
	return matrix;
}

//para poner una lista en una fila de una array
int list_toRow(int currentIndex, term_t list, Matrix_C* matrix){
	fprintf(stderr, "hello world!\n");
	double number_d = 0.0;
	int number_i = 0;
	int i = 0;
	double aux = 0;	

	if (!PL_is_list(list))
		return 0;
	
	term_t head = PL_new_term_ref();
	term_t tail = PL_copy_term_ref(list);

	for (i=0; i<matrix->columns; i++){
	
		if(!PL_get_list(tail, head, tail))
			return 0;

		if (!PL_is_number(head))
			return 0;

		if (PL_is_float(head)){
			if (PL_get_float(head, &number_d)){
				matrix->matrix[i+currentIndex*matrix->columns] = number_d;
			}
		} else {
			if (PL_get_integer(head, &number_i)){
				aux = (double) number_i;
				matrix->matrix[i+currentIndex*matrix->columns] = aux;
			}
		}
	}
	return 1;
}


int lists_toMatrix(term_t list_ofLists, Matrix_C* matrix){
	fprintf(stderr, "hello world!\n");
	term_t head = PL_new_term_ref();
	term_t tail = PL_copy_term_ref(list_ofLists);
	int i;

	for (i=0; i<matrix->rows; i++){

		if(!PL_get_list(tail, head, tail))
			return 0;

		if (list_toRow(i, head, matrix) == 0){
			fprintf(stderr, "Error pasando la fila %d a matriz\n", i);
			return 0;
		}
	}
 return 1;
}

foreign_t pl_sum_matrix (term_t list_ofLists, term_t rows, term_t columns, term_t result){
	int i;
	int rows_ = 0;
	int columns_ = 0;

	if (PL_is_integer(rows)){
		if(!PL_get_integer(rows, &rows_)){
			fprintf(stderr, "La variable filas no es válida\n");
			PL_fail;
		}
	}

	if (PL_is_integer(columns)){
		if(!PL_get_integer(columns, &columns_)){
			fprintf(stderr, "La variable columnas no es válida\n");
			PL_fail;
		}
	}

	//Convertir la lista de listas a Matrix_C
	Matrix_C* matrix = createMatrix(rows_, columns_);
 	if (lists_toMatrix(list_ofLists, matrix) == 0){
		fprintf(stderr, "Error pasando la lista a matriz\n");
		PL_fail;
	}

	for (i=0; i<rows_*columns_; i++){
		fprintf(stderr, "%f\n", matrix->matrix[i]);
	}

	double sum = 0;

	for (i=0; i<matrix->rows*matrix->columns; i++){
		sum += matrix->matrix[i];
	}

	term_t r = PL_new_term_ref();

	if(PL_put_float(r, sum)){
		return PL_unify(r, result);
	} else {
		PL_fail;
	}
}

install_t install() {
	PL_register_foreign("sum_matrix", 4, pl_sum_matrix, 0);
}
