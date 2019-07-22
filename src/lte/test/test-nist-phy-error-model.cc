/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * This software was developed at the National Institute of Standards and
 * Technology by employees of the Federal Government in the course of
 * their official duties. Pursuant to titleElement 17 Section 105 of the United
 * States Code this software is not subject to copyright protection and
 * is in the public domain.
 * NIST assumes no responsibility whatsoever for its use by other parties,
 * and makes no guarantees, expressed or implied, about its quality,
 * reliability, or any other characteristic.

 * We would appreciate acknowledgement if the software is used.

 * NIST ALLOWS FREE USE OF THIS SOFTWARE IN ITS "AS IS" CONDITION AND
 * DISCLAIM ANY LIABILITY OF ANY KIND FOR ANY DAMAGES WHATSOEVER RESULTING
 * FROM THE USE OF THIS SOFTWARE.
 *
 * Modified by: NIST
 */

#include <ns3/log.h>
#include <ns3/test.h>
#include <ns3/double.h>
#include <ns3/lte-phy-error-model.h>
#include <ns3/lte-harq-phy.h>
#include <ns3/simulator.h>
#include <ns3/math.h>
#include <cmath>
#include <string>
#include <iostream>
#include <sstream>


NS_LOG_COMPONENT_DEFINE ("TestNistPhyErrorModel");

using namespace ns3;

enum PhyErrorModelTestCondition  {
  EQUAL = 0
};

class LtePhyErrorModelTestCase : public TestCase
{
public:
  static std::string BuildNameString (LtePhyErrorModel::LtePhyChannel channel, LtePhyErrorModel::LteFadingModel fadingChannel, LtePhyErrorModel::LteTxMode txmode, uint16_t mcs, double newSinr, HarqProcessInfoList_t harqHistory);
  LtePhyErrorModelTestCase (LtePhyErrorModel::LtePhyChannel channel, LtePhyErrorModel::LteFadingModel fadingChannel, LtePhyErrorModel::LteTxMode txmode, uint16_t mcs, double newSinr, HarqProcessInfoList_t harqHistory, double expectedBler, PhyErrorModelTestCondition cond);


private:
  virtual void DoRun (void);

  LtePhyErrorModel::LtePhyChannel m_channel;
  LtePhyErrorModel::LteFadingModel m_fadingChannel;
  LtePhyErrorModel::LteTxMode m_txmode;
  uint16_t m_mcs;
  double m_newSinr; 
  HarqProcessInfoList_t m_harqHistory;
  double m_expectedBler;
  PhyErrorModelTestCondition m_cond;
};

std::string LtePhyErrorModelTestCase::BuildNameString (LtePhyErrorModel::LtePhyChannel channel, LtePhyErrorModel::LteFadingModel fadingChannel, LtePhyErrorModel::LteTxMode txmode, uint16_t mcs, double newSinr, HarqProcessInfoList_t harqHistory)
{
  std::ostringstream oss;
  
  switch (channel)
    {
    case LtePhyErrorModel::PSCCH:
      oss << "PSCCH";
      break;
    case LtePhyErrorModel::PSSCH:
      oss << "PSSCH";
      break;
    case LtePhyErrorModel::PSDCH:
      oss << "PSDCH";
      break;
    case LtePhyErrorModel::PUSCH:
      oss << "PUSCH";
      break;
    default:
      oss << "OTHER channel";
      break;
    }
  oss << ", ";

  switch (fadingChannel)
    {
    case LtePhyErrorModel::AWGN:
      oss << "AWGN";
      break;
    default:
      oss << "Other";
      break;
    }
  oss << ", tx mode=" << txmode
      << ", mcs=" << mcs
      << ", newSinr=" << newSinr << " W (" << 10 * std::log10 (newSinr) << " dB)" 
      << ", harqHistory size=" << harqHistory.size();
  if (harqHistory.size() >0)
    {
      oss << ", last HarqSinr" <<  harqHistory[harqHistory.size()-1].m_sinr << " W (" << 10 * std::log10 (harqHistory[harqHistory.size()-1].m_sinr) << " dB)";
    }
  
  return oss.str ();
}


LtePhyErrorModelTestCase::LtePhyErrorModelTestCase (LtePhyErrorModel::LtePhyChannel channel, LtePhyErrorModel::LteFadingModel fadingChannel, LtePhyErrorModel::LteTxMode txmode, uint16_t mcs, double newSinr, HarqProcessInfoList_t harqHistory, double expectedBler, PhyErrorModelTestCondition cond)
  : TestCase (BuildNameString (channel, fadingChannel, txmode, mcs, newSinr, harqHistory)),
    m_channel (channel),
    m_fadingChannel (fadingChannel),
    m_txmode (txmode),
    m_mcs (mcs),
    m_newSinr (newSinr),
    m_harqHistory (harqHistory),
    m_expectedBler (expectedBler),
    m_cond (cond)
{
}

void
LtePhyErrorModelTestCase::DoRun ()
{
  NS_LOG_FUNCTION (this << BuildNameString (m_channel, m_fadingChannel, m_txmode, m_mcs, m_newSinr, m_harqHistory));

  TbErrorStats_t tbStat;
  
  switch (m_channel)
    {
    case LtePhyErrorModel::PSCCH:
      tbStat = LtePhyErrorModel::GetPscchBler (m_fadingChannel, m_txmode, m_newSinr);
      break;
    case LtePhyErrorModel::PSSCH:
      tbStat = LtePhyErrorModel::GetPsschBler (m_fadingChannel, m_txmode, m_mcs, m_newSinr, m_harqHistory);
      break;
    case LtePhyErrorModel::PSDCH:
      tbStat = LtePhyErrorModel::GetPsdchBler (m_fadingChannel, m_txmode, m_newSinr, m_harqHistory);
      break;
    case LtePhyErrorModel::PUSCH:
      tbStat = LtePhyErrorModel::GetPuschBler (m_fadingChannel, m_txmode, m_mcs, m_newSinr, m_harqHistory);
      break;
    default:
      tbStat.tbler = -1; //put invalid value to make sure the test fails
      break;
    }
  switch (m_cond) 
    {
    case EQUAL:
      NS_TEST_EXPECT_MSG_EQ_TOL (tbStat.tbler, m_expectedBler, 0.001, "wrong value of the bler");
      break;
    default:
      break;
    }
}




class LtePhyErrorModelTestSuite : public TestSuite
{
public:
  LtePhyErrorModelTestSuite ();
};

LtePhyErrorModelTestSuite::LtePhyErrorModelTestSuite ()
  : TestSuite ("phy-error-model", UNIT)
{ 

  LogComponentEnable("LtePhyErrorModel", LOG_LEVEL_ALL);
  LogComponentEnable("TestNistPhyErrorModel", LOG_LEVEL_ALL);

  HarqProcessInfoList_t harqInfoList;

  //Tests with no HARQ history
  //tests not requiring interpolation
  AddTestCase (new LtePhyErrorModelTestCase (LtePhyErrorModel::PSSCH, LtePhyErrorModel::AWGN, LtePhyErrorModel::SISO, 10, std::pow (10, (-1 / 10.0)),  harqInfoList, 1,    EQUAL), TestCase::QUICK);
  AddTestCase (new LtePhyErrorModelTestCase (LtePhyErrorModel::PSSCH, LtePhyErrorModel::AWGN, LtePhyErrorModel::SISO, 10, std::pow (10, (2 / 10.0)),  harqInfoList, 0.968,    EQUAL), TestCase::QUICK);
  AddTestCase (new LtePhyErrorModelTestCase (LtePhyErrorModel::PSSCH, LtePhyErrorModel::AWGN, LtePhyErrorModel::SISO, 10, std::pow (10, (3.2 / 10.0)),  harqInfoList, 0.048,    EQUAL), TestCase::QUICK);

  //tests with interpolation
  AddTestCase (new LtePhyErrorModelTestCase (LtePhyErrorModel::PSSCH, LtePhyErrorModel::AWGN, LtePhyErrorModel::SISO, 10, std::pow (10, (2.5 / 10.0)),  harqInfoList, 0.657,    EQUAL), TestCase::QUICK);

  //Tests with 1 HARQ history
  HarqProcessInfoElement_t el;
  el.m_sinr = std::pow (10, (-2 / 10.0));
  harqInfoList.push_back (el);
  //if SINR does not change, there is no interpolation
  AddTestCase (new LtePhyErrorModelTestCase (LtePhyErrorModel::PSSCH, LtePhyErrorModel::AWGN, LtePhyErrorModel::SISO, 10, std::pow (10, (-2 / 10.0)),  harqInfoList, 0.96,    EQUAL), TestCase::QUICK);
  //if SINR does not change, there is no interpolation
  AddTestCase (new LtePhyErrorModelTestCase (LtePhyErrorModel::PSSCH, LtePhyErrorModel::AWGN, LtePhyErrorModel::SISO, 10, std::pow (10, (-1 / 10.0)),  harqInfoList, 0.463,    EQUAL), TestCase::QUICK);
  
  harqInfoList.erase (harqInfoList.begin());
  el.m_sinr = std::pow (10, (-1 / 10.0));
  harqInfoList.push_back (el);
  AddTestCase (new LtePhyErrorModelTestCase (LtePhyErrorModel::PSSCH, LtePhyErrorModel::AWGN, LtePhyErrorModel::SISO, 10, std::pow (10, (-2 / 10.0)),  harqInfoList, 0.565,    EQUAL), TestCase::QUICK);

  harqInfoList.erase (harqInfoList.begin());
  el.m_sinr = std::pow (10, (-4 / 10.0));
  harqInfoList.push_back (el);  
  AddTestCase (new LtePhyErrorModelTestCase (LtePhyErrorModel::PSSCH, LtePhyErrorModel::AWGN, LtePhyErrorModel::SISO, 10, std::pow (10, (-3 / 10.0)),  harqInfoList, 1,    EQUAL), TestCase::QUICK);


  //Testing PSCCH
  harqInfoList.erase (harqInfoList.begin());
  AddTestCase (new LtePhyErrorModelTestCase (LtePhyErrorModel::PSCCH, LtePhyErrorModel::AWGN, LtePhyErrorModel::SISO, 0, std::pow (10, (-7 / 10.0)),  harqInfoList, 1,    EQUAL), TestCase::QUICK);

  AddTestCase (new LtePhyErrorModelTestCase (LtePhyErrorModel::PSCCH, LtePhyErrorModel::AWGN, LtePhyErrorModel::SISO, 0, std::pow (10, (2 / 10.0)),  harqInfoList, 0,    EQUAL), TestCase::QUICK);

};

static LtePhyErrorModelTestSuite staticLtePhyErrorModelTestSuiteInstance;
