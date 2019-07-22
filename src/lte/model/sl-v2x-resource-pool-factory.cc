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
 *              Fabian Eckermann <fabian.eckermann@udo.edu> (CNI)
 *              Moritz Kahlert <moritz.kahlert@udo.edu> (CNI)
 */

#include "sl-v2x-resource-pool-factory.h"
#include "ns3/log.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("SlV2xResourcePoolFactory");

SlV2xResourcePoolFactory::SlV2xResourcePoolFactory () :
  m_dataAlpha(0.9),
  m_dataP0(-4),
  m_slSubframe(std::bitset<20>(0xFFFFF)),
  m_adjacencyPscchPssch(true),
  m_sizeSubchannel(10),
  m_numSubchannel(5),
  m_startRbSubchannel(0),
  m_startRbPscchPool(0)
{
  NS_LOG_FUNCTION (this);
}

LteRrcSap::SlCommResourcePoolV2x
SlV2xResourcePoolFactory::CreatePool () 
{
  /*m_pool.slSubframeV2x.bitmap = std::bitset<20>(m_slSubframe); 

  m_pool.adjacencyPscchPssch.adjacency = m_adjacencyPscchPssch; 

  if (m_sizeSubchannel == "n4" && m_adjacencyPscchPssch == false){m_pool.sizeSubchannel.size = LteRrcSap::SizeSubchannel::n4;}
  else if (m_sizeSubchannel == "n5"){m_pool.sizeSubchannel.size = LteRrcSap::SizeSubchannel::n5;}
  else if (m_sizeSubchannel == "n6"){m_pool.sizeSubchannel.size = LteRrcSap::SizeSubchannel::n6;}
  else if (m_sizeSubchannel == "n8" && m_adjacencyPscchPssch == false){m_pool.sizeSubchannel.size = LteRrcSap::SizeSubchannel::n8;}
  else if (m_sizeSubchannel == "n9" && m_adjacencyPscchPssch == false){m_pool.sizeSubchannel.size = LteRrcSap::SizeSubchannel::n9;}
  else if (m_sizeSubchannel == "n10"){m_pool.sizeSubchannel.size = LteRrcSap::SizeSubchannel::n10;}
  else if (m_sizeSubchannel == "n12" && m_adjacencyPscchPssch == false){m_pool.sizeSubchannel.size = LteRrcSap::SizeSubchannel::n12;}
  else if (m_sizeSubchannel == "n15"){m_pool.sizeSubchannel.size = LteRrcSap::SizeSubchannel::n15;}
  else if (m_sizeSubchannel == "n16" && m_adjacencyPscchPssch == false){m_pool.sizeSubchannel.size = LteRrcSap::SizeSubchannel::n16;}
  else if (m_sizeSubchannel == "n18" && m_adjacencyPscchPssch == false){m_pool.sizeSubchannel.size = LteRrcSap::SizeSubchannel::n18;}
  else if (m_sizeSubchannel == "n20"){m_pool.sizeSubchannel.size = LteRrcSap::SizeSubchannel::n20;}
  else if (m_sizeSubchannel == "n25" && m_adjacencyPscchPssch == true){m_pool.sizeSubchannel.size = LteRrcSap::SizeSubchannel::n25;}
  else if (m_sizeSubchannel == "n30" && m_adjacencyPscchPssch == false){m_pool.sizeSubchannel.size = LteRrcSap::SizeSubchannel::n30;}
  else if (m_sizeSubchannel == "n48" && m_adjacencyPscchPssch == false){m_pool.sizeSubchannel.size = LteRrcSap::SizeSubchannel::n48;}
  else if (m_sizeSubchannel == "n50" && m_adjacencyPscchPssch == true){m_pool.sizeSubchannel.size = LteRrcSap::SizeSubchannel::n50;}
  else if (m_sizeSubchannel == "n72" && m_adjacencyPscchPssch == false){m_pool.sizeSubchannel.size = LteRrcSap::SizeSubchannel::n72;}
  else if (m_sizeSubchannel == "n75" && m_adjacencyPscchPssch == true){m_pool.sizeSubchannel.size = LteRrcSap::SizeSubchannel::n75;}
  else if (m_sizeSubchannel == "n96" && m_adjacencyPscchPssch == false){m_pool.sizeSubchannel.size = LteRrcSap::SizeSubchannel::n96;}  
  else if (m_sizeSubchannel == "n100" && m_adjacencyPscchPssch == true){m_pool.sizeSubchannel.size = LteRrcSap::SizeSubchannel::n100;}
  else if (m_sizeSubchannel == "spare13"){m_pool.sizeSubchannel.size = LteRrcSap::SizeSubchannel::spare13;}
  else if (m_sizeSubchannel == "spare12"){m_pool.sizeSubchannel.size = LteRrcSap::SizeSubchannel::spare12;}
  else if (m_sizeSubchannel == "spare11"){m_pool.sizeSubchannel.size = LteRrcSap::SizeSubchannel::spare11;}
  else if (m_sizeSubchannel == "spare10"){m_pool.sizeSubchannel.size = LteRrcSap::SizeSubchannel::spare10;}
  else if (m_sizeSubchannel == "spare9"){m_pool.sizeSubchannel.size = LteRrcSap::SizeSubchannel::spare9;}
  else if (m_sizeSubchannel == "spare8"){m_pool.sizeSubchannel.size = LteRrcSap::SizeSubchannel::spare8;}
  else if (m_sizeSubchannel == "spare7"){m_pool.sizeSubchannel.size = LteRrcSap::SizeSubchannel::spare7;}
  else if (m_sizeSubchannel == "spare6"){m_pool.sizeSubchannel.size = LteRrcSap::SizeSubchannel::spare6;}
  else if (m_sizeSubchannel == "spare5"){m_pool.sizeSubchannel.size = LteRrcSap::SizeSubchannel::spare5;}
  else if (m_sizeSubchannel == "spare4"){m_pool.sizeSubchannel.size = LteRrcSap::SizeSubchannel::spare4;}
  else if (m_sizeSubchannel == "spare3"){m_pool.sizeSubchannel.size = LteRrcSap::SizeSubchannel::spare3;}
  else if (m_sizeSubchannel == "spare2"){m_pool.sizeSubchannel.size = LteRrcSap::SizeSubchannel::spare2;}
  else if (m_sizeSubchannel == "spare1"){m_pool.sizeSubchannel.size = LteRrcSap::SizeSubchannel::spare1;}
  else {NS_FATAL_ERROR ("UNSUPPORTED SUBCHANNEL SIZE");}

  if (m_numSubchannel == "n1"){m_pool.numSubchannel.num = LteRrcSap::NumSubchannel::n1;}
  else if (m_numSubchannel == "n3"){m_pool.numSubchannel.num = LteRrcSap::NumSubchannel::n3;}
  else if (m_numSubchannel == "n5"){m_pool.numSubchannel.num = LteRrcSap::NumSubchannel::n5;}
  else if (m_numSubchannel == "n8"){m_pool.numSubchannel.num = LteRrcSap::NumSubchannel::n8;}
  else if (m_numSubchannel == "n10"){m_pool.numSubchannel.num = LteRrcSap::NumSubchannel::n10;}
  else if (m_numSubchannel == "n15"){m_pool.numSubchannel.num = LteRrcSap::NumSubchannel::n15;}
  else if (m_numSubchannel == "n20"){m_pool.numSubchannel.num = LteRrcSap::NumSubchannel::n20;}
  else if (m_numSubchannel == "spare1"){m_pool.numSubchannel.num = LteRrcSap::NumSubchannel::spare1;}
  else {NS_FATAL_ERROR ("UNSUPPORTED SUBCHANNEL NUMBER");}

  m_pool.startRbSubchannel.startRb = m_startRbSubchannel; 

  if (m_dataAlpha == "al0") {m_pool.dataTxParameters.alpha = LteRrcSap::SlTxParameters::al0;}
  else if (m_dataAlpha == "al04") {m_pool.dataTxParameters.alpha = LteRrcSap::SlTxParameters::al04;}
  else if (m_dataAlpha == "al05") {m_pool.dataTxParameters.alpha = LteRrcSap::SlTxParameters::al05;}
  else if (m_dataAlpha == "al06") {m_pool.dataTxParameters.alpha = LteRrcSap::SlTxParameters::al06;}
  else if (m_dataAlpha == "al07") {m_pool.dataTxParameters.alpha = LteRrcSap::SlTxParameters::al07;}
  else if (m_dataAlpha == "al08") {m_pool.dataTxParameters.alpha = LteRrcSap::SlTxParameters::al08;}
  else if (m_dataAlpha == "al09") {m_pool.dataTxParameters.alpha = LteRrcSap::SlTxParameters::al09;}
  else if (m_dataAlpha == "al1") {m_pool.dataTxParameters.alpha = LteRrcSap::SlTxParameters::al1;}
  else {NS_FATAL_ERROR ("UNSUPPORTED DATA TX ALPHA");}
  m_pool.dataTxParameters.p0 = m_dataP0;

  m_pool.startRbPscchPool.startRb = m_startRbPscchPool;  */
  
  return m_pool; 
}

// UE Selected Parameters
void
SlV2xResourcePoolFactory::SetHaveUeSelectedResourceConfig (bool ueSelected)
{
  NS_LOG_FUNCTION (this << ueSelected);
  m_ueSelected = ueSelected;
}

void
SlV2xResourcePoolFactory::SetDataTxAlpha (double alpha)
{
  NS_LOG_FUNCTION (this << alpha);
  m_dataAlpha = alpha;
}

void
SlV2xResourcePoolFactory::SetDataTxP0 (int16_t p0)
{
  NS_LOG_FUNCTION (this << p0);
  m_dataP0 = p0;
}

// V2X Parameter
void
SlV2xResourcePoolFactory::SetSlSubframe(std::bitset<20> slSubframe)
{
  NS_LOG_FUNCTION (this << slSubframe);
  m_slSubframe = slSubframe; 
}

void 
SlV2xResourcePoolFactory::SetAdjacencyPscchPssch(bool adjacencyPscchPssch)
{
  NS_LOG_FUNCTION(this << adjacencyPscchPssch);
  m_adjacencyPscchPssch = adjacencyPscchPssch;
}

void
SlV2xResourcePoolFactory::SetSizeSubchannel(uint16_t sizeSubchannel)
{
  NS_LOG_FUNCTION (this << sizeSubchannel);
  m_sizeSubchannel = sizeSubchannel;
}

void
SlV2xResourcePoolFactory::SetNumSubchannel(uint16_t numSubchannel)
{
  NS_LOG_FUNCTION(this << numSubchannel);
  m_numSubchannel = numSubchannel;
}

void
SlV2xResourcePoolFactory::SetStartRbSubchannel(uint16_t startRbSubchannel)
{
  NS_LOG_FUNCTION(this << startRbSubchannel);
  m_startRbSubchannel = startRbSubchannel;
}

void
SlV2xResourcePoolFactory::SetStartRbPscchPool(uint16_t startRbPscchPool)
{
  NS_LOG_FUNCTION(this << startRbPscchPool);
  m_startRbPscchPool = startRbPscchPool;
}

} // namespace ns3
