#include<stdio.h>
#include<string.h>
#define MAX_DIGITS 20                /* max number of digits that can be displayed */
                       
/*function prototypes*/
void clear_digits_array(void);
void process_digit(int digit, int position);
void print_digits_array(void);

/*initialization of 7-segment data for each digit*/
int segments[10][7] = {{1,1,1,1,1,1,0},
                       {0,1,1,0,0,0,0},
                       {1,1,0,1,1,0,1},
                       {1,1,1,1,0,0,1},
                       {0,1,1,0,0,1,1},
                       {1,0,1,1,0,1,1},
                       {1,0,1,1,1,1,1},
                       {1,1,1,0,0,0,0},
                       {1,1,1,1,1,1,1},
                       {1,1,1,1,0,1,1}};
 
char digits[3][MAX_DIGITS*4];         //declaration of digits array

int main(void)
{
char string[50], *string_pointer;
printf("Enter a number: \n");         //have user enter string
gets(string);                         //read string from user
string_pointer = &string[0];          //initialize pointer to string
clear_digits_array();                 //initializes digits array with ' ' characters
int pos = 0;
while(*string_pointer != NULL)        //loop through length of string
{
/* if character is a digit and positions aren't filled then process digit */
if(*string_pointer > 47 && *string_pointer < 58 && pos < MAX_DIGITS)
{
process_digit((int)(*string_pointer)-48,pos);
pos++;
}
string_pointer++;
}
print_digits_array();                 //print digits entered in 7-segment display

return 0;
}

void clear_digits_array(void)
{
char *p;
/* assigns every element of digits array to ' ' character */
for (p = &digits[0][0]; p < &digits[3][MAX_DIGITS * 4]; p++)
{
*p = ' ';
}
}
 
void process_digit(int digit, int position)
{
int column = 0;
int *q;
q = &segments[0][0];
while(column < 7)               //loop through data for 7-segment display
{
/* if segment display is 1 then it is "turned on" */
if( *(q+digit*7+column) == 1)
{
char *p;
p = &digits[0][0];
/* assign appropriate segment character to correct position in digits array */
switch(column)
{
case 0: *(p+1+position*4)='_';                  break;
case 1: *(p+(MAX_DIGITS*4)+2+position*4)='|';   break;
case 2: *(p+2*(MAX_DIGITS*4)+2+position*4)='|'; break;
case 3: *(p+2*(MAX_DIGITS*4)+1+position*4)='_'; break;
case 4: *(p+2*(MAX_DIGITS*4)+position*4)='|';   break;
case 5: *(p+(MAX_DIGITS*4)+position*4)='|';     break;
case 6: *(p+(MAX_DIGITS*4)+1+position*4)='_';   break;
}
}
column++;
}
}

void print_digits_array(void)
{
char *p;
int counter = 0;
/* prints every element in digits array */
for (p = &digits[0][0]; p < &digits[3][MAX_DIGITS * 4]; p++)
{
printf("%c", *p);
counter++;
/* if counter equal to MAX_DIGITS*4, print new line to signify competerion of row */
if(counter == MAX_DIGITS*4)
{
counter = 0;
printf("\n");
}
}
}