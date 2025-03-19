#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>

//-----------------------------------------------------------------------------
//
// Representing measurements with errors.
//
//

// Type to represent an experimental measurement value.
class Measurement {
private:
    float value; // Measured value
    float error; // Associated erro
public:
    Measurement(const float &_value=0,const float &_error=0 ):error(_error), value(_value)  {}
    float getvalue()const{
      return value;
    }
    float geterror()const{
      return error;
    }
    /*void setvalue(float value){
        this->value=0;
    }
    void setvalue(float error){
        this->error=0
    }*/
//-----------------------------------------------------------------------------
// Arithmetic operations on measurements.
// Some two measurements. Evaluate error.
friend Measurement operator+(Measurement const &a, Measurement const &b);

// Subtract two measurements. Evaluate error.
friend Measurement operator-(Measurement const &a, Measurement const &b);

// Multiply two measurements. Evaluate error.
friend Measurement operator*(Measurement const &a, Measurement const &b);

// Multiply a constant with a measurement. Evaluate error.
friend Measurement operator*(float a, Measurement const &b);

// Divide two measurements. Evaluate error.
friend Measurement operator/(Measurement const &a, Measurement const &b);

// Divide a measurement by a constant. Evaluate error.
friend Measurement operator/(Measurement const &a, float b);
};
//-----------------------------------------------------------------------------
// Type to represent the time and positions of the particle. With errors.
//
struct ParticlePosition {
  Measurement time;   // Time
  Measurement height; // Associated height
};

//-----------------------------------------------------------------------------
//
// Auxiliary types and functions for the main function.
//

// Some useful type synonyms.
using Positions = std::vector<ParticlePosition>;
using Velocities = std::vector<Measurement>;

// Tells how to execute the code.
void usage(std::string exename);

// Reads data from filename.
Positions read_data(std::string filename);

// Computes the value of g given the time and height data.
Measurement compute_g(Positions data);

// Compute velocities in each instant given the data and
// already evaluated g.
Velocities compute_velocities(Positions data, Measurement g);

//-----------------------------------------------------------------------------
//
// main
int main(int argc, char const *argv[]) {
  // We need an argument with the name of the data file.
  if (argc != 2) {
    usage(argv[0]);
    std::exit(1);
  }

  auto data = read_data(argv[1]);

  auto g = compute_g(data);
  auto velocities = compute_velocities(data, g);

  std::cout << "Evaluated values follow.\n\n";
  std::cout << "Gravitational acceleration: " << g.getvalue() << " +- " << g.geterror()
            << std::endl;
  std::cout << "Velocities:\n";
  for (size_t i = 0; i < velocities.size(); ++i) {
    std::cout << velocities[i].getvalue() << " +- " << velocities[i].geterror()
              << std::endl;
  }

  return 0;
}

//-----------------------------------------------------------------------------
//
// Implementations of the functions auxiliary to main.
//

// Tells how to execute the code.
void usage(std::string exename) {
  std::cerr << "Usage: " << exename << " <data file name>\n";
}

// Reads data from filename.
// The data are in the format:
//
// <time> <time error> <height> <height error>.
//
// All are floating point numbers.
Positions read_data(std::string filename) {

  Positions data;

  std::ifstream datafile(filename);
  if (!datafile.good()) {
    std::cerr << "Error reading " << filename << std::endl;
    std::exit(2);
  }

  // Read a position (time+height with errors) value.
  float value, error;
  // Try to read until the end of the file.
  while (datafile >> value) {
    // If we find a value, there must be 3 more values.

    datafile >> error;
    if (datafile.fail()) {
      std::cerr << "Error reading data from " << filename << std::endl;
      std::exit(3);
    }

    Measurement time{value, error};

    datafile >> value;
    datafile >> error;
    if (datafile.fail()) {
      std::cerr << "Error reading data from " << filename << std::endl;
      std::exit(3);
    }

    Measurement height{value, error};

    data.push_back({time, height});
  }

  return data;
}

// Computes the value of g given the time and height data.
Measurement compute_g(Positions data) {
  // Uses the first, second and last positions and corresponding times,
  // and compute
  auto num_points = data.size();
  auto t0 = data[0].time;
  auto t1 = data[1].time;
  auto tn = data[num_points - 1].time;
  auto h0 = data[0].height;
  auto h1 = data[1].height;
  auto hn = data[num_points - 1].height;

  return 2.0f*((hn-h1)*t0-(hn-h0)*t1+(h1-h0)*tn)/((t1-t0)*(tn-t1)*(tn-t0));
}

// Compute velocities in each instant given the data and
// already evaluated g.
Velocities compute_velocities(Positions data, Measurement g) {
  auto const n_data = data.size();
  Velocities velocities(n_data);

  // For each data point (except the last, see below), evaluate the velocity as
  // the starting velocity for a free fall to reach the next point.
  for (size_t i = 0; i < n_data - 1; ++i) {
    //auto delta_h = subtract(data[i + 1].height, data[i].height);
    auto delta_h=data[i+1].height-data[i].height;
    //auto delta_t = subtract(data[i + 1].time, data[i].time);
    auto delta_t=data[i+1].time-data[i].time;

    velocities[i]=delta_h/delta_t + g*delta_t/2;
  }

  // The last velocity is evaluated from the one before last and the value of g.
  //auto last_delta_t = subtract(data[n_data - 1].time, data[n_data - 2].time);
  auto last_delta_t=data[n_data - 1].time-data[n_data - 2].time;
  //velocities[n_data - 1] =
      //subtract(velocities[n_data - 2], multiply(g, last_delta_t));
  velocities[n_data-1]=velocities[n_data-2]-g*last_delta_t;
  return velocities;
}

//-----------------------------------------------------------------------------
//
// Implementation of arithmetic operations on measurements with errors.
// The error propagation formulas assume that the error are Gaussian
// and independent (uncorrelated) in the two measurements.
//

inline float square(float x) { return x * x; }

Measurement operator+(Measurement const &a, Measurement const &b) {
  return {a.getvalue() + b.getvalue(), std::sqrt(square(a.geterror()) + square(b.geterror()))};
}

Measurement operator-(Measurement const &a, Measurement const &b) {
  return {a.getvalue() - b.getvalue(), std::sqrt(square(a.geterror()) + square(b.geterror()))};
}

Measurement operator*(Measurement const &a, Measurement const &b) {
  auto value = a.getvalue() * b.getvalue();
  return {value, std::fabs(value) * std::sqrt(square(a.geterror() / a.getvalue()) +
                                              square(b.geterror() / b.getvalue()))};
}

Measurement operator*(float a, Measurement const &b) {
  return {a * b.getvalue(), std::fabs(a) * b.geterror()};
}

Measurement operator/(Measurement const &a, Measurement const &b) {
  auto value = a.getvalue() / b.getvalue();
  return {value, std::fabs(value) * std::sqrt(square(a.geterror()/a.getvalue()) +
                                              square(b.geterror()/b.getvalue()))};
}

Measurement operator/(Measurement const &a, float b) {
  return {a.getvalue() / b, a.geterror() / std::fabs(b)};
}
