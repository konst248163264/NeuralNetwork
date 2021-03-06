

#ifndef COURSE_PROJECT_HIDDENLAYER_HPP
#define COURSE_PROJECT_HIDDENLAYER_HPP

#include "layer.hpp"
#include "../neuron/neuron.hpp"

class HiddenLayer: public Layer{
public:
  explicit HiddenLayer(const size_t& neuronQuantity, const bool& hasBias);

  friend std::ostream& operator<<(std::ostream& out, const HiddenLayer& layer);

  void setWeights(const std::shared_ptr<Layer> &nextLayer) override;

  double getTotalImpulse(const size_t &toNeuron) const override;

  bool hasBias() const override;
  std::shared_ptr<Neuron> getBias() const override;

  void changeWeights(const double& learningRate, const double& momentum, const std::shared_ptr<Layer>& nextLayer);

private:
  std::shared_ptr<Neuron> bias_;
};

std::ostream& operator<<(std::ostream& out, const HiddenLayer& layer);

#endif //COURSE_PROJECT_HIDDENLAYER_HPP
