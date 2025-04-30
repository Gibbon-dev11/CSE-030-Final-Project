#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include "ArrayList.h"

#include <cmath>

inline int extractInt(int x){
    return x;
}

inline int extractInt(std::string x){
    int result;

    for (int i = 0; i < std::min((int)x.length(), 4); i++){
        result += x[i] * pow(256, i);
    }

    return result;
}

inline int extractInt(float x){
    int result;
    unsigned char* c = (unsigned char*)&x;

    for (int i = 0; i < 4; i++){
        result += *c * pow(256, i);
        c++;
    }

    return result;
}

template <class T>
class HashTable;

template <class T>
std::ostream& operator<<(std::ostream& os, const HashTable<T>& ht);

template <class T>
class HashTable {
    int capacity;
    int size;

    ArrayList<ArrayList<T>> table;

    int f(T x){
        int temp = extractInt(x);

        int ans = temp % capacity;

        if (ans < 0) ans += capacity;

        return ans;
    }

    void inflate(){
        if (size/capacity >= 5){
            ArrayList<T> temp;
            for (int i = 0; i < capacity; i++){
                for (int j = 0; j < table[i].size(); j++){
                    temp.append(table[i][j]);
                }
            }
            for (int i = 0; i < capacity; i++){
                while (table[i].size() > 0){
                    table[i].removeLast();
                }
            }

            capacity *= 2;

            while (table.size() < capacity){
                table.append(ArrayList<T>());
            }
            size = 0;
            for (int i = 0; i < temp.size(); i++){
                insert(temp[i]);
            }
        }
    }

    static_assert(
        //condition, and //if the condition is not met, what error message should we display
        std::is_same<T, int>::value || std::is_same<T, float>::value || std::is_same<T, std::string>::value,
        "Template arguments should be int, float, or string"
    );
    
public:
    HashTable(int k=10){
        capacity = k;
        size = 0;
        for (int i = 0; i < capacity; i++){
            table.append(ArrayList<T>());
        }
    }

    void insert(T value){
        int index = f(value);
        table[index].append(value);
        size++;
        inflate();
    }

    bool search(T value){
        int index = f(value);
        return table[index].search(value);
    }

    friend std::ostream& operator<<<>(std::ostream& os, const HashTable& table);
    friend struct TestProgram;
    friend std::string minVal(HashTable<std::string> ht);
};

template class HashTable<int>;
template class HashTable<float>;
template class HashTable<std::string>;

template <class T>
inline std::ostream& operator<<(std::ostream& os, const HashTable<T>& ht){
    for (int i = 0; i < ht.capacity; i++){
        os << i << ": " << ht.table[i] << "\n";
    }

    return os;
}

#endif