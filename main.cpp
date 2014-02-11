/*
 * main.cpp
 *
 *  Created on: Feb 2, 2014
 *      Author: jieshen
 */

#include "codebook.hpp"
#include <vl/kmeans.h>
#include <vl/host.h>
#include <vl/kdtree.h>
#include <iostream>
#include <boost/shared_ptr.hpp>
using namespace std;
using boost::shared_ptr;

int main(int argc, char* argv[])
{
  VlRand rand;

  uint32_t numData = 10000;
  uint32_t dimension = 128;
  uint32_t numCenters = 2000;

  uint32_t dataIdx, d;

  vl_rand_init(&rand);
  vl_rand_seed(&rand, 1000);

  cerr << "Start Generating data" << endl;;

  float* _data = (float*) malloc(sizeof(float) * dimension * numData);
  shared_ptr<float> data(_data);

  for (dataIdx = 0; dataIdx < numData; dataIdx++)
  {
    for (d = 0; d < dimension; d++)
    {
      float randomNum = (float) vl_rand_real3(&rand) + 1;
      _data[dataIdx * dimension + d] = randomNum;
    }
  }

  EYE::CodeBook codebook;
  codebook.set_K(numCenters);
  codebook.set_dim(dimension);

  cerr << "Start clustering" << endl;

  codebook.GenKMeans(data, numData);
  cerr << "Done" << endl;

  FILE* output = fopen("book.txt", "w");
  codebook.save(output);
  cerr << "save to book.txt" << endl;

  return 0;
}

