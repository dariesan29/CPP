#include <iostream>
#include <array>
#include <thread>
#include <mutex>
#include <chrono>
#include <condition_variable>

template <typename T, size_t N>
class RingBuffer
{
private:
    std::array<T, N> buffer;
    size_t head = 0;
    size_t tail = 0;
    size_t availability = 0;
    std::mutex m;
    std::condition_variable cv_push;
    std::condition_variable cv_pop;

public:
    bool push(T& item)
    {   
        std::unique_lock<std::mutex> ul(m);
        cv_push.wait(ul,[&](){
            if(availability == N)
                std::cout<<"Buffer is full \n";
            return availability < N;
        });
        std::cout<<"Head: "<<item;
        buffer[head % N] = std::move(item);
        head = (head + 1 ) % N;
        availability++;
        std::cout<<"- push completed"<<std::endl;
        cv_pop.notify_one();
        return true;
    }

    bool push(T&& item)
    {   
        std::unique_lock<std::mutex> ul(m);
        cv_push.wait(ul,[&](){
            if(availability == N)
                std::cout<<"Buffer is full \n";
            return availability < N;
        });
        std::cout<<"Head: "<<item;
        buffer[head % N] = std::move(item);
        head = (head + 1 ) % N;
        availability++;
        std::cout<<" - Push completed"<<std::endl;
        cv_pop.notify_one();
        return true;
    }

    bool pop(T& item)
    {   
        std::unique_lock<std::mutex> ul(m);
        cv_pop.wait(ul,[&](){
            if(availability == 0)
                std::cout<<"Buffer is empty \n";
            return availability != 0;
        });
        std::cout<<"Tail: "<<item;
        item = std::move(buffer[tail % N]);
        tail = (tail + 1) % N;
        availability--;
        std::cout<<" - Pop completed"<<std::endl;
        cv_push.notify_one();
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

    std::thread producer([&](){
        for (int i = 1; i < 100; i++)
            rb.push(i);
    });

    std::thread consumer([&](){
        for (int i = 1; i < 100; i++)
            rb.pop(item);
    });

    producer.join();
    consumer.join();

    return 0;
}