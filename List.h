#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef float elem_t;

const int EXPAND_COEF = 2;

elem_t poison_value = -666.228;
// const size_t NO_ELEM = ; // Big constant

struct list_element
{
    elem_t num = -666;
    int next = 0;
    int prev = 0;
};

struct List 
{
    list_element *data = nullptr;
    int head = 0;
    int tail = 0;
    size_t capacity = 0;
    int free = 0;
    int sorted = 0;
};

enum Errors
{
    OK = 0,
    INCORRECT_CAPACITY_VALUE,
    NO_FREE_PLACE,
    INVALID_PLACEMENT_ATTEMPT,
    INVALID_REMOVAL_ATTEMPT,
    BAD_CAPACITY,
    WRONG_ZERO_ELEMENT,
    WRONG_FREE_ELEMENT_CONDITION,
    WRONG_LIST_ELEMENT_CONDITION,
    WRONG_CONNECTION,
};

int ListCtor(List *list, int capacity);

void ListDtor(List *list);

int SearchForPlace(List *list);

int ListInsertForward(List *list, elem_t value);

int ListInsertBack(List *list, elem_t value);

int ListInsertAfter(List *list, int place, elem_t value);

int ListRemove(List *list, int place);

void ListDump(List *list, size_t line);

int ListVerify(List *list);

int VerifyElements(List *list);

void ListResize(List *list);

void SortListByPrevSlowSlowSlowSlow(List *list);

void TranslateLogicalElementToPhysicalElementSlowSlowSlowSlowDoNotCallMe(List *list);
