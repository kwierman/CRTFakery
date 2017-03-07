#ifndef ZMQ_FAKER_HH
#define ZMQ_FAKER_HH

#include "art/Framework/Core/ModuleMacros.h"
#include "art/Framework/Core/EDProducer.h"

#include <string>
#include <vector>

namespace art{
  class Event;
}

namespace fhicl{
  class ParameterSet;
}

namespace bernfebdaq{
  class BernZMQFragment;
}

namespace fake{


  class ZMQFaker : public art::EDProducer{
      std::string fProducerName;

      typedef std::vector<BernZMQFragment> OutputFragments;
  public:
    ZMQFaker(const fhicl::ParameterSet&);
    virtual void produce(art::Event&);
    void reconfigure(fhicl::ParameterSet const&) override;
  };

}


#endif // ZMQ_FAKER_HH
