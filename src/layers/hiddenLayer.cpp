#include "hiddenLayer.hpp"


HiddenLayer::HiddenLayer(const size_t &neuronQuantity, const bool& hasBias):
  Layer(neuronQuantity),
  bias_(nullptr)
{
  if (hasBias){
    bias_ = std::make_shared<Neuron>();
    bias_->setInput(1);
    bias_->setOutput(1);
  }
}

bool HiddenLayer::hasBias() const
{
  return static_cast<bool>(bias_.get());
}

std::shared_ptr<Neuron> HiddenLayer::getBias() const
{
  return bias_;
}

void HiddenLayer::setWeights(const std::shared_ptr<Layer> &nextLayer)
{
  Layer::setWeights(nextLayer);
  if (hasBias()){
    bias_->setWeights(nextLayer->getNeuronQuantity());
  }
}

void HiddenLayer::changeWeights(const double& learningRate, const double& momentum, const std::shared_ptr<Layer>& nextLayer)
{
  std::vector<double> nextLayerWeightDelta = {};

  for (size_t i = 0; i < getNeuronQuantity(); i++){
    nextLayerWeightDelta = {};
    for (size_t j = 0; j < nextLayer->getNeuronQuantity(); j++){
      const double delta = (*nextLayer)[j]->getWeightDelta();
      nextLayerWeightDelta.push_back(delta);
    }

    neurons_.at(i)->setWeightDelta(neurons_.at(i)->countWeightDelta(nextLayerWeightDelta));
    neurons_.at(i)->changeWeights(learningRate, momentum, nextLayerWeightDelta);
  }
  if (hasBias()){
    getBias()->changeWeights(learningRate, momentum, nextLayerWeightDelta);
  }
}

double HiddenLayer::getTotalImpulse(const size_t &toNeuron) const
{
  double impulse = Layer::getTotalImpulse(toNeuron);
  if (hasBias()){
    impulse += getBias()->getWeight(toNeuron);
  }
  return impulse;
}

std::ostream& operator <<(std::ostream &out, const HiddenLayer &layer)
{
  out << "___________________\n"
      << "Hidden layer information:\n"
      << "\tNeuron quantity: " << layer.getNeuronQuantity() << ";\n";

  size_t j = 0;
  for (const std::shared_ptr<Neuron>& neuron: layer.neurons_){
    out << "\tNeuron №" << j++ << ": \n\t" << *neuron << "\n";
  }
  if (layer.hasBias()){
    out << "\tBias neuron: \n\t" << *layer.getBias();
  }
  out << "\n";
  return out;
}
