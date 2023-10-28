# include <iostream>
# include <vector>
using namespace std;
// 一般来说除非主函数不在最后，前面可以不声明函数。

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

class HashMapOpenAddressing
{
private:
    int size;                       // 键值对的数量
    int capacity;                   // 整个哈希表的容量
    double loadThres;               // 负载因子阈值（用于触发哈希表整体扩容）
    int extendRatio;                // 扩容倍数
    vector<Pair *> buckets;         // 桶数组
    Pair* removed;                  // 删除标记
    /**
     * 在这种表示方法中，必须要使用 伪删除 的方法
     * 否则下一次寻址发生与被删除的 key 的 哈希碰撞 便会找不到位置
     * 在这段代码中，removed 是一个 Pair 的 指针对象，可以直接用于填充删除项
    */
public:
    HashMapOpenAddressing()
    {
        // 构造
        size = 0;
        capacity = 4;
        loadThres = 2.0 / 3.0;
        extendRatio = 2;
        buckets = vector<Pair *>(capacity, nullptr); // 按照容量批量建立（初始化）携带空指针的 vector 容器
        removed = new Pair(-1, "-1");
    }
    ~HashMapOpenAddressing()
    {
        // 释放内存
        // 可以复用第一个代码中的释放内存操作，因为主要内容是一致的
        for (const auto &bucket : buckets) {
            delete bucket;
        }
        // 因为删除标记也是指针，故一起删除
        delete removed;
        buckets.clear();
    }

    /* Hash Function */
    int hashFunc(int key)
    {
        return key % capacity;
    }

    /* 负载因子 */
    double loadFactor()
    {
        /** 这里采用了和刚才不同的负载因子返回方式，实际上这种方式中的
        *  static_cast<double>(size) 也是将 size 转化为 double 格式
        */
        return static_cast<double>(size) / capacity;
    }

    /* Get Key 查询操作 */
    string get(int key)
    {
        // 线性探测开始：从index向后遍历；
        // 以下为线性探测的代码：
        /*
        int index = hashFunc(key);
        for (int i = 0; i < capacity; i++) {
            // 计算桶索引，越过尾部返回头部
            int j = (index + i) % capacity;
            // 若遇到空桶，说明无此 key ，则返回 nullptr
            if (buckets[j] == nullptr)
                return nullptr;
            // 若遇到指定 key ，则返回对应 val
            if (buckets[j]->key == key && buckets[j] != removed)
                return buckets[j]->val;
        }
        return nullptr;
        */
        // 直接进行二次探测：
        int index = hashFunc(key);
        if (buckets[index] != nullptr && buckets[index]->key == key && buckets[index] != removed)
                return buckets[index]->val;
        // 一次探测失败时 
        int j = index;       
        for (int i = 1; i < capacity; i++)
        {
            j = (j + i*i) % capacity;
            /*
            // 若 j 爆了，说明无此 key ，返回 nullptr
            if (j > capacity)
                return nullptr;
            */
            // 根据下文，j 不可能爆
            // 若遇到空桶，说明无此 key ，则返回 nullptr
            if (buckets[j] == nullptr)
                return nullptr;
            // 若遇到指定 key ，则返回对应 val
            if (buckets[j]->key == key && buckets[j] != removed)
            {
                return buckets[j]->val;
            }

        }
        
    }
    
    /* 添加操作 */
    void put(int key, string val)
    {
        // 一样的扩容操作
        if (loadFactor() > loadThres)
        {
            extend();
        }
        int index = hashFunc(key);
        // 以下是线性探测的代码
        /*
         // 线性探测，从 index 开始向后遍历
        for (int i = 0; i < capacity; i++) {
            // 计算桶索引，越过尾部返回头部
            int j = (index + i) % capacity;
            // 若遇到空桶、或带有删除标记的桶，则将键值对放入该桶
            if (buckets[j] == nullptr || buckets[j] == removed) {
                buckets[j] = new Pair(key, val);
                size += 1;
                return;
            }
            // 若遇到指定 key ，则更新对应 val
            if (buckets[j]->key == key) {
                buckets[j]->val = val;
                return;
            }
        }       
        */
         // 以下是二次探测的代码
        if (buckets[index] != nullptr && buckets[index]->key == key)
        {
            buckets[index]->val == val;
        }    
        // 一次探测失败时 
        int j = index;       
        for (int i = 1; i < capacity; i++)
        {
            j = (j + i*i) % capacity;
            /*
            // 若 j 爆了，说明需要扩容 ，然后再次put
            if (j > capacity)
                extend();
                put(key, val);
                break;
            // 其实根本不会爆，因为上面的计算式使得j < capacity，然后一般来说当 负载因子 合适的时候不会出现过度拥挤以至于找不到有效地址的情况
            */
            // 若遇到空桶，或者具有删除标记，则进行键值对的更新与替换
            if (buckets[j] == nullptr || buckets[j] == removed)
            {
                buckets[j] = new Pair(key, val);
                size += 1;
                return;
            }
            // 若遇到指定 key ，则更新对应 val
            if (buckets[j]->key == key) 
            {
                buckets[j]->val = val;
                return;
            }

        }
        return;        
    }

    /* 删除对应key的键值对 */
    void remove(int key)
    {
        int index = hashFunc(key);
        // 以下是线性探测的代码：
        /*
        for (int i = 0; i < capacity; i++) {
            // 计算桶索引，越过尾部返回头部
            int j = (index + i) % capacity;
            // 若遇到空桶，说明无此 key ，则直接返回
            if (buckets[j] == nullptr)
                return;
            // 若遇到指定 key ，则标记删除并返回
            if (buckets[j]->key == key) {
                delete buckets[j]; // 释放内存
                buckets[j] = removed;
                size -= 1;
                return;
            }
        }        
        */
        //以下是二次探测的代码
        if (buckets[index] != nullptr && buckets[index]->key == key && buckets[index] != removed)
        {
                delete buckets[index]; // 释放内存
                buckets[index] = removed;
                size -= 1;
                return;
        }
        // 一次探测失败时 
        int j = index;       
        for (int i = 1; i < capacity; i++)
        {
            j = (j + i*i) % capacity;
            // 若遇到空桶，说明无此 key ，则返回
            if (buckets[j] == nullptr)
                return;
            // 若遇到指定 key ，则返回对应 val
            if (buckets[j]->key == key && buckets[j] != removed)
            {
                delete buckets[j];
                buckets[j] = removed;
                size -= 1;
                return;
            }

        }        
    }

    /* 扩容哈希表 */
    void extend()
    {
        // 和链表法类似 先暂存原来的hash表
        vector<Pair *> bucketsTmp = buckets;
        // init
        capacity *= extendRatio;
        buckets = vector<Pair *>(capacity, nullptr);
        size = 0;
        // 搬运键值对
        for (Pair* pair : bucketsTmp)
        {
            if (pair != nullptr && pair != removed)
            {
                put(pair->key, pair->val);
            }
            // free memory
            delete pair;
        }
        
    }

    /* 打印 */
    void print()
    {
        for (auto &pair : buckets)
        {
            if (pair != nullptr)
            {
                cout << pair->key << "->" << pair->val << endl;
            }
            else
            {
                cout << "nullptr" << endl;
            }
            
            
        }
        
    }
};

int main() {
    HashMapOpenAddressing hashMap;
    // 添加一些键值对
    hashMap.put(1, "One");
    hashMap.put(2, "Two");
    hashMap.put(3, "Three");
    hashMap.print();
    // 这里会运行 extend() 函数
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
    
    // 重新添加这里的键值对
    int keyNew = 11;
    hashMap.put(keyNew, "Eleven");
    cout << "Add a New Key" << keyNew << "->" << "Eleven";
    hashMap.print();
    

    // 打印更新后的哈希表
    cout << "Updated Hash Table Contents:" << endl;
    hashMap.print();
    return 0;
}

// 以上代码测试通过