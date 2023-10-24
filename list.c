#include <stdio.h>
#include <string.h>
#include <stdlib.h>


struct node 
{
  struct node *next;
  int           data;
};


#define HASH_LEN (100)


static struct node *get_next (struct node *n)
{
  return n->next;
}


struct node *hash[HASH_LEN] = { 0 };

void free_hash_table(void)
{
   int idx;
   struct node *h, *temp;

   for (idx = 0; idx < HASH_LEN; idx ++){
       if (hash[idx] == NULL) 
           continue;

       h = hash[idx];
       while (h){
          temp = h;
          h = get_next (h);
          free (temp);
      }
      hash[idx] = NULL;
   }
}



int get_key (int value)
{
    return value % HASH_LEN;
}


struct node * create_node (int data)
{
  struct node *n = (struct node *)malloc (sizeof(struct node));
  if (!n)  return n;

  memset (n, 0, sizeof(struct node));
  n->data = data;

  return n;
}

int is_node_duplicate (struct node *n)
{
  struct node *hn, *nd;
  int key = get_key (n->data);

  hn = hash[key];

  if (!hn){
      hash[key] = create_node (n->data);
      return 0;
  }

  while (hn){
    if (hn->data == n->data) 
        return 1;
    
    hn = get_next(hn);
  }

  nd = create_node (n->data);
  nd->next = hash[key];
  hash[key] = nd ;

  return 0;
}

int insert_into_list (struct node **head, struct node *n)
{
  struct node *h = *head;
  if (h == NULL) { *head = n ; return 0; }

  while (h->next){
    h = get_next (h);
  }

  h->next = n;
  return 0;
}
struct node * remove_duplicate (struct node *l1, struct node *l2)
{

   struct node *result = NULL, *n , *temp;

   
   n = l1;
   while (n) {
       if (is_node_duplicate (n) == 1){
            n = get_next (n);
       }else{
          insert_into_list (&result, create_node(n->data));
          n = get_next (n);
       }

   }

   n = l2;
   while (n) {
       if (is_node_duplicate (n) == 1){
           n = get_next (n);
       }else{
          insert_into_list (&result, create_node(n->data));
          n = get_next (n);
       }

   }

   return result;

}


// L1 [ 1 3 4 5 4 8 ]
// L2 [ 6 3 2 ]




void show_list (struct node *head, char *msg)
{ 
  if (msg)    printf ("%s \n", msg);
  while (head) {
    printf ("%d ", head->data);
    head = get_next (head);
  }
  putchar ('\n');
}

void free_list  (struct node *head)
{
  struct node *h ;

  while (head){
    h = head;
    head = get_next (head);
    free (h);
  }
}

#define SIZEOF(a)  sizeof(a)/sizeof(a[0])
int
main(){

   struct node *l1 = NULL, *l2 = NULL, *r = NULL;
      int idx;
   int a1[] = { 1 ,3, 4 , 5, 4, 8};
   int a2[] = { 6 , 3 , 2};


   for (idx = 0; idx < SIZEOF(a1)  ; idx++)
         insert_into_list (&l1, create_node(a1[idx]));
   show_list (l1,"first list");

  for (idx = 0; idx < SIZEOF(a2)  ; idx++)
         insert_into_list (&l2, create_node(a2[idx]));
   show_list (l2,"second list"); 


   r = remove_duplicate (l1, l2);

   free_list (l1);
   free_list (l2);

   free_hash_table ();
   
   show_list (r, "result list");

  return 0;
}
