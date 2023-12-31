#include <stddef.h>
#include <stdio.h>

#define AIV_LIST(x) &(x.list_item)
#define AIV_INT(x) ((struct aiv_int_item*)(x))


struct aiv_list_node
{
    struct aiv_list_node* prev;
    struct aiv_list_node* next;
    unsigned int count;
};

struct aiv_int_item
{
    struct aiv_list_node list_item;
    int value;
};


struct aiv_list_node* aiv_list_get_tail(struct aiv_list_node** head)
{
    if (!head)
    {
        return NULL;
    }

    struct aiv_list_node* current_item = *head;
    struct aiv_list_node* last_item = *head;
    while(current_item)
    { 
        last_item = current_item;
        current_item = current_item->next;
    }

    return last_item;  
};

struct aiv_list_node* aiv_list_append(struct aiv_list_node** head, struct aiv_list_node* item)
{
    struct aiv_list_node* tail = aiv_list_get_tail(head);
    if (!tail)
    {
        *head = item;
        (*head)->count = 1;
    }
    else
    {
        tail->next = item;
        (*head)->count++;
    }

    item->prev = tail;
    item->next = NULL;
    
    return item;
}

unsigned int aiv_list_lenght(struct aiv_list_node* head)
{
    return head->count;
}

void aiv_list_remove(struct aiv_list_node** head, const unsigned int index)
{
     if (*head == NULL)
    {
        return;
    }

    struct aiv_list_node* current_head = *head;
    const unsigned int current_count = current_head->count;

    if (index == 0)
    {
        *head = (*head)->next;
        (*head)->count = current_count - 1;
        return;
    }

    for (int i = 0; i < index; i++)
    {
        current_head = current_head->next;
    }

    if (current_head == NULL)
    {
        printf("INVALID INDEX\n");
    }

    current_head = current_head->prev;

    struct aiv_list_node* next_item = current_head->next->next;

    current_head->next = next_item;
    
    (*head)->count = current_count - 1;

}

void Print(struct aiv_list_node* head)
{
    struct aiv_list_node* current_item = head;

    if (!head)
    {
        printf("List empty\n");
        return;
    }

    printf("List lenght: %u ", aiv_list_lenght(head));

    printf("List Items: ");

    while (current_item)
    {
        struct aiv_int_item* int_item = AIV_INT(current_item);
        printf("%d ", int_item->value);
        current_item = current_item->next;
    }
    
    printf("\n");  

}

void aiv_insert_after_index(struct aiv_list_node** head, struct aiv_list_node* item, const unsigned int index)
{
    if (*head == NULL)
    {
        return;
    }

    struct aiv_list_node* current_head = *head;

    for (int i = 0; i < index; i++)
    {
        current_head = current_head->next;
    }

    struct aiv_list_node* next_item = current_head->next;

    current_head->next = item;
    item->next = next_item;
    item->prev = current_head;
    next_item->prev = item;

    (*head)->count++;    
}

void aiv_insert_before_index(struct aiv_list_node** head, struct aiv_list_node* item, const unsigned int index)
{
    if (*head == NULL)
    {
        return;
    }

    struct aiv_list_node* current_head = *head;
    int current_count = aiv_list_lenght(*head);
    if (index == 0)
    {
        struct aiv_list_node* next_item = (*head)->next;
        *head = item;
        item->next = current_head;
        current_head->prev = item;
        (*head)->count = current_count;    
        (*head)->count++;           
        return;
    }
    
    for (int i = 0; i < index; i++)
    {
        current_head = current_head->next;
    }

    struct aiv_list_node* prev_item = current_head->prev;
    struct aiv_list_node* prev_prev_item = current_head->prev->prev;

    current_head->prev = item;
    item->prev = prev_item;
    item->next = current_head;
    prev_item->next = item;

    (*head)->count++;        
}

int main(int argc, char** argv)
{
    struct aiv_list_node* head = NULL;


    //riempio la lista
    struct aiv_int_item int_item;
    int_item.value = 100;
    aiv_list_append(&head, AIV_LIST(int_item));

    struct aiv_int_item int_item2;
    int_item2.value = 101;
    aiv_list_append(&head, AIV_LIST(int_item2));

    struct aiv_int_item int_item3;
    int_item3.value = 120;
    aiv_list_append(&head, AIV_LIST(int_item3));

    struct aiv_int_item int_item4;
    int_item4.value = 140;
    aiv_list_append(&head, AIV_LIST(int_item4));

    struct aiv_int_item int_item5;
    int_item5.value = 200;
    aiv_list_append(&head, AIV_LIST(int_item5));
    Print(head); //stampa della lista prima di qualsiasi modifica

    struct aiv_int_item int_item6;
    int_item6.value = 10; //valore da aggiungere dopo aver creato la lista
    aiv_insert_after_index(&head, AIV_LIST(int_item6), 1);
    Print(head); //stampa della lista dopo aver aggiunto un nuovo item

    struct aiv_int_item int_item7;
    int_item7.value = 555; //valore da aggiungere dopo aver creato la lista
    aiv_insert_before_index(&head, AIV_LIST(int_item7), 0);
    Print(head); //stampa della lista dopo aver aggiunto un nuovo item

    aiv_list_remove(&head, 5);
    Print(head);//stampa della lista dopo il remove
}