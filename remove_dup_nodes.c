
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define true (1)
#define false (0)

struct node 
{
   struct node   *next;         // next node in the list
   struct node   *hash_next;    // next node in the hash table (obselute)
   int           data;          // data 
};

#define NEXT(h)     (h)->next

//absolute
#define HASH_LEN  (10)
#define H_NEXT(h)   (h)->hash_next

#define do_insert(res, n)                            \
 do {                                                \
     struct node *temp = n;                          \
     n = get_next (n);                               \
     if (insert_no_duplicate  (&res, temp) != true){ \
         free_node (temp);                           \
     }                                               \
 }while (0) 

#define SIZEOF(a)   sizeof(a)/sizeof(a[0])


// function to get the next date value
struct node* get_next (struct node *n)
{
  return (n) ? n->next : n;
}

struct node *get_hash_next (struct node *n)
{
  return (n) ? n->hash_next : n;
}

// function to insert the nodes into list if duplicate found then return false;
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


// function to remove the duplicate notes from the lists and return the result list 
struct node * remove_duplicate_v2 (struct node *l1, struct node *l2)
{
   struct node *res = NULL, *l;
   void free_node (struct node *n);

   while (l1 || l2){
        if (l1)
            do_insert (res, l1);
        else 
            do_insert (res, l2);
   }

   return res;
}


// function to get the tail of the list
struct node* get_tail (struct node *head)
{
   if (head->next == NULL) return head;

   while (head->next) head = get_next (head);
   return head;
}

// function to free the list
void free_node (struct node *n)
{
   n->next = n->hash_next = NULL;
   free (n);
   n = NULL;
}

// function to creat the node 
struct node * create_node (int data)
{
    struct node *n = (struct node*)malloc (sizeof(*n));
   
    n->next = n->hash_next = NULL;
    n->data = data;
    return n;
}

#if 0

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


struct node *hash_table[HASH_LEN];

int get_key (struct node *n)
{
   return (n->data % HASH_LEN);
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
#endif

// function to insert the node at the tail
static void insert_tail (struct node **head, struct node **tail, int data)
{
    if (!*head) {
         *head = *tail = create_node (data);
    } else{
       (*tail)->next = create_node (data);
       (*tail) = (*tail)->next;
    }
}

// function to populate the list from array 
struct node* populate_list (int *array, int len)
{
    struct node *head = NULL, *tail = NULL;
    int idx;

    for ( idx = 0; idx < len ; idx ++){
        insert_tail (&head, &tail, array[idx]);
    }

    return head;
}

// function to show the list values 
void show_list ( struct node *l, char *msg)
{
   if (msg) printf ("%s \n", msg);
   while (l){
     printf ("%d ", l->data);
     l = get_next (l);
   }
   putchar('\n');
}


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
