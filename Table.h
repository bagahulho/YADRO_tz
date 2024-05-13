#ifndef YADRO_TZ_TABLE_H
#define YADRO_TZ_TABLE_H
#include "functions.h"

class Table{
private:
    string start_time;
    string status; // если стол занят, то в качестве "статуса" будет выступать имя клиента
    int total;
    int active_time;
public:
    Table();
    string GetActiveTime(); // получаем время, в течение которого был занят стол в формате "XX:XX"
    string GetStartTime(); // время, когда клиент сел за стол
    string GetStatus(); // статус/имя клиента
    int GetTotal(); // выручка стола
    void SetStartTime(const string &time);
    void SetStatus(const string &name);
    void UpdateActiveTime(const string &end, const string &start, const int &hourly_cost); // для подсчета времени пользования столом и его выручки
};


#endif //YADRO_TZ_TABLE_H
