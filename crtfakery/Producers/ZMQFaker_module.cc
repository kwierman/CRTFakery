#include "crtfakery/Producers/ZMQFaker.hh"
#include "lardata/DetectorInfoServices/DetectorClocksService.h"
#include "fhiclcpp/ParameterSet.h"
#include "art/Framework/Principal/Event.h"
#include "art/Framework/Services/Registry/ServiceHandle.h"
#include "lardataobj/Simulation/AuxDetSimChannel.h"
#include "messagefacility/MessageLogger/MessageLogger.h"
#include "larcore/Geometry/AuxDetGeometry.h"

#include <vector>
#include <memory>
#include <sstream>
#include <string>
#include <math.h>

namespace fake{

  ZMQFaker::ZMQFaker(const fhicl::ParameterSet& pSet)
  {
    this->reconfigure(pSet);
    produces< std::vector<bernfebdaq::BernZMQFragment> >();
  }

  ZMQFaker::~ZMQFaker()
  {

  }

  void ZMQFaker::reconfigure(fhicl::ParameterSet const & pSet) {
    fProducerName = pSet.get<std::string>("ProducerName", "largeant");
  }

  void ZMQFaker::produce(art::Event& evt)
  {
    std::unique_ptr<OutputFragments > fragments(
        new OutputFragments);

    art::ServiceHandle<geo::AuxDetGeometry> geoService;

    art::ServiceHandle<detinfo::DetectorClocksService> detClocks;

    detinfo::ElecClock trigClock = detClocks->provider()->TriggerClock();

    art::ServiceHandle<art::RandomNumberGenerator> rng;
    CLHEP::HepRandomEngine* engine = &rng->getEngine("crt");

    // Handle for (truth) AuxDetSimChannels
    art::Handle<std::vector<sim::AuxDetSimChannel> > channels;
    evt.getByLabel(fProducerName, channels);

    // I hate that you people made me do this.
    const geo::AuxDetGeometry* geometry = &*geoService;
    const geo::AuxDetGeometryCore* geoServiceProvider = geometry->GetProviderPtr();

    evt.put(std::move(crtHits));
  }

  DEFINE_ART_MODULE(ZMQFaker)
}

