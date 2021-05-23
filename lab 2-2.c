#include <stdio.h>
#include <stdlib.h>
typedef struct list{
 int val;
 struct list *next;
 struct list *prev;
} list;
list *list_init(int initVal){
 list *l_p;
 l_p = malloc(sizeof(struct list));
 l_p->val = initVal;
 l_p->next = NULL;
 l_p->prev = NULL;
 return l_p;
}
list* getLast(list *l_p) {
 if (l_p == NULL) {
   return NULL; }
   while (l_p->next) {
   l_p = l_p->next;
 }
 return l_p;
}
void pushNode(list *l_p, int value){
 list *last = getLast(l_p);
 list *tmp = malloc(sizeof(list));
 tmp->val = value;
 tmp->next = NULL;
 tmp->prev = last;
 last->next = tmp;
}
void printList(list *l_p){
 int counter = 1;
 struct list *p;
 p = l_p;
 printf("\n The double linked list: \n");
 do {
   printf(" el%d = %d\n", counter, p->val);
   p = p->next;
   counter++;
 } while (p != NULL);
   printf("\n");
}
void getResult(list *l_p, int n){
 int firstEl = 1;
 int secondEl = 2*n; int result = 0;
 struct list *l, *r;
 l = l_p;
 r = getLast(l_p);
 do {
   result += ((l->val) * (r->val));
   printf(" el%d * el%d = %d * %d\n",firstEl,secondEl,l->val,r->val);
   l = l->next;
   r = r->prev;
   firstEl +=1;
   secondEl -=1;
 } while(r != l->prev);
   printf("\n Calculated result: %d\n", result);
}
list *deleteFirstNode(list *l_p)
{
 struct list *tmp;
 tmp = l_p ->next;
 tmp->prev = NULL;
 free(l_p);
 return tmp;
}
int main(){
 struct list* dlList = list_init(NULL);
 int n;
 printf(" Input n: ");
 scanf("%d", &n); srand(time(NULL));
 for (int i = 1; i <= 2*n; i++){
   pushNode(dlList, rand()%10);
 }
 dlList = deleteFirstNode(dlList);
 printList(dlList);
 getResult(dlList, n);
 return 0;
}
