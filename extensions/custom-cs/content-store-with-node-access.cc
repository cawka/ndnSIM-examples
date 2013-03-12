/* -*-  Mode: C++; c-file-style: "gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2011 University of California, Los Angeles
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

#include <ns3/log.h>
#include <ns3/ndnSIM/model/cs/content-store-impl.h>

#include <ns3/ndnSIM/utils/trie/random-policy.h>
#include <ns3/ndnSIM/utils/trie/lru-policy.h>
#include <ns3/ndnSIM/utils/trie/fifo-policy.h>
#include <ns3/ndnSIM/utils/trie/lfu-policy.h>

#include <ns3/ndnSIM/utils/trie/multi-policy.h>

#include "node-access-policy.h"


#define NS_OBJECT_ENSURE_REGISTERED_TEMPL(type, templ)  \
  static struct X ## type ## templ ## RegistrationClass \
  {                                                     \
    X ## type ## templ ## RegistrationClass () {        \
      ns3::TypeId tid = type<templ>::GetTypeId ();      \
      tid.GetParent ();                                 \
    }                                                   \
  } x_ ## type ## templ ## RegistrationVariable

namespace ns3 {
namespace ndn {

using namespace ndnSIM;

namespace cs {

// just to simplify registration
template<class Policy>
class ContentStoreWithNodeAccess :
    public ContentStoreImpl< ndnSIM::multi_policy_traits< boost::mpl::vector2< Policy, ndnSIM::node_access_policy_traits > > >
{
};


// explicit instantiation and registering
/**
 * @brief ContentStore with freshness and LRU cache replacement policy
 **/
template class ContentStoreWithNodeAccess<lru_policy_traits>;

/**
 * @brief ContentStore with freshness and random cache replacement policy
 **/
template class ContentStoreWithNodeAccess<random_policy_traits>;

/**
 * @brief ContentStore with freshness and FIFO cache replacement policy
 **/
template class ContentStoreWithNodeAccess<fifo_policy_traits>;

/**
 * @brief ContentStore with freshness and Least Frequently Used (LFU) cache replacement policy
 **/
template class ContentStoreWithNodeAccess<lfu_policy_traits>;


NS_OBJECT_ENSURE_REGISTERED_TEMPL(ContentStoreWithNodeAccess, lru_policy_traits);
NS_OBJECT_ENSURE_REGISTERED_TEMPL(ContentStoreWithNodeAccess, random_policy_traits);
NS_OBJECT_ENSURE_REGISTERED_TEMPL(ContentStoreWithNodeAccess, fifo_policy_traits);

NS_OBJECT_ENSURE_REGISTERED_TEMPL(ContentStoreWithNodeAccess, lfu_policy_traits);



} // namespace cs
} // namespace ndn
} // namespace ns3
