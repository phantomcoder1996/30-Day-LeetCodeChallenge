//
//  LRUCache.cpp
//  LeetCodeChallenge
//
//  Created by Reem Gody on 4/24/20.
//  Copyright © 2020 MacBook Pro. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

struct node{
    int key;
    int value;
    int rank;
    
    node(int key,int value, int rank)
    {
        this -> key = key;
        this -> value = value;
        this -> rank = rank;
    }
    
    bool operator< (const node& rhs)
    {
        return rank < rhs.rank;
    }
    
};

class LRUCache
{
        
private:
    vector<node*> heap;
    unordered_map<int,int> ki;
    int time;
    int capacity;
    int size;
    
    
    void increase_key_in_heap(int key)
    {
        int i = ki[key];
        heap[i]->rank = time;
        min_heapify(i);
    }
    
    void min_heapify(int i)
    {
        int n = size;
        int smallest = i;
        int left = (i<<1)+1;
        int right = (i<<1)+2;
        
        if(left<n && *heap[left]<*heap[smallest])
            smallest = left;
        if(right<n && *heap[right]<*heap[smallest])
            smallest = right;
        if(smallest!=i)
        {
        int i_key = heap[i]->key;
        int smallest_key = heap[smallest]->key;
        ki[i_key]= smallest;
        ki[smallest_key]=i;
        swap(heap[i],heap[smallest]);
        min_heapify(smallest);
        }
    }
    
    node* extract_min_from_heap()
    {
        
        return nullptr;
    }
    
    void insert_key_in_heap(int key,int value)
    {
        
        node* n = new node(key,value,time);
        if(size<capacity)
        {
            heap[size] = n;
            ki[key] = size;
            size++;
        }
        else
        {
        int zero_key = heap[0]->key;
        ki.erase(zero_key);
// remove key zero from unordered_map
        heap[0]=n;
        ki[key]=0;
        min_heapify(0);
            
        
        }
        
    }
    
public:
    
    int get(int key)
        {
        time++;
        unordered_map<int, int>::iterator  tmp = ki.find(key);
        if(tmp!=ki.end())
        {
        int index = ki[key];
        int value = heap[index]->value;
        increase_key_in_heap(key);
        return value;
        }
        else
        {
        return -1; //if not found
        }
    }
    
    void put(int key,int value)
    {   time++;
        if(ki.find(key)!=ki.end())
        {
            increase_key_in_heap(key);
            int index = ki[key];
            heap[index]->value = value;
        }
        else{
        insert_key_in_heap(key, value);
        }
    }
        
    LRUCache(int capacity)
        {
        this->size = 0;
        this->capacity = capacity;
        this->time =0;
        heap.resize(capacity);
        }
    
};


int main()
{
    
        LRUCache* cache = new LRUCache(2);
        
        int x;
        cache->put(1,1);
        x = cache->get(1);
        cout<<x<<endl; //1
        x = cache->get(4);
        cout<<x<<endl; //-1
        cache->put(2,2);
        x = cache->get(2);
        cout<<x<<endl;//2
        cache->put(3,3);
        x = cache->get(1); //-1
        cout<<x<<endl;
        x = cache->get(2); //2
        cout<<x<<endl;
        x = cache->get(3); //3
        cout<<x<<endl;
        x = cache->get(2);
        cout<<x<<endl; //2
        cache->put(4,4);
        x = cache->get(3);
        cout<<x<<endl; //-1
        x = cache->get(3);
        cout<<x<<endl; //-1
        x = cache->get(4);
        cout<<x<<endl; //4
        x = cache->get(2);
        cout<<x<<endl; //2
        x = cache->get(4);
        cout<<x<<endl; //4
        cache->put(5,5);
        x = cache->get(4);
        cout<<x<<endl; //4
        x = cache->get(2);
        cout<<x<<endl; //-1
        x = cache->get(5);
        cout<<x<<endl; //5
        cache->put(4,7);
        cache->put(2,2);
        x = cache->get(5);
        cout<<x<<endl; //-1
        x = cache->get(4);
        cout<<x<<endl; //7
        x = cache->get(2);
        cout<<x<<endl; //2
        
        
        
        
    return 0;
}
