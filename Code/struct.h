#pragma once
#ifndef _BASIC_H_
#define _BASIC_H_ 1

#include "pch.h"

struct Attribute {
    int attri_num;  
    std::string attri_name[32]; 
    short attri_type[32]; 
    bool is_unique[32];  //�ж�ÿ�������Ƿ�unique����Ϊtrue
    short primary_key;  //�ж��Ƿ��������,-1Ϊ�����ڣ�������Ϊ����������λ��
    bool has_index[32]; //�ж��Ƿ��������
};

#endif