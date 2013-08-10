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

#include "pre-process-incoming-packets.h"
#include "ns3/ndn-fib.h"
#include "ns3/ndn-fib-entry.h"
#include "ns3/ndn-pit-entry.h"
#include "ns3/ndn-interest.h"
#include "ns3/ndn-data.h"

namespace ns3 {
namespace ndn {
namespace fw {

NS_OBJECT_ENSURE_REGISTERED(PreProcessIncomingPackets);

LogComponent PreProcessIncomingPackets::g_log = LogComponent (PreProcessIncomingPackets::GetLogName ().c_str ());

std::string
PreProcessIncomingPackets::GetLogName ()
{
  return "ndn.fw.PreProcessIncomingPackets";
}

TypeId
PreProcessIncomingPackets::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::ndn::fw::PreProcessIncomingPackets")
    .SetGroupName ("Ndn")
    .SetParent <BaseStrategy> ()
    .AddConstructor <PreProcessIncomingPackets> ()

    // .AddAttribute ("Attribute", "Attribute spec",
    //                         StringValue ("DefaultValue"),
    //                         MakeStringAccessor (&BaseStrategy::m_variable),
    //                         MakeStringChecker ())
    ;
  return tid;
}

PreProcessIncomingPackets::PreProcessIncomingPackets ()
{
}

void
PreProcessIncomingPackets::OnInterest (Ptr<Face> face,
                                       Ptr<Interest> interest)
{
  std::cout << "Before BaseStrategy processing of incoming Interest for: " << interest->GetName () << std::endl;
  
  BaseStrategy::OnInterest (face, interest);
}

void
PreProcessIncomingPackets::OnData (Ptr<Face> face,
                                   Ptr<Data> data)
{
  std::cout << "Before BaseStrategy processing of incoming Data for: " << data->GetName () << std::endl;

  BaseStrategy::OnData (face, data);
}


} // namespace fw
} // namespace ndn
} // namespace ns3
