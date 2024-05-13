#include "functions.h"
#include "Table.h"
#include "cases.h"

int main(int argc, char* argv[]) 
{
    ifstream fin;
    string path = argv[1];
    is_correct_data(path); // проверяем содержимое файла
    fin.open(path);

    string line, start, end; // line будет выступать в качестве буфера/пустышки
    int number_of_tables, hourly_cost;
    map<int, Table> tables; // тут будет вся информация о столах
    vector<string> clients; // тут храним тех, кто находится в клубе
    vector<string> queue; // тут храним очередь
    // входящие <время> <ID> <имя клиента> <номер стола>
    string time_input;
    string id_input;
    string name_input;
    int table_input_number;

    // обрабатываем первые 4 параметра
    fin >> line;
    number_of_tables = stoi(line);
    fin >> start; // время открытия
    fin >> end; // время закрытия
    fin >> line;
    hourly_cost = stoi(line);

    cout << start << endl;

    while(!fin.eof())
    { // определяет конец файла
        fin >> time_input;
        fin >> id_input;
        fin >> name_input;

        // просто дублируем входящую строку
        if(id_input == "2")
         {
            fin >> line;
            table_input_number = stoi(line);
            cout << time_input << " " << id_input << " " << name_input << " " << table_input_number << endl;
        }
        else
            cout << time_input << " " << id_input << " " << name_input << endl;

        // если пришел в нерабочие часы
        if(if_left_smaller(time_input, start))
        {
            cout << time_input << " " << 13 << " " << "NotOpenYet\n";
            continue;
        }

        // обрабатываем варианты входящих ID
        switch (stoi(id_input)) 
        {
            case 1:
            {
                case_1(clients, name_input, time_input);
                break;
            }
            case 2:
            {
                case_2(clients, queue, tables, name_input, time_input, number_of_tables, table_input_number, hourly_cost);
                break;
            }
            case 3:
            {
                case_3(clients, queue, tables, name_input, time_input, number_of_tables);
                break;
            }
            case 4:
            {
                case_4(clients, queue, tables, name_input, time_input, number_of_tables, hourly_cost);
                break;
            }
        }
    }

    // проверяем остался ли кто-то за компьютером к закрытию
    // если да, то освобождаем стол и рассчитываем их
    for(int i = 1; i < number_of_tables + 1; i++)
    {
        if(tables[i].GetStatus() != "not busy")
        {
            tables[i].SetStatus("not busy");
            tables[i].UpdateActiveTime(end, tables[i].GetStartTime(), hourly_cost);
        }
    }

    // выводим тех, кто остался до самого закрытия
    sort(clients.begin(), clients.end());
    for(int i = 0; i < clients.size(); i++)
        cout << end << " " << 11 << " " << clients[i] << endl;

    cout << end << endl;

    // выводим необходимую информацию о столах
    for(int i = 1; i < number_of_tables + 1; i++)
        cout << i << " " << tables[i].GetTotal() << " " << tables[i].GetActiveTime() << endl;
    fin.close();
    return 0;
}
