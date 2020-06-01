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
    int loadDiskBlock(int page_id, std::string file_name, int block_id);
public:
    // ���캯��
    BufferManager(int frame_size);
    // ��������
    ~BufferManager();
    // ͨ��ҳ�ŵõ�ҳ�ľ��(һ��ҳ��ͷ��ַ)
    char* getPage(std::string file_name, int block_id);
    // ���page_id����Ӧ��ҳ�Ѿ����޸�
    void modifyPage(int page_id);
    // ��סһ��ҳ
    void pinPage(int page_id);
    // ���һ��ҳ�Ķ�ס״̬(��Ҫע�����һ��ҳ���ܱ���ζ�ס���ú���ֻ�ܽ��һ��)
    // �����Ӧҳ��pin_count_Ϊ0���򷵻�-1
    int unpinPage(int page_id);
    // ����Ӧ�ڴ�ҳд���Ӧ�ļ��Ķ�Ӧ�顣����ķ���ֵΪint�����о���ʵûʲô�ã�������Ϊvoid
    int flushPage(int page_id, std::string file_name, int block_id);
    // ��ȡ��Ӧ�ļ��Ķ�Ӧ�����ڴ��е�ҳ�ţ�û���ҵ�����-1
    int getPageId(std::string file_name, int block_id);
};

#endif