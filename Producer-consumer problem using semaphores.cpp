#include <bits/stdc++.h>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>

using namespace std;

const int BUFFER_SIZE = 5;
queue<int> buffer;

mutex mtx;
condition_variable cond_producer;
condition_variable cond_consumer;

void producer(int id)
{
    for (int i = 0; i < 10; ++i)
    {
        unique_lock<mutex> lock(mtx);
        cond_producer.wait(lock, []{ return buffer.size() < BUFFER_SIZE; });  // Capture mutex implicitly
        int item = i;
        buffer.push(item);
        cout << "Producer " << id << " produced: " << item << ", Buffer size: " << buffer.size() << endl;

        cond_consumer.notify_one();  // Notify consumer

        this_thread::sleep_for(chrono::milliseconds(100));
    }
}

void consumer(int id)
{
    for (int i = 0; i < 10; ++i)
    {
        unique_lock<mutex> lock(mtx);

        cond_consumer.wait(lock, []{ return !buffer.empty(); });  // Capture mutex implicitly

        int item = buffer.front();
        buffer.pop();
        cout << "Consumer " << id << " consumed: " << item << ", Buffer size: " << buffer.size() << endl;

        cond_producer.notify_one();  // Notify producer

        this_thread::sleep_for(chrono::milliseconds(150));
    }
}

int main()
{
    const int NUM_PRODUCERS = 2;
    const int NUM_CONSUMERS = 2;

    thread producers[NUM_PRODUCERS];
    thread consumers[NUM_CONSUMERS];

    for (int i = 0; i < NUM_PRODUCERS; ++i)
    {
        producers[i] = thread(producer, i + 1);
    }

    for (int i = 0; i < NUM_CONSUMERS; ++i)
    {
        consumers[i] = thread(consumer, i + 1);
    }

    for (int i = 0; i < NUM_PRODUCERS; ++i)
    {
        producers[i].join();
    }

    for (int i = 0; i < NUM_CONSUMERS; ++i)
    {
        consumers[i].join();
    }

    cout << "All producers and consumers have finished." << endl;

    return 0;
}
