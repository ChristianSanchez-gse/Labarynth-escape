#pragma once

#include <iostream>
#include <exception>
#include <stdexcept>
#include <algorithm>

using namespace std;

template<typename T>
class Grid {
private:
  struct ROW {
    T*  Cols;     // array of column elements
    size_t NumCols;  // total # of columns (0..NumCols-1)
  };

  ROW* Rows;     // array of ROWs
  size_t  NumRows;  // total # of rows (0..NumRows-1)
  int totalElements;
public:
  //
  // default constructor:
  //
  // Called automatically by C++ to construct a 4x4 Grid.  All
  // elements are initialized to the default value of T.
  //
  Grid() {
    Rows = new ROW[4];  // 4 rows
    NumRows = 4;
    totalElements = 0;
    // initialize each row to have 4 columns:
    for (size_t r = 0; r < NumRows; ++r) {
      Rows[r].Cols = new T[4];
      Rows[r].NumCols = 4;

      // initialize the elements to their default value:
      for (size_t c = 0; c < Rows[r].NumCols; ++c) {
        Rows[r].Cols[c] = T();  // default value for type T:
        totalElements++;
      }
    }
  }

  //
  // parameterized constructor:
  //
  // Called automatically by C++ to construct a Grid with R rows,
  // where each row has C columns. All elements are initialized to 
  // the default value of T.
  //
  Grid(size_t R, size_t C) {
    Rows = new ROW[R];
    NumRows = R;
    totalElements = 0;

    for (size_t r = 0; r < NumRows; ++r) {
        Rows[r].Cols = new T[C];
        Rows[r].NumCols = C;
            //initialize all thge elements to their values passed
        for(size_t c = 0; c < Rows[r].NumCols; ++c) {
            Rows[r].Cols[c] = T();
            totalElements++;
        }
    }

  }
    
  //
  // destructor:
  //
  // Called automatically by C++ to free the memory associated by the vector.
  //
  virtual ~Grid() {
      //iterate through each row and its corresponding columns and delete
      for (size_t i = 0; i < NumRows; i++) {
              delete [] Rows[i].Cols;
      }
      delete [] Rows;
  }


  //
  // copy constructor:
  //
  // Called automatically by C++ to construct a Grid that contains a
  // copy of an existing Grid.  Example: this occurs when passing
  // Grid as a parameter by value
  //
  //   void somefunction(Grid<int> G2)  <--- G2 is a copy:
  //   { ... }
  //
  Grid(const Grid<T>& other) {
      //copying the size rows array
      this->NumRows = other.NumRows;
      this->Rows = new ROW[other.NumRows];
      totalElements = 0;
      // iterating through each row and copying the columns
      for (size_t i = 0; i < NumRows; i++) {
          this->Rows[i].NumCols = other.Rows[i].NumCols;
          this->Rows[i].Cols = new T[other.Rows[i].NumCols];
          for (size_t j = 0; j < other.Rows[i].NumCols; j++) {
              this->Rows[i].Cols[j] = other.Rows[i].Cols[j];
              totalElements++;
          }
      }
  }
    
  //
  // copy operator=
  //
  // Called when you assign one vector into another, i.e. this = other;
  //
  Grid& operator=(const Grid& other) {
      if (this == &other) {
          return *this;
      }
      //iterate through each row and its corresponding columns and delete
      for (size_t i = 0; i < NumRows; i++) {
              delete [] Rows[i].Cols;
      }
      delete [] Rows;
      this->NumRows = other.NumRows;
      this->Rows = new ROW[other.NumRows];
      totalElements = 0;
      //make and copy other to this
      for (size_t i = 0; i < NumRows; i++) {
          this->Rows[i].NumCols = other.Rows[i].NumCols;
          this->Rows[i].Cols = new T[other.Rows[i].NumCols];
          for (size_t j = 0; j < other.Rows[i].NumCols; j++) {
              this->Rows[i].Cols[j] = other.Rows[i].Cols[j];
              totalElements++;
          }
      }
      return *this;  // TO DO:  update this, it is only here so code compiles.
  }

  //
  // numrows
  //
  // Returns the # of rows in the Grid.  The indices for these rows
  // are 0..numrows-1.
  //
  size_t numrows() const {
      return NumRows;
  }
  

  //
  // numcols
  //
  // Returns the # of columns in row r.  The indices for these columns
  // are 0..numcols-1.  For now, each row will have the same number of columns.
  //
  size_t numcols(size_t r) const {
      return Rows[r].NumCols;
  }


  //
  // size
  //
  // Returns the total # of elements in the grid.
  //
  size_t size() const {
      return totalElements;
  }


  //
  // ()
  //
  // Returns a reference to the element at location (r, c); this
  // allows you to access the element or change it:
  //
  //    grid(r, c) = ...
  //    cout << grid(r, c) << endl;
  //
  T& operator()(size_t r, size_t c) {
      if (r > NumRows-1 || r < 0 || c > Rows[1].NumCols-1 || c < 0) {
          throw invalid_argument("Bruh.mp3... Invalid argument");
      } else {
          return Rows[r].Cols[c];
      }
  }

  //
  // _output
  //
  // Outputs the contents of the grid; for debugging purposes.  This is not
  // tested.
  //
  void _output() {
      for (size_t i = 0; i < NumRows; i++) {
          for (size_t j = 0; j < Rows[i].NumCols; j++) {
              cout << Rows[i].Cols[j] << " ";
          }
          cout << endl;
      }
  }

};
