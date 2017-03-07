#ifndef BERN_ZMQ_DATA_HH
#define BERN_ZMQ_DATA_HH


namespace fake{

  class BernZMQData : art::CommandableFragmentGenerator
  {
  protected:
    bool getNext_(artdaq::FragmentPtrs& output) override;
    void start() override;
    void stop() override;
    void stopNoMutex() override;
  public:
    BernZMQData(fhicl::ParameterSet const& );
    ~BernZMQData();
  };
}


#endif // BERN_ZMQ_DATA_HH
