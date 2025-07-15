#include "stract.h"

int add(struct abonent **startObj, struct abonent **endObj, int *length);
int delet(struct abonent **startObj, struct abonent **endObj, int *length);
int search(struct abonent **startObj, struct abonent **endObj, int length);
int get(struct abonent mass);
int getAll(struct abonent **startObj, struct abonent **endObj, int length);
int freeList(struct abonent **startObj, struct abonent **endObj);