#pragma once
#ifndef _BUFFER_MANAGER_H
#define _BUFFER_MANAGER_H

#pragma once
#include "pch.h"
#include "define.h"
class Block
{
private:
	BYTE data[BLOCKSIZE];
	std::string table_name;
	int block_id;
	bool dirty_bit;
	bool use_bit;
	bool is_pinned;
public:
	Block(std::string table = "", int _block_id = -1, bool _dirty_bit = false, bool _use_bit = false, bool _is_pinned = false) {
		table_name = table;
		block_id = _block_id;
		dirty_bit = _dirty_bit;
		use_bit = _use_bit;
		is_pinned = _is_pinned;
		for (int i = 0; i < BLOCKSIZE; i++) {
			data[i] = 255;
		}
		data[0] = 0;
		short free_space_ptr = BLOCKSIZE - 3;
		memcpy(data + 1, &free_space_ptr, sizeof(short));
		short free_space = BLOCKSIZE - 5;
		memcpy(data + BLOCKSIZE - 2, &free_space, sizeof(short));
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
	BYTE* getData();

	BYTE* getRecord(int ith);
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
	BufferManager(int page_num_ = MAXBUFFERSIZE) : current_position(0), page_num(min(page_num_, MAXBUFFERSIZE)) {
		initialize();
	};
	// ��������
	~BufferManager();
	// ͨ��ҳ�ŵõ�ҳ�ľ��(һ��ҳ��ͷ��ַ)
	Block* getPage(std::string table_name, int block_id);
	// ���page_id����Ӧ��ҳ�Ѿ����޸�
	void modifyPage(int page_id);
	// ��סһ��ҳ
	void pinPage(int page_id);
	// ���һ��ҳ�Ķ�ס״̬(��Ҫע�����һ��ҳ���ܱ���ζ�ס���ú���ֻ�ܽ��һ��)
	// �����Ӧҳ��pin_count_Ϊ0���򷵻�-1
	void unpinPage(int page_id);
	// ����Ӧ�ڴ�ҳд���Ӧ�ļ��Ķ�Ӧ�顣
	void flushPage(int page_id);
	int getBlockNum(std::string table_name);
	int getPageId(std::string table_name, int block_id);
};

#endif // !_BUFFER_MANAGER_H
