#include <stdio.h>
#include <SWI-Prolog.h>

foreign_t pl_sum_list(term_t list, term_t result){
	if (!PL_is_list(list))
		PL_fail;
	
	term_t head = PL_new_term_ref();
	term_t tail = PL_copy_term_ref(list);

	double sum = 0;

	while(PL_get_list(tail, head, tail)){
		double d = 0;
		int i = 0;

		if (!PL_is_number(head))
			continue;

		if (PL_is_integer(head)){
			PL_get_integer(head, &i);
			d = (double) i;
		} else {
			PL_get_float(head, &d);
		}

		sum += d;
	}

term_t r = PL_new_term_ref();
PL_put_float(r, sum);

return PL_unify(r, result);

}

install_t install() {
	PL_register_foreign("sum_list", 2, pl_sum_list, 0);
}
