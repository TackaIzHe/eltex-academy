struct msgbuf
{
    long mtype; /* тип сообщения, должен быть > 0 */
    char mtext[10]; /* содержание сообщения */
};