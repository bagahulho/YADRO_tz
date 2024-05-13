#ifndef YADRO_TZ_FUNCTIONS_H
#define YADRO_TZ_FUNCTIONS_H
#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <vector>
using namespace std;

int get_hours(const string &time);
int get_minutes(const string &time);
bool if_left_smaller(const string &left, const string &right);
void is_correct_time(const string &time);
void is_correct_id(const string &id);
void is_correct_name(const string &name);
void is_correct_num(const string &num);
void is_correct_data(const string &path);

#endif //YADRO_TZ_FUNCTIONS_H
