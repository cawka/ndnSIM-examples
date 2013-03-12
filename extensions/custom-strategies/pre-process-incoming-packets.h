/* -*- Mode: C++; c-file-style: "gnu"; tab-width: 4; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2013 University of California, Los Angeles
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
 * Author: Alexander Afanasyev <alexander.afanasyev@ucla.edu>
 */

#ifndef PRE_PROCESS_INCOMING_PACKETS_H
#define PRE_PROCESS_INCOMING_PACKETS_H

#include "ns3/log.h"
#include "ns3/ndn-forwarding-strategy.h"
#include "ns3/ndn-l3-protocol.h"
#include "ns3/ndnSIM/model/fw/best-route.h"

namespace ns3 {
namespace ndn {
namespace fw {

typedef BestRoute BaseStrategy;

class PreProcessIncomingPackets:
    public BaseStrategy
{
public:
  static TypeId
  GetTypeId ();

  static std::string
  GetLogName ();

  PreProcessIncomingPackets ();

  // from ndn-forwarding-strategy
  virtual void
  OnInterest (Ptr<Face> face,
              Ptr<const InterestHeader> header,
              Ptr<const Packet> origPacket);

  virtual void
  OnData (Ptr<Face> face,
          Ptr<const ContentObjectHeader> header,
          Ptr<Packet> payload,
          Ptr<const Packet> origPacket);

protected:
  static LogComponent g_log;
};



} // namespace fw
} // namespace ndn
} // namespace ns3

#endif // CUSTOM_STRATEGY_H
