#include "monty.h"
/**
 * m_push - handles the push instruction
 * @stack: double pointer to the stack to push to
 * @line_number: number of the line in the file
 */

void m_push(stack_t **stack, unsigned int line_number)
{

stack_t *new;
	int num = 0, i;

	if (data.words[1] == NULL)
	{
		dprintf(STDERR_FILENO, "L%u: usage: push integer\n", line_number);
		exit(EXIT_FAILURE);
	}

	for (i = 0; data.words[1][i]; i++)
	{
		if (isalpha(data.words[1][i]) != 0)
		{
			dprintf(STDERR_FILENO,"L%u: usage: push integer\n", line_number);
			free_all(1);
			exit(EXIT_FAILURE);
		}
	}
	num = atoi(data.words[1]);

	if (data.qflag == 0)
		new = add_dnodeint(stack, num);
	else if (data.qflag == 1)
		new = add_dnodeint_end(stack, num);
	if (!new)
	{
		dprintf(STDERR_FILENO,"Error: malloc failed\n" );
		free_all(1);
		exit(EXIT_FAILURE);
	}
}

/**
 * m_pall - Prints the values of a stack_t linked list.
 * @stack: A pointer to the top mode node of a stack_t linked list.
 * @line_number: The current working line number of a Monty bytecodes file.
 */
void m_pall(stack_t **stack, unsigned int line_number)
{
	stack_t *tmp = (*stack)->next;

	while (tmp)
	{
		printf("%d\n", tmp->n);
		tmp = tmp->next;
	}
	(void)line_number;
}

/**
 * m_pint - print value on top of `stack', or exit if stack is empty
 * @stack: double pointer to head of stack
 * @line_number: line number of current operation
 *
 * Return: void
 */
void m_pint(stack_t **stack, unsigned int line_number)
{
	stack_t *head = *stack;

	if (!head)
	{
		dprintf(STDERR_FILENO, "L%u: can't pint, stack empty\n" , line_number);
		exit(EXIT_FAILURE);
	}
	printf("%d\n", head->n);
}
/**
 * m_swap - handles the swap instruction
 * @stack: double pointer to the stack to push to
 * @line_number: number of the line in the file
 */
void m_swap(stack_t **stack, unsigned int line_number)
{
	stack_t *temp = *stack, *node = NULL;
	int num;

	if (dlistint_len(*stack) < 2)
	{
		dprintf(STDERR_FILENO,
        "L%u L<line_number>: can't swap, stack too short", line_number);
		free_all(1);
		exit(EXIT_FAILURE);
	}

	temp = get_dnodeint_at_index(*stack, 0);
	num = temp->n;
	delete_dnodeint_at_index(stack, 0);
	node = insert_dnodeint_at_index(stack, 1, num);
	if (!node)
	{
		dprintf(STDERR_FILENO, "Error: malloc failed\n");
		free_all(1);
		exit(EXIT_FAILURE);
	}
}
/**
 * m_add - handles the add instruction
 * @stack: double pointer to the stack to push to
 * @line_number: number of the line in the file
 */
void m_add(stack_t **stack, unsigned int line_number)
{
	int sum = 0;
	stack_t *node = NULL;
	stack_t *node_0 = get_dnodeint_at_index(*stack, 0);
	stack_t *node_1 = get_dnodeint_at_index(*stack, 1);

	if (dlistint_len(*stack) < 2)
	{
		dprintf(STDERR_FILENO,
         "L%u L<line_number>: can't add, stack too short", line_number);
		free_all(1);
		exit(EXIT_FAILURE);
	}

	sum = node_0->n + node_1->n;
	delete_dnodeint_at_index(stack, 0);
	delete_dnodeint_at_index(stack, 0);
	node = add_dnodeint(stack, sum);
	if (!node)
	{
		dprintf(STDERR_FILENO, "Error:malloc failed");
		free_all(1);
		exit(EXIT_FAILURE);
	}
}
/**
 * m_nop - handles the nop instruction
 * @stack: double pointer to the stack to push to
 * @line_number: number of the line in the file
 */
void m_nop(stack_t **stack, unsigned int line_number)
{
	(void)stack;
	(void)line_number;
}