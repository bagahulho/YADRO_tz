#include "Table.h"

Table::Table()
{
    this->start_time = "0";
    this->status = "not busy";
    this->active_time = 0;
    this->total = 0;
}

string Table::GetActiveTime()
{
    int hourDiff = this->active_time / 60;
    int minuteDiff = this->active_time % 60;

    string hourDiffStr = (hourDiff < 10) ? "0" + to_string(hourDiff) : to_string(hourDiff);
    string minuteDiffStr = (minuteDiff < 10) ? "0" + to_string(minuteDiff) : to_string(minuteDiff);

    return hourDiffStr + ":" + minuteDiffStr;
}

string Table::GetStartTime()
{
    return start_time;
}

string Table::GetStatus()
{
    return status;
}

int Table::GetTotal()
{
    return total;
}

void Table::SetStartTime(const string &time)
{
    this->start_time = time;
}

void Table::SetStatus(const string &name)
{
    this->status = name;
}

void Table::UpdateActiveTime(const string &end, const string &start, const int &hourly_cost)
{
    int hour1 = get_hours(end);
    int minute1 = get_minutes(end);
    int hour2 = get_hours(start);
    int minute2 = get_minutes(start);
    int totalMinute1 = hour1 * 60 + minute1;
    int totalMinute2 = hour2 * 60 + minute2;
    int difference = totalMinute1 - totalMinute2;
    this->active_time += difference;
    // сразу добавляем в выручку
    int ans = 0;
    while(totalMinute2 < totalMinute1)
    {
        ans += 1;
        totalMinute2 += 60;
    }
    this->total += ans * hourly_cost;
}