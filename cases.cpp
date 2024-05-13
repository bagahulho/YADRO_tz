#include "Table.h"
#include "functions.h"
#include "cases.h"

void case_1(vector<string> &clients, const string &name_input, const string & time_input)
{
    if (find(clients.begin(), clients.end(), name_input) != clients.end())
        cout << time_input << " " << 13 << " " << "YouShallNotPass\n";
    else
        clients.push_back(name_input);
}

void case_2(vector<string> &clients, vector<string> &queue, map<int, Table> &tables, const string &name_input, const string & time_input, const int &number_of_tables, const int &table_input_number, const int &hourly_cost)
{
    if (find(clients.begin(), clients.end(), name_input) == clients.end())
        cout << time_input << " " << 13 << " " << "ClientUnknown\n";
    else if(tables[table_input_number].GetStatus() != "not busy")
        cout << time_input << " " << 13 << " " << "PlaceIsBusy\n";
    else
    {
        // проверяем сидит ли клиент уже за столом, если да, то освобождаем его
        for(int i = 1; i < number_of_tables + 1; i++)
        {
            if(tables[table_input_number].GetStatus() == name_input)
            {
                tables[i].SetStatus("not busy");
                tables[i].UpdateActiveTime(time_input, tables[i].GetStartTime(), hourly_cost);
                break;
            }
        }
        // проверяем стоял ли клиент в очереди и удаляем
        if(find(queue.begin(), queue.end(), name_input) != queue.end())
            queue.erase(find(queue.begin(), queue.end(), name_input));
        // закрепляем стол за клиентом
        tables[table_input_number].SetStatus(name_input);
        tables[table_input_number].SetStartTime(time_input);
    }
}

void case_3(vector<string> &clients, vector<string> &queue, map<int, Table> &tables, const string &name_input, const string & time_input, const int &number_of_tables)
{
    if(queue.size() >= number_of_tables)
        cout << time_input << " " << 11 << " " << name_input << endl;
    else if (find(clients.begin(), clients.end(), name_input) != clients.end()) // проверяем находится ли человек в клубе
    {
        queue.push_back(name_input);
        // проверка на пустые столы
        for(int i = 1; i < number_of_tables + 1; i++)
        {
            if(tables[i].GetStatus() == "not busy")
            {
                cout << time_input << " " << 13 << " " << "ICanWaitNoLonger!\n";
                queue.pop_back();
                break;
            }
        }
    }
    else if (find(clients.begin(), clients.end(), name_input) == clients.end())
        cout << time_input << " " << 13 << " " << "ClientUnknown\n";
}

void case_4(vector<string> &clients, vector<string> &queue, map<int, Table> &tables, const string &name_input, const string & time_input, const int &number_of_tables, const int &hourly_cost)
{
    if (find(clients.begin(), clients.end(), name_input) == clients.end())
        cout << time_input << " " << 13 << " " << "ClientUnknown\n";
    else
    {
        // если в очереди никого нет, то просто освобождаем стол
        if(queue.empty())
        {
            for (int i = 1; i < number_of_tables + 1; i++)
            {
                if (tables[i].GetStatus() == name_input)
                {
                    tables[i].SetStatus("not busy");
                    tables[i].UpdateActiveTime(time_input, tables[i].GetStartTime(), hourly_cost);
                    break;
                }
            }
        }
        // в ином случае сразу садим за освобожденный стол первого человека из очереди
        else
        {
            for (int i = 1; i < number_of_tables + 1; i++)
            {
                if (tables[i].GetStatus() == name_input)
                {
                    tables[i].UpdateActiveTime(time_input, tables[i].GetStartTime(), hourly_cost); // фиксируем время прошлого клиента
                    tables[i].SetStatus(queue[0]); // и закрепляем стол за новым пользователем
                    tables[i].SetStartTime(time_input);
                    cout << time_input << " " << 12 << " " << queue[0] << " " << i << endl;
                    queue.erase(queue.begin()); // удаляем из очереди
                    break;
                }
            }
        }
        clients.erase(find(clients.begin(), clients.end(), name_input)); // удаляем уходящего из списка клиентов
    }
}