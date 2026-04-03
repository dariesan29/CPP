#include <iostream>
#include <list>
#include <unordered_map>
#include <algorithm>

class CacheLRU{
private:
   std::list<std::pair<int, char>> LRU;
   std::unordered_map<int, std::list<std::pair<int, char>>::iterator> MAP_it;
   int max = 3;

   public:
   CacheLRU(int max) 
    :max(max){}

   void put(int key, char value)
   {
        auto it = MAP_it.find(key);
        if(it != MAP_it.end())
            {
                it->second->second = value;
                LRU.splice(LRU.begin(), LRU, it->second);
            }
        else{
            if(LRU.size() == max)
                {
                    auto last_key = LRU.back();
                    MAP_it.erase(last_key.first);
                    LRU.pop_back();
                }
            LRU.emplace_front(key, value);
            MAP_it[key] = LRU.begin();
        }
   }

   char get(int key)
    {   
        auto it = MAP_it.find(key);
        if(it != MAP_it.end())
            {
            LRU.splice(LRU.begin(), LRU, it->second );
            return it->second->second;
            }
        return -1;
    }

    friend std::ostream& operator<<(std::ostream& os,CacheLRU& LRU);
};

    std::ostream& operator<<(std::ostream& os,CacheLRU& list){
        for (auto pair : list.LRU)
            os<<pair.first<<" "<<pair.second<<std::endl;
        os<<std::endl;
        return os;
    }

int main(){

    CacheLRU LRU{4};

    LRU.put(1, 'A');
    LRU.put(2, 'B');
    LRU.put(3, 'C'); 
    std::cout<<LRU;

    std::cout<<LRU.get(2)<<std::endl;
    std::cout<<LRU;

    std::cout<<LRU.get(4)<<std::endl;
    std::cout<<LRU;
    
    LRU.put(4, 'D');
    std::cout<<LRU;

    LRU.put(3, 'E');
    std::cout<<LRU;

    std::cout<<LRU.get(4)<<std::endl;
    std::cout<<LRU;

    LRU.put(1, 'A');
    std::cout<<LRU;

    return 0;
}
