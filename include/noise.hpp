#include <cmath>
#include <random>
#include <vector>

namespace noise {
class Noise {
  public:
    Noise();
    float evaluate(float x, float y);

  private:
    const int PERMUTATION_SIZE = 256;
    std::vector<int> permutation;

    float fade(float t);
    
    // Linear interpolation
    float lerp(float t, float a, float b);

    // Gradient
    float grad(int hash, float x, float y);
    void init();
  };
} // namespace noise
