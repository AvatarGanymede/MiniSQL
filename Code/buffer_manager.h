#pragma once
#ifndef _BUFFER_MANAGER_H_
#define _BUFFER_MANAGER_H_

#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
#include "pch.h"
#include "define.h"
#include "record_manager.h"

class Block
{
private:
	char data[BLOCKSIZE];
	std::string table_name;
	int block_id;
	bool dirty_bit;
	bool use_bit;
	bool is_pinned;
	int ptr;
	int free_space;
public:
	Block(std::string table = "", int _block_id = -1, bool _dirty_bit = false, bool _use_bit = false, bool _is_pinned = false) {
		table_name = table;
		block_id = _block_id;
		dirty_bit = _dirty_bit;
		use_bit = _use_bit;
		is_pinned = _is_pinned;
		for (int i = 0; i < BLOCKSIZE; i++) {
			data[i] = -1;
		}
		ptr = 0;
		free_space = BLOCKSIZE - 3;
		sprintf(data + 1, "%08x", BLOCKSIZE - 1);
	}
	~Block();
	void setTableName(std::string table);
	std::string getTableName();
	void setBlockId(int _block_id);
	int getBlockId();
	void setDirty(bool _dirty);
	bool isDirty();
	void setUsed(bool _use);
	bool isUsed();
	void setPinned(bool _pinned);
	bool isPinned();
	char* getData();

	char* getNextRecord();
};

// BufferManager�ࡣ�����ṩ�����������Ľӿڡ�
class BufferManager {
private:
    Block* Pages;           // ����أ�ʵ���Ͼ���һ��Ԫ��ΪPage�����飬ʵ���ڴ�ռ佫�����ڶ���
    int page_num;           // ��¼��ҳ��
    int current_position;   // ʱ���滻������Ҫ�õ��ı���
    int getEmptyPageId();
    // ����Ӧ�ļ��Ķ�Ӧ�������Ӧ�ڴ�ҳ�������ļ������ڷ���-1�����򷵻�0
    bool loadDiskBlock(int page_id, std::string table_name, int block_id);
    void initialize();
public:
    // ���캯��
    BufferManager(int buffer_size = MAXBUFFERSIZE) :current_position(0), page_num(min(buffer_size, MAXBUFFERSIZE))
    {
        initialize();
    };
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