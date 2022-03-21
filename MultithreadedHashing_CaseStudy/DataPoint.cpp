#include <iostream>
#include <thread>
#include <mutex>
#include "DataPoint.h"

/*class DataPoint{
  private:
    mutex *my_mutex;
    int my_data;
  public:
    DataPoint();
    ~DataPoint();
    int GetData();
    void SetData(int new_data);
    void IncrementData(int amt);
}*/

DataPoint::DataPoint() {
    my_data = 0;
}
DataPoint::DataPoint(int start_val){
    my_data = start_val;
}

int DataPoint::GetData(){
    std::lock_guard<std::mutex> get_guard(my_mutex);
    return my_data;
}

void DataPoint::SetData(int new_val){
    std::lock_guard<std::mutex> set_guard(my_mutex);
    my_data = new_val;
}

void DataPoint::IncrementData(int amt){
    std::lock_guard<std::mutex> increment_guard(my_mutex);
    my_data += amt;
}

