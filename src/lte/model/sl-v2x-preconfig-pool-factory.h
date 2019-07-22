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

#ifndef SL_PRECONFIG_POOL_FACTORY_V2X_H
#define SL_PRECONFIG_POOL_FACTORY_V2X_H

#include "lte-rrc-sap.h"
#include "sl-v2x-resource-pool-factory.h"

namespace ns3 {

/** Class to generate preconfigured pool configuration */
class SlV2xPreconfigPoolFactory : public SlV2xResourcePoolFactory
{
public:
  SlV2xPreconfigPoolFactory ();

  /**
   * Generate a preconfigure V2X resource pool based on the factory configuration
   * \return a new preconfigured V2X resource pool
   */
  LteRrcSap::SlV2xPreconfigCommPool CreatePool(); 

private: 
  LteRrcSap::SlV2xPreconfigCommPool m_pool; 
}; 

} // namespace ns3

#endif
