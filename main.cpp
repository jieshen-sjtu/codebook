/*
 * main.cpp
 *
 *  Created on: Feb 2, 2014
 *      Author: jieshen
 */

#include "codebook.hpp"
#include <glog/logging.h>
#include <vl/kmeans.h>
#include <vl/host.h>
#include <vl/kdtree.h>

int main(int argc, char* argv[])
{
  google::InitGoogleLogging(argv[0]);

  LOG(ERROR)<< "Start testing codebook";

  VlRand rand;

  uint32_t numData = 10000;
  uint32_t dimension = 128;
  uint32_t numCenters = 2000;

  float * data;

  uint32_t dataIdx, d;

  vl_rand_init(&rand);
  vl_rand_seed(&rand, 1000);

  LOG(ERROR)<< "Start Generating data";

  data = (float*) vl_malloc(sizeof(float) * dimension * numData);

  for (dataIdx = 0; dataIdx < numData; dataIdx++)
  {
    for (d = 0; d < dimension; d++)
    {
      float randomNum = (float) vl_rand_real3(&rand) + 1;
      data[dataIdx * dimension + d] = randomNum;
    }
  }

  jieshen::CodeBook codebook;
  codebook.set_K(numCenters);
  codebook.set_dim(dimension);

  LOG(ERROR)<< "Start clustering";

  codebook.GenKMeans(data, numData);
  LOG(ERROR)<< "Done";

  vl_free(data);

  FILE* output = fopen("book.txt", "w");
  codebook.save(output);
  LOG(ERROR) << "save to book.txt";

  return 0;
}

