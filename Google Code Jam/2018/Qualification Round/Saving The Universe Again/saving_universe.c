#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 30

struct stack {
	char process;
	int current_damage;
};

int calc_damage(char *instructions);
void create_stack(struct stack *operations, char *instructions);
void swap(struct stack *operations, int *damage, int *swap_quantity, int top);

int main() {
	struct stack operations[MAX];
	int shield, damage, test_case, input_quantity, swap_quantity;
	char instructions[MAX + 1];

	test_case = 0;

	while (scanf(" %d", &input_quantity) != EOF) {

		while (input_quantity != 0) {
			test_case += 1;
			swap_quantity = 0;

			scanf(" %d %s", &shield, instructions);
			damage = calc_damage(instructions);
			create_stack(operations, instructions);

			while (shield < damage && swap_quantity != -1)
				swap(operations, &damage, &swap_quantity, strlen(instructions) - 1);

			if (swap_quantity == -1)
				printf("Case #%d: IMPOSSIBLE\n", test_case);
			else
				printf("Case #%d: %d\n", test_case, swap_quantity);

			input_quantity -= 1;
		}
	}

	return 0;
}

int calc_damage(char *instructions) {
	int len = strlen(instructions);
	int total_damage = 0, current_damage = 1;

	for (int i = 0; i < len; i++) {
		if (instructions[i] == 'S')
			total_damage += current_damage;
		else
			current_damage *= 2;
	}

	return total_damage;
}

void create_stack(struct stack *operations, char *instructions) {
	int len = strlen(instructions);
	int current_damage = 1;

	for (int i = 0; i < len; i++) {
		operations[i].process = instructions[i];

		if (instructions[i] == 'C')
			current_damage *= 2;

		operations[i].current_damage = current_damage;
	}

	return;
}

void swap(struct stack *operations, int *damage, int *swap_quantity, int top) {
	int swap = 0;

	while (top != 0 && !swap) {
		if (operations[top].process == 'S' && operations[top - 1].process == 'C') {
			// setup operations
			operations[top].current_damage /= 2;
			*damage -= operations[top].current_damage;
			*swap_quantity += 1;
			swap = 1;

			// swap operation
			struct stack temp = operations[top];
			operations[top] = operations[top - 1];
			operations[top - 1] = temp;
		}

		top -= 1;
	}

	if (!swap)
		*swap_quantity = -1;

	return;
}