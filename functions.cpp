#include "functions.h"

int get_hours(const string &time)
{
    string buff = time;
    buff.erase(2,3);
    int hours = stoi(buff);
    return hours;
}

int get_minutes(const string &time)
{
    string buff = time;
    buff.erase(0,3);
    int minutes = stoi(buff);
    return minutes;
}

bool if_left_smaller(const string &left, const string &right)
{
    int left_hours = get_hours(left);
    int left_min = get_minutes(left);
    int right_hours = get_hours(right);
    int right_min = get_minutes(right);
    if (left_hours < right_hours || ((left_hours == right_hours) && (left_min < right_min)))
        return true;
    else
        return false;
}

void is_correct_time(const string &time)
{
    if(!(isdigit(time[0]) && isdigit(time[1]) && time[2] == ':' && isdigit(time[3]) && isdigit(time[4])))
    {
        cout << time;
        exit(0);
    }
    else{
        if (!((((int)time[0] - 48) == 0 || ((int)time[0] - 48) == 1 || (((int)time[0] - 48) == 2 && ((int)time[1] - 48) <= 4)) && (((int)time[3] - 48) <= 5)))
        {
            cout << time;
            exit(0);
        }
    }
}

void is_correct_id(const string &id)
{
    if( id != "1" && id != "2" && id != "3" && id != "4")
    {
        cout << id << endl;
        exit(0);
    }
}

void is_correct_name(const string &name)
{
    for(int i = 0; i < name.length(); i++)
    {
        if(!(islower(name[i]) || isdigit(name[i]) || name[i] == '_' || name[i] == '-'))
        {
            cout << name << endl;
            exit(0);
        }
    }
}

void is_correct_num(const string &num)
{
    for(int i = 0; i < num.length(); i++)
    {
        if(!(isdigit(num[i])))
        {
            cout << num << endl;
            exit(0);
        }
    }
}

void is_correct_data(const string &path)
{ // проверка на корректность данных в файле
    ifstream fin;
    fin.open(path);
    if(!fin.is_open())
        cout << "File open ERROR";
    else
    {
        string line, id, previous_time = "";
        int number_of_tables;
        fin >> line; is_correct_num(line);
        number_of_tables = stoi(line);
        if(number_of_tables == 0)
        {
            cout << number_of_tables;
            exit(0);
        }
        fin >> line; is_correct_time(line);
        fin >> line; is_correct_time(line);
        fin >> line; is_correct_num(line);
        while(!fin.eof())
        {
            fin >> line; is_correct_time(line);
            // если данное время меньше предыдущего
            if(previous_time != "" && if_left_smaller(line, previous_time)){
                cout << line << endl;
                exit(0);
            }
            previous_time = line;
            fin >> id; is_correct_id(id);
            fin >> line; is_correct_name(line);
            if(id == "2")
            {
                fin >> line; is_correct_num(line);
                // если нет номера стола, за который хочет сесть клиент
                if(stoi(line) > number_of_tables)
                {
                    cout << line << endl;
                    exit(0);
                }
            }
        }
    }
    fin.close();
}
