#ifndef COURSE_PROJECT_XORTRAIN_HPP
#define COURSE_PROJECT_XORTRAIN_HPP

#include "training.hpp"

#include <memory>
#include <vector>

class NeuralNetwork;

class XORTraining: public Training{
public:
  XORTraining(const std::shared_ptr<NeuralNetwork> &neuralNetwork,
              const double &learningRate,
              const double &momentum);

  void trainSet(const double &minError) override;
  void trainSet() override;
};

#endif
