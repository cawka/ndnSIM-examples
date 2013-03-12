/* -*-  Mode: C++; c-file-style: "gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2012-2013 University of California, Los Angeles
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

#ifndef NODE_ACCESS_POLICY_H_
#define NODE_ACCESS_POLICY_H_

#include <boost/intrusive/options.hpp>
#include <boost/intrusive/list.hpp>

#include <ns3/nstime.h>
#include <ns3/simulator.h>
#include <ns3/traced-callback.h>

#include <ns3/node.h>
#include <ns3/ndn-content-store.h>
#include <ns3/channel.h>

namespace ns3 {
namespace ndn {
namespace ndnSIM {

/**
 * @brief Traits for freshness policy
 */
struct node_access_policy_traits
{
  /// @brief Name that can be used to identify the policy (for NS-3 object model and logging)
  static std::string GetName () { return "NodeAccess"; }

  struct policy_hook_type { };

  template<class Container>
  struct container_hook
  {
    struct type { };
  };

  template<class Base,
           class Container,
           class Hook>
  struct policy
  {
    // struct policy_container {};

    class type
    {
    public:
      typedef policy policy_base; // to get access to get_freshness methods from outside
      typedef Container parent_trie;

      type (Base &base)
        : base_ (base)
      {
      }

      inline void
      update (typename parent_trie::iterator item)
      {
        // do nothing
      }

      inline bool
      insert (typename parent_trie::iterator item)
      {
        Ptr<Node> node = item->payload ()->GetContentStore ()->template GetObject<Node> ();

        std::cout << "ConentObject: " << item->payload ()->GetHeader ()->GetName () << " has been added to Node# " << node->GetId () << std::endl;
        printNeighbors (node);

        return true;
      }

      inline void
      lookup (typename parent_trie::iterator item)
      {
        // do nothing. it's random policy
      }

      inline void
      erase (typename parent_trie::iterator item)
      {
        Ptr<Node> node = item->payload ()->GetContentStore ()->template GetObject<Node> ();

        std::cout << "ConentObject: " << item->payload ()->GetHeader ()->GetName () << " has been evicted from Node# " << node->GetId () << std::endl;

        printNeighbors (node);
      }

      inline void
      clear ()
      {
        // normally, this will be fired only when simulation terminates
      }

      inline void
      set_max_size (size_t max_size)
      {
        max_size_ = max_size;
      }

      inline size_t
      get_max_size () const
      {
        return max_size_;
      }

    private:
      type () : base_(*((Base*)0)) { };

      static std::list< Ptr<Node> >
      enumerateNeighbors (Ptr<Node> node)
      {
        std::list< Ptr<Node> > neighbors;

        for (uint32_t deviceId = 0; deviceId < node->GetNDevices (); deviceId ++)
          {
            Ptr<NetDevice> device = node->GetDevice (deviceId);

            // get channel, to which device is connected (a "wire")
            Ptr<Channel> channel = device->GetChannel ();

            for (uint32_t channelDeviceId = 0; channelDeviceId < channel->GetNDevices (); channelDeviceId ++)
              {
                Ptr<NetDevice> channelDevice = channel->GetDevice (channelDeviceId);
                if (channelDevice == device)
                  continue;

                neighbors.push_back (channelDevice->GetNode ());
              }
          }
        return neighbors;
      }

      static void
      printNeighbors (Ptr<Node> node)
      {
        std::cout << "            NEIGHBORS: ";
        std::list< Ptr<Node> > neighbors = enumerateNeighbors (node);
        for (std::list< Ptr<Node> >::iterator i = neighbors.begin (); i != neighbors.end (); i++)
          {
            std::cout << " " << (*i)->GetId ();
          }
        std::cout << std::endl;
      }

    private:
      Base &base_;
      size_t max_size_;
    };
  };
};

} // ndnSIM
} // ndn
} // ns3

#endif // NODE_ACCESS_POLICY_H
