/*
 * @lc app=leetcode.cn id=146 lang=cpp
 *
 * [146] LRU 缓存机制
 */

#include<iostream>
#include<queue>
using namespace std;

// @lc code=start
class LRUCache {
    // starts from 1
    int lru[10001] = { 0 };
    int pos[10001] = { 0 };
    int head = 0;
    int tail = 0;
    queue<int> usequeue;
    int capacity;
    int size = 0;

    void update(int key){
        pos[key] = ++tail;
        usequeue.push(key);
        if (size==0) ++head;
    }

    void remove(){
        while (head < pos[usequeue.front()]){
            // invaild
            usequeue.pop();
            ++head;
        }
        pos[usequeue.front()] = 0;
        usequeue.pop();
        ++head;
        --size;
    }

public:
    LRUCache(int _capacity) {
        capacity = _capacity;
    }
    
    int get(int key) {
        if (pos[key]==0) {
            // no key
            return -1;
        } else {
            update(key);
            return lru[key];
        }
    }
    
    void put(int key, int value) {
        if (pos[key]==0){
            // no key
            lru[key] = value;
            // remove
            if (size==capacity)
                remove();
            update(key);
            ++size;
        } else {
            update(key);
            lru[key] = value;
        }
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
// @lc code=end

