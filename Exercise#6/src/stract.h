struct abonent
{
    char id;
    char name[10];
    char second_name[10];
    char tel[10];
    struct abonent *prev; // Указатель на предыдущий узел
    struct abonent *next; // Указатель на следующий узел
};