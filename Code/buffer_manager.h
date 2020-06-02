#pragma once
#ifndef _BUFFER_MANAGER_H_
#define _BUFFER_MANAGER_H_ 1

#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
#include "pch.h"
#include "define.h"
#include "record_manager.h"


// BufferManager�ࡣ�����ṩ�����������Ľӿڡ�
class BufferManager {
private:
    Block* Pages;           // ����أ�ʵ���Ͼ���һ��Ԫ��ΪPage�����飬ʵ���ڴ�ռ佫�����ڶ���
    int page_num;           // ��¼��ҳ��
    int current_position;   // ʱ���滻������Ҫ�õ��ı���
    int getEmptyPageId();
    // ����Ӧ�ļ��Ķ�Ӧ�������Ӧ�ڴ�ҳ�������ļ������ڷ���-1�����򷵻�0
    bool loadDiskBlock(int page_id, std::string table_name, int block_id);
public:
    // ���캯��
    BufferManager(int buffer_size = MAXBUFFERSIZE) :current_position(0), page_num(min(buffer_size, MAXBUFFERSIZE)), Pages(new Block[buffer_size]) {};
    // ��������
    ~BufferManager();
    // ͨ��ҳ�ŵõ�ҳ�ľ��(һ��ҳ��ͷ��ַ)
    char* getPage(std::string table_name, int block_id);
    // ���page_id����Ӧ��ҳ�Ѿ����޸�
    void modifyPage(int page_id);
    // ��סһ��ҳ
    void pinPage(int page_id);
    // ���һ��ҳ�Ķ�ס״̬(��Ҫע�����һ��ҳ���ܱ���ζ�ס���ú���ֻ�ܽ��һ��)
    // �����Ӧҳ��pin_count_Ϊ0���򷵻�-1
    void unpinPage(int page_id);
    // ����Ӧ�ڴ�ҳд���Ӧ�ļ��Ķ�Ӧ�顣
    void flushPage(int page_id);
};

#endif