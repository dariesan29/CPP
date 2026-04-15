#include <iostream>
#include <array>
#include <thread>
#include <mutex>
#include <chrono>

template <typename T, size_t N>
class RingBuffer
{
private:
    std::array<T, N> buffer;
    size_t head = 0;
    size_t tail = 0;
    size_t availability = 0;
    std::mutex m;

public:
    bool push(T& item)
    {   
        std::unique_lock<std::mutex> lg(m);
        if(availability == N){
            std::cout<<"Buffer is full"<<std::endl;
            lg.unlock();
            std::this_thread::sleep_for(std::chrono::seconds(1));
            lg.lock();
            return false;
        }
        buffer[head % N] = item;
        head++;
        availability++;
        std::cout<<"Push completed - "<<"head: "<<item<<std::endl;
        return true;
    }

    bool push(T&& item)
    {   
        item = 6;
        std::unique_lock<std::mutex> lg(m);
        if(availability == N){
            std::cout<<"Buffer is full"<<std::endl;
            lg.unlock();
            std::this_thread::sleep_for(std::chrono::seconds(1));
            lg.lock();
            return false;
        }
        buffer[head % N] = item;
        head = (head + 1) % N;
        availability++;
        std::cout<<"Push completed - "<<"head: "<<item<<std::endl;
        return true;
    }

    bool pop(T& item)
    {   
        std::unique_lock<std::mutex> lg(m);
        if(!availability){
            std::cout<<"Buffer is empty"<<std::endl;
            lg.unlock();
            std::this_thread::sleep_for(std::chrono::seconds(1));
            lg.lock();
            return false;
        }
        item = std::move(buffer[tail % N]);
        tail = (tail + 1) % N;
        availability--;
        std::cout<<"Pop completed - "<<"tail: "<<item<<std::endl;
        return true;
    }

    void print()
    {
        for(const auto& item : buffer)
            std::cout<<item<<" ";
        std::cout<<std::endl;
    }
};


int main()
{   
    RingBuffer<int, 10> rb;
    int item;
    int item_to_push;

    int &&a = 5;
    a = 2;

    item_to_push = 2;

    std::thread producer([&](){
        for (int i = 1; i < 100; i++)
            rb.push(i);
    });

    std::thread consumer([&](){
        for (int i = 1; i < 100; i++)
            rb.pop(i);
    });

    producer.join();
    consumer.join();

    return 0;
}