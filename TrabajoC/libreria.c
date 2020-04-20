#include <stdio.h>
#include <SWI-Prolog.h>

typedef struct {
  int rows;
	int columns;
	double* matrix;
	
}Matrix_C;

//createMatrix
//Inicializamos el espacio de memoria necesario para la matriz
Matrix_C* createMatrix(int rows, int columns){
	Matrix_C* matrix = calloc(1, sizeof(Matrix_C));
	matrix->rows = rows;
	matrix->columns = columns;
	matrix->matrix = calloc(rows*columns, sizeof(double));
	return matrix;
}

//destroyMatrix
//Liberamos la memoria del sistema
void destroyMatrix(Matrix_C* matrix){
	free(matrix);
	matrix = NULL;
}

//checkInteger
//Comprueba si el term_t introducido es un integer
int checkInteger(int* integer, term_t term){
	if(PL_is_integer(term)){
		if(!PL_get_integer(term, integer)){
			return 0;
		}
		return 1;
	} else {
		return 0;
	}
}

//list_toRow
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

//list_toMatrix
//Pasar de lista a matriz en C
int list_toMatrix(term_t list_ofLists, Matrix_C* matrix){
	term_t head = PL_new_term_ref();
	term_t tail = PL_copy_term_ref(list_ofLists);
	int i;

	for (i=0; i<matrix->rows; i++){

		if(!PL_get_list(tail, head, tail)){
			fprintf(stderr, "Error recogiendo la lista.\n");
			return 0;
		}

		if (list_toRow(i, head, matrix) == 0){
			fprintf(stderr, "Error pasando la fila %d a matriz\n", i);
			return 0;
		}
	}
 return 1;
}

//matrix_toList
//Pasar de matriz en C a lista de Prolog
int matrix_toList(Matrix_C* matrix, term_t term){
	int i, j;
	
	if(!PL_put_nil(term)){
		fprintf(stderr, "Error creando la lista vacía\n");
		return 0;
	}
	
	for (i=matrix->rows-1; i>=0; i--){
		term_t currentRow = PL_new_term_ref();
		if(!PL_put_nil(currentRow)){
			fprintf(stderr, "Error creando la lista vacía\n");
			return 0;
		}
		for(j=matrix->columns-1; j>=0; j--){
			term_t aux_t = PL_new_term_ref();
			if(!PL_put_float(aux_t, matrix->matrix[j+i*matrix->columns])){
				fprintf(stderr, "Error recogiendo un número float de la matriz.\n");
				return 0;
			} else if(!PL_cons_list(currentRow, aux_t, currentRow)){
				fprintf(stderr, "Error construyendo una fila de la lista.\n");
				return 0;
			}
		}
		if(!PL_cons_list(term, currentRow, term)){
			fprintf(stderr, "Error añadiendo una fila a la lista.\n");
			return 0;
		}
	}
	return 1;
}


								//AQUÍ EMPIEZAN LOS PREDICADOS DE PROLOG//


//mult_matrix_by(2, [[2], [3], [4], [5]], 4, 1, R).
// pl_multiply_matrix_by 
//Multiplicar número por matriz
foreign_t pl_multiply_matrix_by (term_t multiplier_, term_t list_ofLists, term_t rows_, term_t columns_, term_t result){
	int i=0;
	int multiplier;
	int rows, columns;

	if(!checkInteger(&multiplier, multiplier_)){
		fprintf(stderr, "La variable multiplier no es válida\n");		
		PL_fail;
	}

	if(!checkInteger(&rows, rows_)){
		fprintf(stderr, "La variable rows no es válida\n");		
		PL_fail;
	}

	if(!checkInteger(&columns, columns_)){
		fprintf(stderr, "La variable columns no es válida\n");		
		PL_fail;
	}

	Matrix_C* matrix = createMatrix(rows, columns);
 	if (list_toMatrix(list_ofLists, matrix) == 0){
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

	destroyMatrix(matrix);
	return PL_unify(aux, result);
}

//total_matrix([[1, 2], [3, 4]], 2, 2, R).
//pl_total_matrix
//sumar todos los números de la matriz
foreign_t pl_total_matrix (term_t list_ofLists, term_t rows_, term_t columns_, term_t result){
	int i;
	int rows = 0;
	int columns = 0;

	if(!checkInteger(&rows, rows_)){
		fprintf(stderr, "La variable rows no es válida\n");		
		PL_fail;
	}

	if(!checkInteger(&columns, columns_)){
		fprintf(stderr, "La variable columns no es válida\n");		
		PL_fail;
	}

	Matrix_C* matrix = createMatrix(rows, columns);
 	if (list_toMatrix(list_ofLists, matrix) == 0){
		fprintf(stderr, "Error pasando la lista a matriz\n");
		PL_fail;
	}

	double sum = 0;

	for (i=0; i<matrix->rows*matrix->columns; i++){
		sum += matrix->matrix[i];
	}

	term_t r = PL_new_term_ref();

	destroyMatrix(matrix);
	if(PL_put_float(r, sum)){
		return PL_unify(r, result);
	} else {
		PL_fail;
	}
}

//sum_matrixes([[1,2], [2,1], [1,1]], [[2,1], [2,1], [1,1]], 3, 2, R).
//pl_sum_matrixes
//Sumar dos matrices
foreign_t pl_sum_matrixes (term_t list_ofLists1, term_t list_ofLists2, term_t rows_, term_t columns_, term_t result){
	int columns, rows, i;
	
	if(!checkInteger(&rows, rows_)){
		fprintf(stderr, "La variable rows no es válida\n");		
		PL_fail;
	}

	if(!checkInteger(&columns, columns_)){
		fprintf(stderr, "La variable columns no es válida\n");		
		PL_fail;
	}

	Matrix_C* matrix1 = createMatrix(rows, columns);
 	if (list_toMatrix(list_ofLists1, matrix1) == 0){
		fprintf(stderr, "Error pasando la primera lista a matriz.\nRecuerde que, para sumar dos matrices, ambas tienen que tener las mismas dimensiones.\n");
		PL_fail;
	}

	Matrix_C* matrix2 = createMatrix(rows, columns);
 	if (list_toMatrix(list_ofLists2, matrix2) == 0){
		fprintf(stderr, "Error pasando la segunda lista a matriz.\nRecuerde que, para sumar dos matrices, ambas tienen que tener las mismas dimensiones.\n");
		PL_fail;
	}

	Matrix_C* resultMatrix = createMatrix(rows, columns);

	for (i=0; i<resultMatrix->rows*resultMatrix->columns; i++){
		resultMatrix->matrix[i] = matrix1->matrix[i] + matrix2->matrix[i];
	}

	term_t aux = PL_new_term_ref();
	if (!matrix_toList(resultMatrix, aux)){
		fprintf(stderr, "Error pasando la matriz a lista\n");
		PL_fail;
	}
	destroyMatrix(resultMatrix);
	destroyMatrix(matrix1);
	destroyMatrix(matrix2);

	return PL_unify(aux, result);
}

//pl_multiply_matrixes
//Multiplicar dos matrices
//multiply_matrixes([[1,0,0,2],[0,1,0,0],[0,0,1,-2], [0,0,0,1]],[[2],[-3],[1],[1]], 4, 4, 4, 1, R).
foreign_t pl_multiply_matrixes (term_t list_ofLists1, term_t list_ofLists2, term_t rows1_, 
		term_t columns1_, term_t rows2_, term_t columns2_, term_t result){
	int columns1, rows1, columns2, rows2;

	if(!checkInteger(&columns1, columns1_)){
		fprintf(stderr, "La variable columns1 no es válida\n");		
		PL_fail;
	}

	if(!checkInteger(&rows2, rows2_)){
		fprintf(stderr, "La variable rows2 no es válida\n");		
		PL_fail;
	}

	if(columns1 != rows2){
		fprintf(stderr, "No se pueden multiplicar dos matrices si el "
		"número de columnas de la primera no es igual al número de filas de la segunda\n");
		PL_fail;
	}

	if(!checkInteger(&rows1, rows1_)){
		fprintf(stderr, "La variable rows1 no es válida\n");		
		PL_fail;
	}

	if(!checkInteger(&columns2, columns2_)){
		fprintf(stderr, "La variable columns2 no es válida\n");		
		PL_fail;
	}

	Matrix_C* matrix1 = createMatrix(rows1, columns1);
 	if (list_toMatrix(list_ofLists1, matrix1) == 0){
		fprintf(stderr, "Error pasando la primera lista a matriz.\n");
		PL_fail;
	}

	Matrix_C* matrix2 = createMatrix(rows2, columns2);
 	if (list_toMatrix(list_ofLists2, matrix2) == 0){
		fprintf(stderr, "Error pasando la segunda lista a matriz.\n");
		PL_fail;
	}

	Matrix_C* resultMatrix = createMatrix(rows1, columns2);
	int i, j, k;

	for(i=0; i<rows1; i++){
		for(j=0; j<columns2; j++){
			for (k=0; k<columns1; k++){
				resultMatrix->matrix[i*columns2+j] += matrix1->matrix[i*columns1+k] * matrix2->matrix[k*columns2+j];
			}
		}
	}

	term_t aux = PL_new_term_ref();
	if (!matrix_toList(resultMatrix, aux)){
		fprintf(stderr, "Error pasando la matriz a lista\n");
		PL_fail;
	}
	destroyMatrix(matrix1);
	destroyMatrix(matrix2);
	destroyMatrix(resultMatrix);

	return PL_unify(aux, result);
}

//pl_help_matrix()
//ayuda de la librería
foreign_t pl_help_matrix (){
	fprintf(stderr, "Bienvenid@ a la librería Matrilog.\nLas operaciones disponibles son:\n\n");
	fprintf(stderr, "  - mult_matrix_by(multiplier:integer, list_ofLists:list, rows:integer, columns:integer, Result:variable)\n    Multiplicar por multiplier todos los elementos de una matriz y almacenar la matriz resultado en Result\n\n");
	fprintf(stderr, "  - total_matrix(list_ofLists:list, rows:integer, columns:integer, Result:variable)\n    Sumar todos los elementos de una matriz y almacenar el resultado en Result\n\n");
	fprintf(stderr, "  - sum_matrixes(list_ofLists:list, list_ofLists:list, rows:integer, columns:integer, Result:variable)\n    Sumar dos matrices y almacenar el resultado en Result\n\n");
	fprintf(stderr, "  - multiply_matrixes(list_ofLists:list, list_ofLists:list, rows1:integer, columns1:integer, rows2:integer, columns2:integer, Result:variable)\n    Multiplicar dos matrices y almacenar el resultado en Result\n");
	PL_succeed;
}

install_t install() {
	PL_register_foreign("mult_matrix_by", 5, pl_multiply_matrix_by, 0);
	PL_register_foreign("total_matrix", 4, pl_total_matrix, 0);
	PL_register_foreign("sum_matrixes", 5, pl_sum_matrixes, 0);
	PL_register_foreign("multiply_matrixes", 7, pl_multiply_matrixes, 0);
	PL_register_foreign("help_matrix", 0, pl_help_matrix, 0);
}
