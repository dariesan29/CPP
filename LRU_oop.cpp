#include <iostream>
#include <list>
#include <unordered_map>
#include <algorithm>

template <typename T, typename V, size_t N>
class CacheLRU{
private:
   std::list<std::pair<T, V>> LRU;
   std::unordered_map<T, typename std::list<std::pair<T, V>>::iterator> MAP_it;

public:

   void put(T key, V value)
   {
        auto it = MAP_it.find(key);
        if(it != MAP_it.end())
            {
                it->second->second = value;
                LRU.splice(LRU.begin(), LRU, it->second);
            }
        else{
            if(LRU.size() == N)
                {
                    auto last_key = LRU.back();
                    MAP_it.erase(last_key.first);
                    LRU.pop_back();
                }
            LRU.emplace_front(key, value);
            MAP_it[key] = LRU.begin();
        }
   }

   V get(T key)
    {   
        auto it = MAP_it.find(key);
        if(it != MAP_it.end())
            {
            LRU.splice(LRU.begin(), LRU, it->second );
            return it->second->second;
            }
        return -1;
    }
    
   friend std::ostream& operator<< (std::ostream& os,CacheLRU<T, V, N>& list){
        for (auto pair : list.LRU)
            os<<pair.first<<" "<<pair.second<<std::endl;
        os<<std::endl;
        return os;
    }
};

int main(){

    CacheLRU<unsigned, int, 3> LRU;

    LRU.put(1, 5);
    LRU.put(2, 6);
    LRU.put(3, 7); 

    std::cout<<LRU;

    std::cout<<LRU.get(2)<<std::endl;
    std::cout<<LRU;

    std::cout<<LRU.get(4)<<std::endl;
    std::cout<<LRU;
    
    LRU.put(4, 4);
    std::cout<<LRU;

    LRU.put(3, 3);
    std::cout<<LRU;

    std::cout<<LRU.get(4)<<std::endl;
    std::cout<<LRU;

    LRU.put(1, 1);
    std::cout<<LRU;

    return 0;
}