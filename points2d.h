// Name: Chengen Wei
// CSCI335
// Assignment 1
// points2d.h
// Due day: 2/16/23
// class Points2D is used for

#ifndef CSCI335_HOMEWORK1_POINTS2D_H_
#define CSCI335_HOMEWORK1_POINTS2D_H_

#include <array>
#include <iostream>
#include <cstddef>
#include <string>
#include <sstream>
#include <stdlib.h>

namespace teaching_project {

// Place comments that provide a brief explanation of the class,
// and its sample usage.
template<typename Object>
class Points2D {
 public:
  // Default "big five" -- you have to alter them for your assignment.
  // That means that you will remove the "= default" statement.
  //  and you will provide an implementation.
  

  // Zero-parameter constructor.
  // Set size to 0.
  Points2D<Object>() {
    this->size_ = 0;
    this->sequence_ = nullptr;
  };

  //Size only constructor
  Points2D<Object>(int length_) {
    this->size_ = length_;
    this->sequence_ = new std::array<Object,2>[length_];
  };

  // Copy-constructor.
  Points2D(const Points2D &rhs) {
    this->sequence_ = new std::array<Object, 2>[rhs.size_];
    this->size_ = rhs.size_;
    for(size_t i; i < rhs.size_; i++) {
      this->sequence_[i][0] = rhs[i][0];
      this->sequence_[i][1] = rhs[i][1];
    }
  };

  // Copy-assignment. If you have already written
  // the copy-constructor and the move-constructor
  // you can just use:
  // {
  // Points2D copy = rhs;
  // std::swap(*this, copy);
  // return *this;
  // }
  Points2D &operator=(const Points2D &rhs) {
    Points2D copy = rhs;
    std::swap(*this, copy);
    return *this;
  };

  // Move-constructor.
  Points2D(Points2D &&rhs) : sequence_{rhs.sequence_}, size_{rhs.size_} {
    rhs.size_ = 0;
    rhs.sequence_ = nullptr;
  };

  // Move-assignment.
  // Just use std::swap() for all variables.
  Points2D &operator=(Points2D &&rhs) {
    if (this != &rhs) {
      std::swap(this->sequence_, rhs.sequence_);
      std::swap(this->size_, rhs.size_);
    }
    return *this;
  };

  //Destructor to ensure all data is freed
  ~Points2D() {
    if(this->size_ > 0) {
      delete this->sequence_;
    }
  };

  // End of big-five.

  // One parameter constructor.
  Points2D(const std::array<Object, 2>& item) {
    this->size_ = 1;
    this->sequence_ = new std::array<Object,2>[1];
    this->sequence_[0][0] = item[0];
    this->sequence_[0][1] = item[1];
  };

  // Read a chain from standard input.
  void ReadPoints2D() {
    // Part of code included (without error checking).
    std::string input_line;
    std::getline(std::cin, input_line);
    std::stringstream input_stream(input_line);
    if (input_line.empty()) return;
    // Read size of sequence (an integer).
    int size_of_sequence;
    input_stream >> size_of_sequence;
    this->size_ = size_of_sequence;
    this->sequence_ = new std::array<Object, 2>[size_of_sequence];
    
    Object token;
    for (int i = 0 ;input_stream >> token; ++i) {
      this->sequence_[i][0] = token;
      input_stream >> token;
      this->sequence_[i][1] = token;
    }
    
  }

  size_t size() const {
    return this->size_;
  }

  // @location: an index to a location in the sequence.
  // @returns the point at @location.
  // const version.
  // abort() if out-of-range.
  const std::array<Object, 2>& operator[](size_t location) const {
    if (location > this->size_) {
      abort();
    }
    return this->sequence_[location];
  }

 //  @c1: A sequence.
 //  @c2: A second sequence.
 //  @return their sum. If the sequences are not of the same size, append the
 //    result with the remaining part of the larger sequence.
 friend Points2D operator+(const Points2D &c1, const Points2D &c2) {
   size_t bigger = 0;
   size_t smaller = 0;
   if (c1.size_ > c2.size_) {
      bigger = c1.size_;
      smaller = c2.size_;
   } else {
     bigger = c2.size_;
     smaller = c1.size_;
   }

   Points2D points(bigger);
   for(size_t i = 0; i < smaller; i++) {
     points[i][0] = c1[i][0] + c2[i][0];
     points[i][1] = c1[i][1] + c2[i][1];
   }

   if (c1.size_ > c2.size_) {
     for(size_t i = smaller; i < bigger; i++) {
       points[i][0] = c1[i][0];
       points[i][1] = c1[i][1];
     }
   } else {
     for(size_t i = smaller; i < bigger; i++) {
       points[i][0] = c2[i][0];
       points[i][1] = c2[i][1];
     }
   }
  return points;
 }

 // Overloading the << operator.
 friend std::ostream &operator<<(std::ostream &out, const Points2D &some_points2) {
   if (some_points2.size_ == 0) {
     out << "()" << std::endl;
     return out;
   }

   for(size_t i = 0; i < some_points2.size_; i++) {
     out << "(";
     out << some_points2[i][0];
     out << ",";
     out << some_points2[i][1];
     out << ")";
   }

   out << std::endl;
   return out;
 }
 
 private:
  // Sequence of points.
  std::array<Object, 2> *sequence_;
  // Size of sequence.
  size_t size_;

};

}  // namespace teaching_project
#endif // CSCI_335_HOMEWORK1_POINTS2D_H_
