# include <iostream>
# include <vector>
using namespace std;

/* 键值对 */
struct Pair {
  public:
    int key;
    string val;
    Pair(int key, string val) {
        this->key = key;
        this->val = val;
    }
};

class HashMapChaining
{
private:
    int size;                       // 键值对的数量
    int capacity;                   // 整个哈希表的容量
    double loadThres;               // 负载因子阈值（用于触发哈希表整体扩容）
    int extendRatio;                // 扩容倍数
    vector<vector<Pair *>> buckets; // 桶数组
    // 解释这里的 vector 嵌套：
    /**
     *  在上一个文件（即这一套hashtable的实现）中用vector提供的数组来简易存储哈希表 
     *  然后这里要让每一个桶通过链表（这里通过vector简单地实现：因为vector自带一个迭代器不断往下迭代
     *  这种方法和用动态数组去通过静态方法（数组）构造链表的方式相同（相比于直接实现动态链表很明显这里不再需要变动指针）
     *  于是总结vector的嵌套用法：
     *  vector<type> name type为数组中容纳的类型
     *  因此 vector<Pair *> 表示一个容纳 Pair的指针 的数组
     *  这里于是不需要后面的name
     *  然后在外部嵌套一个vector<> buckets构造更大的数组并以 buckets 命名
     */ 
public:
    HashMapChaining() : size(0), capacity(4), loadThres(2.0/3), extendRatio(2) {
        buckets.resize(capacity);
    }
    ~HashMapChaining()
    {
        for (auto &bucket : buckets)
        {
            for (Pair *pair : bucket)
            {
                // free memory
                delete pair;
            }
            
        }
        
    }

    /* Hash Func */
    int hashFunc(int key)
    {
        return key % capacity;
    }

    /*负载因子*/
    double loadFactor()
    {
        return (double)size / (double)capacity;
    }

    /* Get Key */
    string get(int key)
    {
        int index = hashFunc(key);
        for (Pair *pair : buckets[index])
        {
            if (pair->key == key)
            {
                return pair->val;
            }
            
        }
        return nullptr;
    }
    /* Add val */
    void put(int key, string val)
    {
        // 每次进行添加操作时先确定是否扩容
        if (loadFactor() > loadThres)
        {
            extend(); // this->extend 的使用通常是在有重名的情况下，为了明确指示要访问成员函数或成员变量时才需要。如果在当前成员函数内部没有同名的局部变量或参数，可以省略 this->。
        }
        int index = hashFunc(key);
        // 遍历桶，如果 key 相同，则更新 val 并返回
        for (Pair *pair : buckets[index])
        {
            if (pair->key == key)
            {
                pair->val = val;
                return;
            }
            
        }
        // 找不到则更新vector容器的尾部
        buckets[index].push_back(new Pair(key, val));
        size++; 
    }

    /* Extend */
    void extend()
    {
        // 暂存和扩容复制
        vector<vector<Pair *>> bucketsTmp = buckets;
        // init
        capacity *= extendRatio;
        buckets.clear();
        buckets.resize(capacity);
        size = 0;
        // 复制
        for (auto &bucket : bucketsTmp) // 这里如果设置成buckets便会删除原有的参数
        {
            for (Pair *pair : bucket)
            {
                put(pair->key, pair->val);
                // free memory
                delete pair;
            }
        }
        
    }

    /* Remove Key */
    void remove(int key)
    {
        int index = hashFunc(key);
        auto &bucket = buckets[index];
        // 开始遍历，删除键值对
        for (int i = 0; i < bucket.size(); i++)
        {
            if (bucket[i]->key == key)
            {
                Pair *tmp = bucket[i];
                //  关于这里为什么是begin()+i：当上式为 true 的时候，i 为从0开始的编号
                //  换句话说，设第 m 个值匹配，则 i = m-1，而 begin() 指向第一个元素（对应的 i 值为 0）
                //  此时的删除编号即为 0+m-1=m-1 ，也就是第 m 个值的编号
                bucket.erase(bucket.begin()+i); // 删除键值对
                delete tmp; // 释放内存，因为erase不能释放内存(user's resposibility)，故需要设一个指针用于释放内存
                size--;
                return;
            }
            
        }
        
    }

    /* 打印哈希表 */
    void print()
    {
        for (auto &bucket : buckets)
        {
            cout << "[";
            for (Pair *pair : bucket)
            {
                cout << pair->key << "->" << pair->val << ", ";
            }
            cout << "]" << endl;

        }
    }
};

int main() {
    HashMapChaining hashMap;
    // 添加一些键值对
    hashMap.put(1, "One");
    hashMap.put(2, "Two");
    hashMap.put(3, "Three");
    hashMap.print();
    hashMap.put(4, "Four");
    hashMap.put(20, "Twenty");
    // 打印哈希表
    cout << "Hash Table Contents:" << endl;
    hashMap.print();
    // 查询键值对
    int keyToFind = 2;
    string foundValue = hashMap.get(keyToFind);
    if (!foundValue.empty()) {
        cout << "Value for key " << keyToFind << " is: " << foundValue << endl;
    } 
    else {
        cout << "Key " << keyToFind << " not found in the hash table." << endl;
    }
    foundValue = hashMap.get(20);
    if (!foundValue.empty()) {
        cout << "Value for key " << 20 << " is: " << foundValue << endl;
    } 
    else {
        cout << "Key " << 20 << " not found in the hash table." << endl;
    }
    // 删除一个键值对
    int keyToRemove = 3;
    hashMap.remove(keyToRemove);
    cout << "Removed key " << keyToRemove << endl;

    // 打印更新后的哈希表
    cout << "Updated Hash Table Contents:" << endl;
    hashMap.print();
    return 0;
}