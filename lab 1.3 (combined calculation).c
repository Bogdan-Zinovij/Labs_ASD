#include <stdio.h>
#include <stdlib.h>
#include <math.h>
double x;
int i;
double combineRecursion(double x, int i, int n, double sum, double element){
  if(n == 0){
    element = (x-1)/(x+1);
    printf(" Number of call: %d    Current element: %lf    Sum value: %lf\n", n+1, element, sum);
    if(i != 1){
      sum += element + combineRecursion(x, i, n+1, sum, element);
    } else {
        sum = element;
      }
    printf(" Number of call: %d    Current element: %lf    Sum value: %lf\n", n+1, element, sum);
  } else {
        element = element * ((2*n-1)*(x-1)*(x-1))/((2*n+1)*(x+1)*(x+1));
        printf(" Number of call: %d    Current element: %lf    Sum value: %lf\n", n+1, element, sum);
        if(n+1!=i){
            sum += element + combineRecursion(x, i, n+1, sum, element);
          } else {
              sum += element;
            }
  printf(" Number of call: %d    Current element: %lf    Sum value: %lf\n", n+1, element, sum);
  }
  return sum;
}

int main()
{
  printf("Input x (0 < x < 1):\n");
  scanf("%lf",&x);
  printf("Input number of elements i:\n");
  scanf("%d",&i);
  printf("  Calculated sum: %lf", combineRecursion(x, i, 0, 0, 0));
  printf("\n  With formula:   %lf\n", 0.5*log(x));
}
