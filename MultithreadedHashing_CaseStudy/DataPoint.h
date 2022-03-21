#include <thread>
#include <iostream>
#include <mutex>

class DataPoint{
  private:
    std::mutex my_mutex;
    int my_data;
  public:
    DataPoint();
    DataPoint(int start_val);
    int GetData();
    void SetData(int new_data);
    void IncrementData(int amt);
};