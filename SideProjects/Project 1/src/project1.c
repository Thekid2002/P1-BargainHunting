#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void scan_data(int* operator, double * right_operand) {
    scanf( " %c %lf", operator, right_operand );
}

double do_next_op(char operator, double right_operand, double accumulator){
    switch ( operator ) {
        case '+':
            accumulator += right_operand;
            break;
        case '-':
            accumulator -= right_operand;
            break;
        case '*':
            accumulator *= right_operand;
            break;
        case '/':
            if(right_operand != 0) accumulator /= right_operand;
            break;
        case '^':
            accumulator = pow(accumulator, right_operand);
            break;
        case '#':
            if(accumulator > 0) accumulator = sqrt(accumulator);
            break;
        case '%':
            accumulator *= -1;
            break;
        case '!':
            accumulator = 1 / accumulator;
            break;
        case 'q':
            printf("Result so far is %lf", accumulator);
            exit(42);
    }
    return accumulator;
}

void run_calculator(double * accumulator, char* operator, double* right_operand){
    printf( "Enter operator and optional operand>" );
    scan_data(operator, right_operand);
    *accumulator = do_next_op(*operator, *right_operand, *accumulator);
    printf("Result so far is %lf \n", *accumulator);
}

int main(void) {
    double accumulator = 0;
    char operator;
    double right_operand;

    while (1) {
       run_calculator(&accumulator, &operator, &right_operand);
    }
}
