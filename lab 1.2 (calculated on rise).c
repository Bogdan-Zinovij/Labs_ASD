#include <stdio.h>
#include <stdlib.h>
#include <math.h>
double previousElement;
double x;
int i;
double recursiveRaise(double x, int i, int counter){
  double currentElement, sum;
  counter++;
  printf(" Number of call: %d    Current element: %lf    Sum value: %lf\n", counter, currentElement, sum);
  if(i != 0){
    sum = recursiveRaise(x, i-1, counter);
  }

   if(i == 0){
      currentElement = (x-1)/(x+1);
      sum = currentElement;
      previousElement = currentElement;
    } else {
    currentElement = previousElement * ((2*i-1)*(x-1)*(x-1))/((2*i+1)*(x+1)*(x+1));
    sum += currentElement;
    previousElement = currentElement;}
    printf(" Number of call: %d    Current element: %lf    Sum value: %lf\n", counter, currentElement, sum);
  return sum;
  }

int main()
{
   printf("Input x (0 < x < 1):\n");
   scanf("%lf",&x);
   printf("Input number of elements i:\n");
   scanf("%d",&i);
   printf("\n  Calculated sum: %lf", recursiveRaise(x, i-1, 0));
   printf("\n  With formula:   ""%lf""\n", 0.5*log(x));
}
