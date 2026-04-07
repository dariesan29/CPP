#include <iostream>
#include <array>

template <typename T, size_t N>
class RingBuffer
{
private:
    std::array<T, N> buffer;
    size_t head = 0;
    size_t tail = 0;
    size_t availability = 0;

public:
    bool push(T item)
    {       
        if(availability == N){
            std::cout<<"Buffer is full"<<std::endl;
            return false;
        } 
        buffer[head % N] = item;
        head++;
        availability++;
        std::cout<<"Push completed - "<<"head: "<<item<<std::endl;
        return true; 
    }

    bool pop(T& item)
    {
        if(!availability){
            std::cout<<"Buffer is empty"<<std::endl;
            return false;
        }
        item = buffer[tail % N];
        tail++;
        availability--;
        std::cout<<"Pop completed - "<<"tail: "<<item<<std::endl;
        return true;
    }

    void print()
    {
        for(auto item : buffer)
            std::cout<<item<<" ";
        std::cout<<std::endl;
    }
};


int main()
{   
    RingBuffer<int, 4> rb;
    int item;

    rb.push(1);
    rb.push(2);
    rb.push(3);
    rb.push(4);
    rb.push(5);
    rb.push(6);

    rb.pop(item);

    rb.push(5);
    rb.push(6);
    rb.pop(item);
    rb.pop(item);
    rb.pop(item);
    rb.pop(item);
    rb.pop(item);

    rb.push(7);
    rb.print();
    return 0;
}