#include <iostream>
#include <list>
#include <unordered_map>
#include <algorithm>

class CacheLRU{
   std::list<std::unordered_map<int, char>> LRU;
   int max = 3;

   public:
   CacheLRU(int max) 
    :max(max){}

   void put(int key, char value)
   {
        std::unordered_map<int, char> um;
        um[key] = value;
        LRU.push_front(um);
        if(LRU.size() > max)
            LRU.pop_back();
   }

   char get(int key)
    {   
        for (auto it = LRU.begin(); it != LRU.end(); it++){
            if (it->count(key))
                {
                    LRU.splice(LRU.begin(), LRU, it);
                    return it->at(key);
                }
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