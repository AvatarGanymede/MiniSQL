#pragma once
#ifndef _API_H_
#define _API_H_

#include "interpreter.h"
#include "pch.h"
#include "buffer_manager.h"
#include "record_manager.h"
extern RecordManager record_manager;
extern Interpreter In;

bool create_table(Interpreter* in);

int insert_record(string values[], int num);

bool execfile(Interpreter* in, string file_name);

bool get_col_ids(vector<int>* col_ids, string str, string table_name, Interpreter* in);

bool api_select(string table_name, vector<int> col_ids, vector<Where_clause> w_clause, vector<int> logic);

int api_delete(string table_name, vector<Where_clause> w_clouse, vector<int> logic);

bool is_unique(string table_name, string col_name);


#endif // !_API_H_
