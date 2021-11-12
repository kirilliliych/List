#include "List.h"
#define DUMP  ListDump(&list, __LINE__);
#define DUMPF ListDump(list, __LINE__);
int main()
{
    List list = {};

    int list_capacity = 0;
    printf("Enter desired list capacity. Value should be positive!\n");
    scanf("%d", &list_capacity);
    while (ListCtor(&list, list_capacity))
    {
        printf("Wrong list capacity input, please try again!\n");
        getchar();
        scanf("%d", &list_capacity);
    }

    ListInsertForward(&list, 12);
    ListInsertForward(&list, 24);   
    ListInsertForward(&list, 36);
    ListDump(&list, __LINE__);
    ListInsertAfter(&list, 2, 228);
    ListDump(&list, __LINE__);
    ListInsertAfter(&list, 1, 45);
    ListDump(&list, __LINE__);
    ListVerify(&list);
    ListInsertBack(&list, 22);
    ListDump(&list, __LINE__);
    SortListByPrevSlowSlowSlowSlow(&list);
    ListDump(&list, __LINE__);
    ListDtor(&list);
    return OK;
}

int ListCtor(List *list, int capacity)
{
    assert(list != nullptr);

    if (capacity <= 0)
    {
        return INCORRECT_CAPACITY_VALUE;
    }

    list->capacity = (size_t) capacity;

    list->data = (list_element *) calloc(capacity + 1, sizeof(list_element));
    assert(list->data != nullptr);

    for (int elem_index = 0; elem_index <= capacity; ++elem_index)
    {
        list->data[elem_index].num  = poison_value;
        list->data[elem_index].next = elem_index + 1;
        list->data[elem_index].prev = -1;
    }

    list->data[0].prev = 0;
    list->data[0].next = 0;
    list->data[capacity].next = 0;

    list->head = 0;
    list->tail = 0;
    list->free = 1;

    return OK;
}

void ListDtor(List *list)
{
    assert(list != nullptr);
    assert(list->data != nullptr); 

    list->head = 0;
    list->tail = 0;
    list->capacity = 0;
    list->free = 0;
    list->sorted = 0;

    free(list->data);
    list->data = nullptr;
}

int ListInsertForward(List *list, elem_t value)
{
    assert(list != nullptr);
    assert(list->data != nullptr);
  
    if (list->free == 0)
    {
        ListResize(list);   
    }
    
    int free_place = list->free;
    list->free = list->data[list->free].next;
    list->data[free_place].next = list->head;
    list->data[free_place].prev = 0;
    list->data[free_place].num = value;

    if (list->head != 0)
    {
        list->data[list->head].prev = free_place;
    }
    list->head = free_place;

    if (list->tail == 0)
    {
        list->tail = free_place;
    }
    
    return free_place;    
}

int ListInsertBack(List *list, elem_t value)
{
    assert(list != nullptr);
    assert(list->data != nullptr);  

    if (list->free == 0)
    {
        ListResize(list);
    }

    int free_place = list->free;
    list->free = list->data[list->free].next;

    list->data[free_place].next = 0;
    list->data[free_place].prev = list->tail;
    list->data[free_place].num = value;  

    list->data[list->tail].next = free_place;
    list->tail = free_place;

    if (list->head == 0)
    {
        list->head = free_place;
    }
    
    return free_place;
}

int ListInsertAfter(List *list, int place, elem_t value)
{
    assert(list != nullptr);
    assert(list->data != nullptr);

    if (place <= 0)
    {
        printf("The element cannot have unpositive place number\n");
        return INVALID_PLACEMENT_ATTEMPT;
    }
    else if (place > list->capacity)
    {
        printf("Element's number cannot be bigger than capacity\n");
        return INVALID_PLACEMENT_ATTEMPT;
    } 
    
    if (place == list->tail)
    {
        return ListInsertBack(list, value);
    }  

    if (list->data[place].prev == -1)
    {
        printf("Attempt to place new value after uninitialized list element\n");
        return INVALID_PLACEMENT_ATTEMPT;
    }
    
    
    if (list->free == 0)
    {
        ListResize(list);   
    }

    int free_place = list->free;
    list->free = list->data[list->free].next;

    list->data[free_place].num = value;                                                                                                       
    list->data[free_place].next = list->data[place].next;
    list->data[list->data[free_place].next].prev = free_place;
    list->data[place].next = free_place;
    list->data[free_place].prev = place;
    
    return free_place;
}

int ListRemove(List *list, int place)
{
    assert(list != nullptr);
    assert(list->data != nullptr);

    if (place <= 0)
    {
        printf("The element cannot have unpositive place number\n");
        return INVALID_REMOVAL_ATTEMPT;
    }
    else if (place > list->capacity)
    {
        printf("Element's number cannot be bigger than capacity\n");
        return INVALID_REMOVAL_ATTEMPT;
    }
    else if (list->data[place].prev == -1)
    {
        printf("Unitialized element cannot be removed");
        return INVALID_REMOVAL_ATTEMPT;
    }

    list->data[list->data[place].prev].next = list->data[place].next;
    list->data[list->data[place].next].prev = list->data[place].prev;

    list->data[place].num = poison_value;
    list->data[place].prev = -1;
    
    list->data[place].next = list->free;
    list->free = place;

    return OK;
}

void ListDump(List *list, size_t line)
{
    assert(list != nullptr);
    assert(list->data != nullptr);

    printf("LINE: %u\n\n", line);
    printf("capacity: %u\n"
           "head: %u\n"
           "tail: %u\n"
           "free: %d\n"
           "data:   \n",
           list->capacity,
           list->head,
           list->tail,
           list->free);

    for (int i = 0; i < 4; ++i)
    {
        if (i == 0)
        {
            printf("element_index:  ");
        }

        if (i == 1)
        {
            printf("element_number: ");
        }

        if (i == 2)
        {
            printf("element_next:   ");
        }

        if (i == 3)
        {
            printf("element_prev:   ");
        }

        for (size_t elem_index = 0; elem_index <= list->capacity; ++elem_index)
        {
            if (i == 0)
            {
                printf("%10u", elem_index);
            }

            if (i == 1)
            {
                printf("%10lg", list->data[elem_index].num);
            }

            if (i == 2)
            {
                printf("%10d", list->data[elem_index].next);
            }

            if (i == 3)
            {
                printf("%10d", list->data[elem_index].prev);
            }
        }

        printf("\n");
    }
    
    printf("\n\n");
}

int ListVerify(List *list)
{
    assert(list != nullptr);
    assert(list->data != nullptr);

    if (list->capacity <= 0)
    {
        printf("Unpositive capacity\n");
        return BAD_CAPACITY;
    }

    int ver_res = VerifyElements(list);
    if (ver_res)
    {
        return ver_res;
    }

    printf("List is ok\n");
    return OK;
}

int VerifyElements(List *list)
{
    assert(list != nullptr);
    assert(list->data != nullptr);

    if ((list->data[0].num != poison_value) || (list->data[0].next != 0) || (list->data[0].prev != 0))
    {
        printf("Zero element is corrupted\n");
        return WRONG_ZERO_ELEMENT;
    }

    for (size_t elem_index = 1; elem_index <= list->capacity; ++elem_index)
    {
        if (list->data[elem_index].num == poison_value)
        {
            if ((list->data[elem_index].prev != -1) || (list->data[elem_index].next > list->capacity) || (list->data[elem_index].next < 0))
            {
                printf("Free element's prev or next index is invalid, element number %d\n", elem_index);
                return WRONG_FREE_ELEMENT_CONDITION;
            }
        }
        else
        {
            if ((list->data[elem_index].next < 0) || (list->data[elem_index].prev < 0) || (list->data[elem_index].next > list->capacity) || (list->data[elem_index].prev > list->capacity))
            { 
                printf("List element's prev or next index is invalid %d\n", elem_index);
                return WRONG_LIST_ELEMENT_CONDITION;
            }        

            if ((elem_index != list->data[list->data[elem_index].next].prev) && (list->data[elem_index].next != 0))
            {
                printf("Wrong connection between element %d and his next %d\n", elem_index, list->data[elem_index].next);
                return WRONG_CONNECTION;
            }
            
            if ((elem_index != list->data[list->data[elem_index].prev].next) && (list->data[elem_index].prev != 0))
            {
                printf("Wrong connection between element %d and his prev %d\n", elem_index, list->data[elem_index].prev);
                return WRONG_CONNECTION;
            }
        }
    }

    return OK;
}

void ListResize(List *list)
{
    assert(list != nullptr);
    assert(list->data != nullptr);

    printf("Warning! List resizing, it slows list working process\n");

    void *new_data = realloc(list->data, (EXPAND_COEF * list->capacity + 1) * sizeof(list_element));
    assert(new_data != nullptr);

    list->data = (list_element *) new_data;

    list->free = list->capacity + 1;
    list->capacity = list->capacity * EXPAND_COEF;
    
    for (int cur_free_elem_index = list->free; cur_free_elem_index <= list->capacity; ++cur_free_elem_index)
    {
        list->data[cur_free_elem_index].num  = poison_value;
        list->data[cur_free_elem_index].prev = -1;
        list->data[cur_free_elem_index].next = cur_free_elem_index + 1;
    }

    list->data[list->capacity].next = 0;
}

void SortListByPrevSlowSlowSlowSlow(List *list)
{
    assert(list != nullptr);
    assert(list->data != nullptr);

    list_element *new_data = (list_element *) calloc(list->capacity + 1, sizeof(list_element));
    assert(new_data != nullptr);

    new_data[0].num  = poison_value;
    new_data[0].next = 0;
    new_data[0].prev = 0;
    
    int valid_elems_num = 0;

    for (int elem_index = 1; elem_index <= list->capacity; ++elem_index)
    {
        if (list->data[elem_index].prev == -1)
        {
            continue;
        }

        new_data[list->data[elem_index].prev + 1].prev = list->data[elem_index].prev;
        new_data[list->data[elem_index].prev + 1].next = list->data[elem_index].next;
        new_data[list->data[elem_index].prev + 1].num  = list->data[elem_index].num;

        ++valid_elems_num;
    }

    ++valid_elems_num;

    for (; valid_elems_num <= list->capacity; ++valid_elems_num)
    {
        new_data[valid_elems_num].num  = poison_value;
        new_data[valid_elems_num].prev = -1;
        new_data[valid_elems_num].next = valid_elems_num + 1;
    }

    list->data = new_data;
    list->sorted = 1;
}

void TranslateLogicalElementToPhysicalElementSlowSlowSlowSlowDoNotCallMe(List *list)
{
    
}
