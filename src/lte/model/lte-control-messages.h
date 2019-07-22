/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2010 TELEMATICS LAB, DEE - Politecnico di Bari
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author: Giuseppe Piro  <g.piro@poliba.it>
 * Author: Marco Miozzo <marco.miozzo@cttc.es>
 * Modified by: NIST (D2D)
 *              Fabian Eckermann <fabian.eckermann@udo.edu> (CNI)
 *              Moritz Kahlert <moritz.kahlert@udo.edu> (CNI)
 */

#ifndef LTE_CONTROL_MESSAGES_H
#define LTE_CONTROL_MESSAGES_H

#include <ns3/ptr.h>
#include <ns3/simple-ref-count.h>
#include <ns3/ff-mac-common.h>
#include <ns3/lte-rrc-sap.h>
#include <list>

namespace ns3 {

class LteNetDevice;


/**
 * \ingroup lte
 *
 * The LteControlMessage provides a basic implementations for
 * control messages (such as PDCCH allocation map, CQI feedbacks)
 * that are exchanged among eNodeB and UEs.
 */
class LteControlMessage : public SimpleRefCount<LteControlMessage>
{
public:
  /**
   * The type of the message
   * NOTE: The messages sent by UE are filtered by the
   *  LteEnbPhy::ReceiveLteControlMessageList in order to remove the ones 
   *  that has been already handoff by the eNB for avoiding propagation of
   *  spurious messages. When new messaged have to been added, consider to
   *  update the switch statement implementing the filtering.
   */
  enum MessageType
  {
    DL_DCI, UL_DCI, // Downlink/Uplink Data Control Indicator
    DL_CQI, UL_CQI, // Downlink/Uplink Channel Quality Indicator
    BSR, // Buffer Status Report, including sidelink bsr
    DL_HARQ, // UL HARQ feedback
    RACH_PREAMBLE, // Random Access Preamble
    RAR, // Random Access Response
    MIB, // Master Information Block
    SIB1, // System Information Block Type 1
    SL_DCI, SCI, //Sidelink Data Control Indicator (DCI-5) and Sidelink Control Information (SCI-0)
    SL_DCI_V2X, SCI_V2X, // Sidelink Data Control Indicator (DCI-5A) and Sidelink Control Information (SCI-1)
    MIB_SL, // Master Information Block Sidelink
    SL_DISC_MSG // sidelink dicovery message
  };

  LteControlMessage (void);
  virtual ~LteControlMessage (void);

  /**
   * \brief Set the type of the message
   * \param type the type of the message
   */
  void SetMessageType (MessageType type);
  /**
   * \brief Get the type of the message
   * \return the type of the message
   */
  MessageType GetMessageType (void);

private:
  MessageType m_type; ///< message type
};


// -----------------------------------------------------------------------

/**
 * \ingroup lte
 * The Downlink Data Control Indicator messages defines the RB allocation for the
 * users in the downlink
 */
class DlDciLteControlMessage : public LteControlMessage
{
public:
  DlDciLteControlMessage (void);
  virtual ~DlDciLteControlMessage (void);

  /**
  * \brief add a DCI into the message
  * \param dci the dci
  */
  void SetDci (DlDciListElement_s dci);

  /**
  * \brief Get dic information
  * \return dci messages
  */
  DlDciListElement_s GetDci (void);

private:
  DlDciListElement_s m_dci; ///< DCI
};


// ---------------------------------------------------------------------------

/**
 * \ingroup lte
 * The Uplink Data Control Indicator messages defines the RB allocation for the
 * users in the uplink
 */
class UlDciLteControlMessage : public LteControlMessage
{
public:
  UlDciLteControlMessage (void);
  virtual ~UlDciLteControlMessage (void);

  /**
  * \brief add a DCI into the message
  * \param dci the dci
  */
  void SetDci (UlDciListElement_s dci);

  /**
  * \brief Get dic information
  * \return dci messages
  */
  UlDciListElement_s GetDci (void);

private:
  UlDciListElement_s m_dci; ///< DCI
};

// ---------------------------------------------------------------------------

/**
 * \ingroup lte
 * The Sidelink Data Control Indicator messages defines the RB allocation for the
 * users in the sidelink
 */
class SlDciLteControlMessage : public LteControlMessage
{
public:
  SlDciLteControlMessage (void);
  virtual ~SlDciLteControlMessage (void);

  /**
  * \brief add a DCI into the message
  * \param dci the dci
  */
  void SetDci (SlDciListElement_s dci);

  /**
  * \brief Get dic informations
  * \return dci messages
  */
  SlDciListElement_s GetDci (void);

private:
  SlDciListElement_s m_dci;
};

// ---------------------------------------------------------------------------

/**
 * \ingroup lte
 * The Sidelink Data Control Indicator messages defines the RB allocation for the
 * users in the sidelink
 */
class SlDciLteControlMessageV2x : public LteControlMessage
{
public:
  SlDciLteControlMessageV2x (void);
  virtual ~SlDciLteControlMessageV2x (void);


  /**
  * \brief add a DCIV2x into the message
  * \param dci the dci
  */
  void SetDci (SlDciListElementV2x dci);

  /**
  * \brief Get dciV2X informations
  * \return dciV2X messages
  */
  SlDciListElementV2x GetDci (void);

private:
  SlDciListElementV2x m_dci; 
};


// ---------------------------------------------------------------------------

/**
 * \ingroup lte
 * The downlink CqiLteControlMessage defines an ideal list of
 * feedback about the channel quality sent by the UE to the eNodeB.
 */
class DlCqiLteControlMessage : public LteControlMessage
{
public:
  DlCqiLteControlMessage (void);
  virtual ~DlCqiLteControlMessage (void);

  /**
  * \brief add a DL-CQI feedback record into the message.
  * \param dlcqi the DL cqi feedback
  */
  void SetDlCqi (CqiListElement_s dlcqi);

  /**
  * \brief Get DL cqi information
  * \return dlcqi messages
  */
  CqiListElement_s GetDlCqi (void);

private:
  CqiListElement_s m_dlCqi; ///< DL CQI
};


// ---------------------------------------------------------------------------

/**
 * \ingroup lte
 * The uplink BsrLteControlMessage defines the specific
 * extension of the CE element for reporting the buffer status report
 */
class BsrLteControlMessage : public LteControlMessage
{
public:
  BsrLteControlMessage (void);
  virtual ~BsrLteControlMessage (void);

  /**
  * \brief add a BSR feedback record into the message.
  * \param bsr the BSR feedback
  */
  void SetBsr (MacCeListElement_s bsr);

  /**
  * \brief Get BSR information
  * \return BSR message
  */
  MacCeListElement_s GetBsr (void);

private:
  MacCeListElement_s m_bsr; ///< BSR

};


// ---------------------------------------------------------------------------

/**
 * \ingroup lte
 * The downlink DlHarqFeedbackLteControlMessage defines the specific
 * messages for transmitting the DL HARQ feedback through PUCCH
 */
class DlHarqFeedbackLteControlMessage : public LteControlMessage
{
public:
  DlHarqFeedbackLteControlMessage (void);
  virtual ~DlHarqFeedbackLteControlMessage (void);

  /**
  * \brief add a DL HARQ feedback record into the message.
  * \param m the DL HARQ feedback
  */
  void SetDlHarqFeedback (DlInfoListElement_s m);

  /**
  * \brief Get DL HARQ information
  * \return DL HARQ message
  */
  DlInfoListElement_s GetDlHarqFeedback (void);

private:
  DlInfoListElement_s m_dlInfoListElement; ///< DL info list element

};


// ---------------------------------------------------------------------------

/**
 * \ingroup lte
 *
 * abstract model for the Random Access Preamble
 */
class RachPreambleLteControlMessage : public LteControlMessage
{
public:
  RachPreambleLteControlMessage (void);
  
  /** 
   * Set the Random Access Preamble Identifier (RAPID), see 3GPP TS 36.321 6.2.2
   *
   * \param rapid the RAPID
   */
  void SetRapId (uint32_t rapid);
  
  /** 
   * 
   * \return the RAPID
   */
  uint32_t GetRapId () const;

private:
  uint32_t m_rapId; ///< the RAPID

};


// ---------------------------------------------------------------------------

/**
 * \ingroup lte
 *
 * abstract model for the MAC Random Access Response message
 */
class RarLteControlMessage : public LteControlMessage
{
public:
  RarLteControlMessage (void);

  /** 
   * 
   * \param raRnti the RA-RNTI, see 3GPP TS 36.321 5.1.4
   */
  void SetRaRnti (uint16_t raRnti);

  /** 
   * 
   * \return  the RA-RNTI, see 3GPP TS 36.321 5.1.4
   */
  uint16_t GetRaRnti () const;

  /**
   * a MAC RAR and the corresponding RAPID subheader 
   * 
   */
  struct Rar
  {
    uint8_t rapId; ///< RAPID
    BuildRarListElement_s rarPayload; ///< RAR payload
  };

  /** 
   * add a RAR to the MAC PDU, see 3GPP TS 36.321 6.2.3
   * 
   * \param rar the rar
   */
  void AddRar (Rar rar);

  /** 
   * 
   * \return a const iterator to the beginning of the RAR list
   */
  std::list<Rar>::const_iterator RarListBegin () const;
  
  /** 
   * 
   * \return a const iterator to the end of the RAR list
   */
  std::list<Rar>::const_iterator RarListEnd () const;

private:
  std::list<Rar> m_rarList; ///< RAR list
  uint16_t m_raRnti; ///< RA RNTI

};


// ---------------------------------------------------------------------------

/**
 * \ingroup lte
 * \brief Abstract model for broadcasting the Master Information Block (MIB)
 *        within the control channel (BCCH).
 *
 * MIB is transmitted by eNodeB RRC and received by UE RRC at every radio frame,
 * i.e., every 10 milliseconds.
 *
 * \sa LteEnbRrc::ConfigureCell, LteEnbPhy::StartFrame,
 *     LteUeRrc::DoRecvMasterInformationBlock
 */
class MibLteControlMessage : public LteControlMessage
{
public:
  /**
   * \brief Create a new instance of MIB control message.
   */
  MibLteControlMessage (void);

  /**
   * \brief Replace the MIB content of this control message.
   * \param mib the desired MIB content
   */
  void SetMib (LteRrcSap::MasterInformationBlock mib);

  /**
   * \brief Retrieve the MIB content from this control message.
   * \return the current MIB content that this control message holds
   */
  LteRrcSap::MasterInformationBlock GetMib () const;

private:
  LteRrcSap::MasterInformationBlock m_mib; ///< MIB

}; // end of class MibLteControlMessage


// ---------------------------------------------------------------------------

/**
 * \ingroup lte
 * \brief Abstract model for broadcasting the System Information Block Type 1
 *        (SIB1) within the control channel (BCCH).
 *
 * SIB1 is transmitted by eNodeB RRC and received by UE RRC at the 6th subframe
 * of every odd-numbered radio frame, i.e., every 20 milliseconds.
 *
 * \sa LteEnbRrc::SetSystemInformationBlockType1, LteEnbPhy::StartSubFrame,
 *     LteUeRrc::DoRecvSystemInformationBlockType1
 */
class Sib1LteControlMessage : public LteControlMessage
{
public:
  /**
   * \brief Create a new instance of SIB1 control message.
   */
  Sib1LteControlMessage (void);

  /**
   * \brief Replace the SIB1 content of this control message.
   * \param sib1 the desired SIB1 content
   */
  void SetSib1 (LteRrcSap::SystemInformationBlockType1 sib1);

  /**
   * \brief Retrieve the SIB1 content from this control message.
   * \return the current SIB1 content that this control message holds
   */
  LteRrcSap::SystemInformationBlockType1 GetSib1 () const;

private:
  LteRrcSap::SystemInformationBlockType1 m_sib1; ///< SIB1

}; // end of class Sib1LteControlMessage


// ---------------------------------------------------------------------------

/**
 * \ingroup lte
 * The Sidelink Control Indicator messages defines the RB allocation for the
 * users in the sidelink shared channel
 */
class SciLteControlMessage : public LteControlMessage
{
public:
  SciLteControlMessage (void);

  /**
  * \brief add a SCI into the message
  * \param sci the sci
  */
  void SetSci (SciListElement_s sci);

  /**
  * \brief Get sci informations
  * \return sci messages
  */
  SciListElement_s GetSci (void);

private:
  SciListElement_s m_sci;
};

// ---------------------------------------------------------------------------

/**
 * \ingroup lte
 * The Sidelink Control Indicator messages defines the RB allocation for the
 * users in the sidelink shared channel
 */
class SciLteControlMessageV2x : public LteControlMessage
{
public:
  SciLteControlMessageV2x (void);

  /**
  * \brief add a SCIV2x into the message
  * \param sci the sci
  */
  void SetSci (SciListElementV2x sci);


  /**
  * \brief Get sci informations
  * \return sci messages
  */
  SciListElementV2x GetSci (void);

private:
  SciListElementV2x m_sci;
};

// ---------------------------------------------------------------------------

/**
 * \ingroup lte
 * Abstract model for broadcasting the Master Information Block Sidelink (MIB-SL)
 * MIB-SL is transmitted by sidelink-enabled UEs (when required) every 40 milliseconds.
 * */
class MibSLLteControlMessage : public LteControlMessage
{
public:
  MibSLLteControlMessage (void);

  /**
  * \brief add a MIB-SL into the message
  * \param mibSL the MIB-SL
  */
  void SetMibSL (LteRrcSap::MasterInformationBlockSL mibSL);

  /**
  * \brief Get MIB-SL informations
  * \return mibSL messages
  */
  LteRrcSap::MasterInformationBlockSL GetMibSL (void);

private:
  LteRrcSap::MasterInformationBlockSL m_mibSL;
};


// ---------------------------------------------------------------------------

/**
 * \ingroup lte
 * the discovery message 
 *
 */ 
class SlDiscMessage: public LteControlMessage
{
public:
  SlDiscMessage (void);

  /**
   * \brief set discovery message
   * \param discMsg discovery message
   */
  void SetSlDiscMessage (SlDiscMsg discMsg);

  /**
   * \brief get discovery message
   * \return discovery message
   */
  SlDiscMsg GetSlDiscMessage (void);

private:
SlDiscMsg m_discMsg;

};

} // namespace ns3

#endif  // LTE_CONTROL_MESSAGES_H
