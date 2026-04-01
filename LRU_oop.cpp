#include <iostream>
#include <list>
#include <unordered_map>
#include <algorithm>

class CacheLRU{
private:
   std::list<std::pair<int, char>> LRU;
   std::unordered_map<int, std::list<std::pair<int, char>>::iterator> list_it;
   int max = 3;

   public:
   CacheLRU(int max) 
    :max(max){}

   void put(int key, char value)
   {
        auto it = list_it.find(key);
        if(it != list_it.end())
            {
                it->second->second = value;
                LRU.splice(LRU.begin(), LRU, it->second);
            }
        else{
            if(LRU.size() > max)
                {
                    auto last_key = LRU.back();
                    list_it.erase(last_key.first);
                    LRU.pop_back();
                }
            LRU.emplace_front(key, value);
            list_it[key] = LRU.begin();
        }
   }

   char get(int key)
    {   
        auto it = list_it.find(key);
        if(it != list_it.end())
            {
            LRU.splice(LRU.begin(), LRU, it->second );
            return it->second->second;
            }
        return -1;
    }

    friend std::ostream& operator<<(std::ostream& os, const CacheLRU& LRU);
};

    std::ostream& operator<<(std::ostream& os, const CacheLRU& list){
        for (auto um : list.LRU)
        {
            for (auto pair : um)
            os<<pair.first<<" "<<pair.second<<std::endl;
        }
        os<<std::endl;
        return os;
    }

int main(){

    CacheLRU LRU{3};

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
