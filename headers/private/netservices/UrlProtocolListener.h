/*
 * Copyright 2010-2017 Haiku Inc. All rights reserved.
 * Distributed under the terms of the MIT License.
 */
#ifndef _B_URL_PROTOCOL_LISTENER_H_
#define _B_URL_PROTOCOL_LISTENER_H_


#include <stddef.h>
#include <cstdlib>

#include <UrlResult.h>


class BCertificate;

#ifndef LIBNETAPI_DEPRECATED
namespace BPrivate {

namespace Network {
#endif

class BUrlRequest;


enum BUrlProtocolDebugMessage {
	B_URL_PROTOCOL_DEBUG_TEXT,
	B_URL_PROTOCOL_DEBUG_ERROR,
	B_URL_PROTOCOL_DEBUG_HEADER_IN,
	B_URL_PROTOCOL_DEBUG_HEADER_OUT,
	B_URL_PROTOCOL_DEBUG_TRANSFER_IN,
	B_URL_PROTOCOL_DEBUG_TRANSFER_OUT
};


class BUrlProtocolListener {
public:
	virtual	void				ConnectionOpened(BUrlRequest* caller);
	virtual	void				HostnameResolved(BUrlRequest* caller,
									const char* ip);
	virtual	void				ResponseStarted(BUrlRequest* caller);
#ifdef LIBNETAPI_DEPRECATED
	virtual	void				HeadersReceived(BUrlRequest* caller,
									const BUrlResult& result);
	virtual	void				DataReceived(BUrlRequest* caller,
									const char* data, off_t position,
									ssize_t size);
	virtual	void				DownloadProgress(BUrlRequest* caller,
									ssize_t bytesReceived, ssize_t bytesTotal);
	virtual	void				UploadProgress(BUrlRequest* caller,
									ssize_t bytesSent, ssize_t bytesTotal);
#else
	virtual	void				HeadersReceived(BUrlRequest* caller);
	virtual	void				BytesWritten(BUrlRequest* caller,
									size_t bytesWritten);
	virtual	void				DownloadProgress(BUrlRequest* caller,
									off_t bytesReceived, off_t bytesTotal);
	virtual void				UploadProgress(BUrlRequest* caller,
									off_t bytesSent, off_t bytesTotal);
#endif

	virtual	void				RequestCompleted(BUrlRequest* caller,
									bool success);
	virtual	void				DebugMessage(BUrlRequest* caller,
									BUrlProtocolDebugMessage type,
									const char* text);
	virtual	bool				CertificateVerificationFailed(
									BUrlRequest* caller,
									BCertificate& certificate,
									const char* message);
};

#ifndef LIBNETAPI_DEPRECATED
} // namespace Network

} // namespace BPrivate
#endif

#endif // _B_URL_PROTOCOL_LISTENER_H_
