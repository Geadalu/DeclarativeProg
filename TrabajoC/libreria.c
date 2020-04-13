#include <stdio.h>
#include <SWI-Prolog.h>

//TODO: sumar y multiplicar dos matrices

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

//Pasar de lista a matriz en C
int lists_toMatrix(term_t list_ofLists, Matrix_C* matrix){
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

//Pasar de matriz en C a lista de Prolog
int matrix_toList(Matrix_C* matrix, term_t term){
	int i, j;
	
	if(!PL_put_nil(term)){
		fprintf(stderr, "Error pasando la matriz a lista en PL_put_nil(term)\n");
		return 0;
	}
	
	for (i=matrix->rows-1; i>=0; i--){
		term_t currentRow = PL_new_term_ref();
		if(!PL_put_nil(currentRow)){
			fprintf(stderr, "Error pasando la matriz a lista en PL_put_nil(cR)\n");
			return 0;
		}
		for(j=matrix->columns-1; j>=0; j--){
			term_t aux_t = PL_new_term_ref();
			if(!PL_put_float(aux_t, matrix->matrix[j+i*matrix->columns])){
				fprintf(stderr, "Error pasando la matriz a lista en PL_put_float\n");
				return 0;
			} else if(!PL_cons_list(currentRow, aux_t, currentRow)){
				fprintf(stderr, "Error pasando la matriz a lista en PL_cons_list\n");
				return 0;
			}
		}
		if(!PL_cons_list(term, currentRow, term)){
			fprintf(stderr, "Error pasando la matriz a lista en PL_cons_list\n");
			return 0;
		}
	}
	return 1;
}

// pl_multiply_matrix 
//Multiplicar número por matriz
foreign_t pl_multiply_matrix (term_t multip, term_t list_ofLists, term_t rows, term_t columns, term_t result){
	int i=0;
	int multiplier;
	int rows_, columns_;

	if(PL_is_integer(multip)){
		if(!PL_get_integer(multip, &multiplier)){
			fprintf(stderr, "La variable multiplicador no es válida\n");
			PL_fail;
		}
	}

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

	for (i=0; i<matrix->rows*matrix->columns; i++){
		matrix->matrix[i] = matrix->matrix[i]*multiplier;
	}

	term_t aux = PL_new_term_ref();
	if (!matrix_toList(matrix, aux)){
		fprintf(stderr, "Error pasando la matriz a lista\n");
		PL_fail;
	}
	return PL_unify(aux, result);
}

//sumar todos los números de la matriz
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
	PL_register_foreign("mult_matrix", 5, pl_multiply_matrix, 0);
}
