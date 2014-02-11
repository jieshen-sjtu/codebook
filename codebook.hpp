/*
 * codebook.hpp
 *
 *  Created on: Feb 1, 2014
 *      Author: jieshen
 */

#ifndef __codebook_CODEBOOK_HPP__
#define __codebook_CODEBOOK_HPP__

#include <stdint.h>
#include <cstddef>
#include <cstdio>
#include <boost/shared_ptr.hpp>

namespace EYE
{
  using boost::shared_ptr;

  class CodeBook
  {
  public:
    enum
    {
      MAX_KMEANS_ITER = 100, NUM_KDTREES = 3, MAX_COMP = 500,
    };

    // constructor and destructor
  public:
    CodeBook();
    CodeBook(const uint32_t dim, const uint32_t K);
    ~CodeBook();

  public:
    void clear();

    // setting and accessing
  public:
    inline void set_dim(const uint32_t dim)
    {
      dim_ = dim;
    }
    inline void set_K(const uint32_t K)
    {
      K_ = K;
    }

    inline uint32_t get_dim() const
    {
      return dim_;
    }
    inline uint32_t get_K() const
    {
      return K_;
    }
    inline const float* get_clusters() const
    {
      return clusters_;
    }

    // IO operation
  public:
    void save(FILE* output) const;
    void load(FILE* input);

  private:
    uint32_t dim_;
    uint32_t K_;
    float* clusters_;

  public:
    // ensure that the clusters should be allocate the memory outside
    void GenKMeans(const shared_ptr<float>& data, const uint32_t num_data);
  };
}

#endif /* __codebook_CODEBOOK_HPP__ */
