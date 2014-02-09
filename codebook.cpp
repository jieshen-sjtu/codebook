/*
 * codebook.cpp
 *
 *  Created on: Feb 1, 2014
 *      Author: jieshen
 */

#include "codebook.hpp"

#include <vl/kmeans.h>

#include <glog/logging.h>
#include <cstdlib>
#include <cstdio>

namespace jieshen
{
  CodeBook::CodeBook()
      : dim_(0), K_(0), clusters_(NULL)
  {
  }

  CodeBook::CodeBook(const uint32_t dim, const uint32_t K)
      : dim_(dim), K_(K), clusters_(NULL)
  {
  }

  CodeBook::~CodeBook()
  {
    clear();
  }

  void CodeBook::clear()
  {
    dim_ = 0;
    K_ = 0;

    if (clusters_)
      free(clusters_);
    clusters_ = NULL;
  }

  void CodeBook::save(FILE* output) const
  {
    if (clusters_ == NULL)
      LOG(FATAL)<< "Check the clusters";

      fprintf(output, "num_centers:%u dim:%u\n", K_, dim_);
      for (uint32_t i = 0; i < K_ * dim_; ++i)
      {
        fprintf(output, "%f ", clusters_[i]);
        if ((i + 1) % dim_ == 0)
        fprintf(output, "\n");
      }
    }

  void CodeBook::load(FILE* input)
  {
    clear();

    fscanf(input, "num_centers:%u dim:%u\n", &K_, &dim_);
    for (uint32_t i = 0; i < K_ * dim_; ++i)
    {
      fscanf(input, "%f ", clusters_ + i);
      if ((i + 1) % dim_ == 0)
        fscanf(input, "\n");
    }
  }

  void CodeBook::GenKMeans(const float* const data, const uint32_t num_data)
  {

    if (data == NULL)
    {
      fprintf(stderr, "NULL pointer for data\n");
      exit(-1);
    }

    VlKMeans* kmeans_model = vl_kmeans_new(VL_TYPE_FLOAT, VlDistanceL2);

    // use the ANN for fast computation
    vl_kmeans_set_algorithm(kmeans_model, VlKMeansANN);
    vl_kmeans_set_num_trees(kmeans_model, NUM_KDTREES);
    vl_kmeans_set_max_num_comparisons(kmeans_model, MAX_COMP);
    vl_kmeans_set_max_num_iterations(kmeans_model, MAX_KMEANS_ITER);

    // initialize centers
    vl_kmeans_init_centers_with_rand_data(kmeans_model, data, dim_, num_data,
                                          K_);

    vl_kmeans_refine_centers(kmeans_model, data, num_data);

    const float* clusters = (const float*) vl_kmeans_get_centers(kmeans_model);

    if (clusters_ != NULL)
      free(clusters_);

    clusters_ = (float*) vl_malloc(sizeof(float) * K_ * dim_);
    memcpy(clusters_, clusters, sizeof(float) * K_ * dim_);

    vl_kmeans_delete(kmeans_model);
  }
}

