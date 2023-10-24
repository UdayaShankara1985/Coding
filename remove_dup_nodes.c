
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define true (1)
#define false (0)

#define H_NEXT(h)   (h)->hash_next
#define NEXT(h)     (h)->next

#define HASH_LEN  (10)

struct node 
{
   struct node *next;
   struct node *hash_next;
   int          data;
};

struct node *hash_table[HASH_LEN];


struct node* get_next (struct node *n)
{
  return (n) ? n->next : n;
}

struct node *get_hash_next (struct node *n)
{
  return (n) ? n->hash_next : n;
}



int get_key (struct node *n)
{
   return (n->data % HASH_LEN);
}

int insert_no_duplicate (struct node ** head, struct node *n)
{
   struct node *h = *head, *prev = NULL;
   n->next = NULL;

   if (!h) {
      *head = n;
      return true;
   }
   
   while (h) { 
       if (h->data == n->data) 
           return false;

       prev = h;
       h = get_next (h);
   }

   prev->next = n;
   return true;
}

struct node * remove_duplicate_v2 (struct node *l1, struct node *l2)
{
   struct node *res = NULL, *temp;
   void free_node (struct node *n);

   while (l1 || l2){
      if (l1) {
          temp = l1;
          l1 = get_next (l1);
          if (insert_no_duplicate (&res, temp) != true){
              free_node (temp);
          }
      } 
      if (l2){
          temp = l2;
          l2 = get_next (l2);
          if (insert_no_duplicate (&res, temp) != true){
              free_node (temp);
          } 
      }
     
   }

   return res;
}


int is_node_duplicate (struct node *head, struct node *n)
{
   int key = get_key(n); 
   struct node *h;

    if (hash_table[key] == NULL) {
        hash_table[key] = n;
        return false;
    }

    h = hash_table[key];

    while (h) {
       if (h->data == n->data)
           return true;

       h = get_hash_next (h);
    }

    n->hash_next = hash_table[key];
    hash_table[key] = n;

    return false;
}

struct node* get_tail (struct node *head)
{
   if (head->next == NULL) return head;

   while (head->next) head = get_next (head);
   return head;
}

void free_node (struct node *n)
{
   n->next = n->hash_next = NULL;
   free (n);
   n = NULL;
}

struct node * create_node (int data)
{
    struct node *n = (struct node*)malloc (sizeof(*n));
   
    n->next = n->hash_next = NULL;
    n->data = data;
    return n;
}

void insert_into_list (struct node **head, struct node *n)
{
   struct node *h = *head;
   n->next = NULL;

   if (!*head) *head = n;
   else {
      (get_tail (h))->next = n;
   }
}

struct node * remove_duplicate (struct node *l1, struct node *l2)
{
    struct node *result = NULL, *next;
  
     get_tail (l1)->next = l2;

     while (l1) {
        next = get_next (l1);
        if (is_node_duplicate (NULL, l1) == true){
           free_node (l1);
        } else {
          insert_into_list (&result, l1);
        } 
        l1 = next;
     }

    return result;
}

static void insert_tail (struct node **head, struct node **tail, int data)
{
    if (!*head) {
         *head = *tail = create_node (data);
    } else{
       (*tail)->next = create_node (data);
       (*tail) = (*tail)->next;
    }
}

struct node* populate_list (int *array, int len)
{
    struct node *head = NULL, *tail = NULL;
    int idx;

    for ( idx = 0; idx < len ; idx ++){
        insert_tail (&head, &tail, array[idx]);
    }

    return head;
}

void show_list ( struct node *l, char *msg)
{
   if (msg) printf ("%s \n", msg);
   while (l){
     printf ("%d ", l->data);
     l = get_next (l);
   }
   putchar('\n');
}
#define SIZEOF(a)   sizeof(a)/sizeof(a[0])




int main()
{
    int a1[] = { 1, 2, 2, 4};
    int a2[] = { 1, 3, 4, 5};

    struct node *l1, *l2, *r;

    l1 = populate_list (a1, SIZEOF(a1));
    l2 = populate_list (a2, SIZEOF(a1));

    show_list (l1, "first list");
    show_list (l2, "second list");

    r = remove_duplicate_v2 (l1, l2);
    show_list (r, "result list");
}
