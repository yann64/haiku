/*
 * Copyright 2013 Haiku Inc. All rights reserved.
 * Distributed under the terms of the MIT License.
 */

#ifndef _B_URL_ROSTER_H_
#define _B_URL_ROSTER_H_


#include <stdlib.h>


class BDataIO;
class BUrl;

#ifndef LIBNETAPI_DEPRECATED
namespace BPrivate {

namespace Network {
#endif

class BUrlContext;
class BUrlProtocolListener;
class BUrlRequest;

class BUrlProtocolRoster {
public:
#ifdef LIBNETAPI_DEPRECATED
	static	BUrlRequest*	MakeRequest(const BUrl& url,
								BUrlProtocolListener* listener = NULL,
								BUrlContext* context = NULL);
#else
	static	BUrlRequest*	MakeRequest(const BUrl& url, BDataIO* output,
								BUrlProtocolListener* listener = NULL,
								BUrlContext* context = NULL);
#endif
};

#ifndef LIBNETAPI_DEPRECATED
} // namespace Network

} // namespace BPrivate
#endif

#endif
