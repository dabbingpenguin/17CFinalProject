#ifndef BloomFilter_H
#define BloomFilter_H

#include <cmath>
#include <vector>
#include <string>
#include <fstream>
#include "GeneralHashFunctions.hpp"
#include "TreeList.hpp"

class BloomFilter
{
  private:
    TreeList<bool> bloomFilter; 
    int SIZE;
    int elementSize;
  public:
    BloomFilter(int size)
    {
      // Fill up Bloom Filter with all 0's
      SIZE = size;
      elementSize = 0;

      for (int i=0; i<SIZE; ++i)
        bloomFilter.push_back(0);
      // Read from file to fill up Bloom Filter
      std::ifstream file("bloomfilter.bin", std::ios::binary | std::ios::in); 
      if (file.good())
      {
        for (int i=0; i<SIZE; ++i)
          file.read(reinterpret_cast<char*>(&bloomFilter[i]), sizeof(bool));           
      }
      file.close();
    }

    ~BloomFilter()
    {
      writeToFile();
    }

    void writeToFile()
    {
      std::ofstream file("bloomfilter.bin", std::ios::binary | std::ios::out); 
      for (int i=0; i<SIZE; ++i)
        file.write(reinterpret_cast<char*>(&bloomFilter[i]), sizeof(bool));           
    }

    void addString(std::string str)
    {
      bloomFilter[RSHash(str) % SIZE] = 1; 
      bloomFilter[FNVHash(str) % SIZE] = 1;
      elementSize ++;
      writeToFile();
    }

    bool isProbableToExist(std::string str)
    {
      return (bloomFilter[RSHash(str) % SIZE] && bloomFilter[FNVHash(str) % SIZE]);
    }
    
    float getProbabilityOfFalsePositives()
    {
      return powf(1.0f - expf((-1)*2*elementSize/SIZE), 2); 
    }
};

#endif