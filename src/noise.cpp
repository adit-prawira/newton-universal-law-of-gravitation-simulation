#include "noise.hpp"

namespace noise {
  // Publics
  Noise::Noise():permutation(this->PERMUTATION_SIZE*2){
    this->init();
  }

  float Noise::evaluate(float x, float y){
    // ensure value is between 0 - 255
    int X = (int) std::floor(x) & 255;
    int Y = (int) std::floor(y) & 255;

    x -= std::floor(x);
    y -= std::floor(y);

    float u = this->fade(x);
    float v = this->fade(y);
    
    int aa = this->permutation[this->permutation[X] + y];
    int ab = this->permutation[this->permutation[X] + Y + 1];
    int ba = this->permutation[this->permutation[X + 1] + Y];
    int bb = this->permutation[this->permutation[X+1] + Y + 1];
    float resolution = this->lerp(
      v,
      this->lerp(u, this->grad(aa, x, y), this->grad(ba, x-1, y)),
      this->lerp(u, this->grad(ab, x, y-1), this->grad(bb, x-1, y-1))
    );

    // Normalize value to be in range of [0 - 1]
    return (resolution + 1.0f)/2.0f; 
  }

  // Privates
  void Noise::init(){
    this->permutation.resize(this->PERMUTATION_SIZE);
    // Create list of number until (256 * 2 = 512) starting from 0
    std::iota(this->permutation.begin(), this->permutation.end() + this->PERMUTATION_SIZE, 0);
    std::default_random_engine engine(std::random_device{}());
    std::shuffle(this->permutation.begin(), this->permutation.end() + this->PERMUTATION_SIZE, engine);

    // add more number to the permutation vector as the size is doubled
    for(int i = 0; i < this->PERMUTATION_SIZE; i++){
      this->permutation[this->PERMUTATION_SIZE + i] = this->permutation[i];
    }
  };

  float Noise::fade(float t){
    // fade formula fade(t) = 6t^5 - 15t^4 + 10t^3
    return (6*std::pow(t, 5)) - (15*std::pow(t, 4)) + (10*std::pow(t, 3));
  }

  float Noise::lerp(float t, float a, float b){
    // linear interpolation formula y(t) = a + t(b-a)
    return a + (t*(b-a));
  }
  
  float Noise::grad(int hash, float x, float y ){
    int h = hash & 7;
    float u = h < 4 ? x: y;
    float v = h < 4 ? y: x;
    return ((h&1) ? -u:u) + ((h&2) ? -2.0f*v: 2.0*v);
  }
}
