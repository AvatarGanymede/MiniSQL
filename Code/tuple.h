#pragma once
#include "pch.h"
struct Data {
    int type;
    int datai;
    float dataf;
    std::string datas;
};
class Tuple {
private:
    std::vector<Data> contents;  //�洢Ԫ�����ÿ�����ݵ���Ϣ
    bool deleted;
public:
    Tuple() :deleted(false) {};
    Tuple(const Tuple& tuple_in){//����Ԫ��
        deleted = tuple_in.deleted;
        for (int i = 0; i < tuple_in.contents.size(); i ++){
            contents.push_back(tuple_in.contents[i]);
        }
    };  
    void addData(Data data_in);  //����Ԫ��
    std::vector<Data> getData()const;  //��������
    void eraseData(int i);
    int getSize();  //����Ԫ�����������
    bool isDeleted();
    void setDeleted();
    void showTuple();  //��ʾԪ���е���������
};
