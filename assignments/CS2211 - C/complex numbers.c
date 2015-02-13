#include<stdio.h>

struct complex_t { double real, imaginary; }; //structure declaration

/* function prototypes */
struct complex_t complex_multi(struct complex_t num1, struct complex_t num2);
struct complex_t complex_div(struct complex_t *num1, struct complex_t *num2);

int main(void)
{
struct complex_t complex_number1, complex_number2, complex_number3, complex_number4; //complex structure variables
double real_one, real_two, imaginary_one, imaginary_two;                             //member declarations
printf("Enter number to initialize real number for first structure: \n");
scanf("%lf", &real_one);
printf("Enter number to initialize imaginary number for first structure: \n");
scanf("%lf", &imaginary_one);
printf("Enter number to initialize real number for second structure: \n");
scanf("%lf", &real_two);
printf("Enter number to initialize imaginary number for second structure: \n");
scanf("%lf", &imaginary_two);

/* user input values used to initialize member values for two complex structures */
complex_number1.real = real_one; complex_number1.imaginary = imaginary_one;
complex_number2.real = real_two; complex_number2.imaginary = imaginary_two;

/* complex number 3 is initialized to multiplication of complex number 1 and 2 */
complex_number3 = complex_multi(complex_number1, complex_number2);
//print real and imaginary number
printf("real number is %lf and imaginary number is %lf\n", complex_number3.real, complex_number3.imaginary);

return 0;
}

struct complex_t complex_multi(struct complex_t num1, struct complex_t num2)   
{
struct complex_t product;
product.real = num1.real*num2.real-num1.imaginary*num2.imaginary; //compute real number
product.imaginary = ((int)'j')*(num2.real*num1.imaginary+num1.real*num2.real); //compute imaginary number. j substituted for sqrt(-1)
return product;
}