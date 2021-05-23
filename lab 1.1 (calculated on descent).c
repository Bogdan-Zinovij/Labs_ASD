#include <stdio.h>
#include <stdlib.h>
#include <math.h>
double x;
int n;
double recursiveDescent(double x, int n, int i, double sum, double previousElement){
  double currentElement;
  if(i == 0){
    currentElement = (x-1)/(x+1);
    sum = currentElement;
    previousElement = currentElement;
    printf(" Number of call: %d    Current element: %lf    Sum value: %lf\n", i+1, currentElement, sum);
    recursiveDescent(x, n, i+1, sum, previousElement);
  } else if(i == n){
      printf("  Calculated sum: %lf", sum);
      printf("\n  With formula:   %lf\n", 0.5*log(x));
      return sum;
    } else {
        currentElement = previousElement * ((2*i-1)*(x-1)*(x-1))/((2*i+1)*(x+1)*(x+1));
        sum += currentElement;
        previousElement = currentElement;
        printf(" Number of call: %d    Current element: %lf    Sum value: %lf\n", i+1, currentElement, sum);
        recursiveDescent(x, n, i+1, sum, previousElement);
      }
}

int main()
{
  printf("Input x (0 < x < 1):\n");
  scanf("%lf",&x);
  printf("Input number of elements n:\n");
  scanf("%d",&n);
  recursiveDescent(x, n, 0, 0, 0);
}
