/*
 * Copyright 2010-2011, Oliver Tappe, zooey@hirschkaefer.de.
 * Distributed under the terms of the MIT License.
 */
#ifndef _ICU_TIME_CONVERSION_H
#define _ICU_TIME_CONVERSION_H


#include <time.h>

#include <StorageDefs.h>

#include "ICUTimeData.h"
#include "LocaleBackend.h"


namespace BPrivate {
namespace Libroot {


class ICUTimeConversion {
public:
								ICUTimeConversion(const ICUTimeData& timeData);
	virtual						~ICUTimeConversion();

	virtual void				Initialize(
									TimeConversionDataBridge* dataBridge);

			status_t			TZSet(const char* timeZoneID, const char* tz);

			status_t			Localtime(const time_t* inTime,
									struct tm* tmOut);
			status_t			Gmtime(const time_t* inTime, struct tm* tmOut);

			status_t			Mktime(struct tm* inOutTm, time_t& timeOut);

			status_t			Timegm(struct tm* inOutTm, time_t& timeOut);

private:
			status_t			_FillTmValues(const U_NAMESPACE_QUALIFIER
										TimeZone* icuTimeZone,
									const time_t* inTime, struct tm* tmOut);

			status_t			_Mktime(const U_NAMESPACE_QUALIFIER
										TimeZone* icuTimeZone,
									struct tm* inOutTm, time_t& timeOut);

			const ICUTimeData&	fTimeData;

			TimeConversionDataBridge*	fDataBridge;

			U_NAMESPACE_QUALIFIER TimeZone*	fTimeZone;
			char				fTimeZoneID[B_FILE_NAME_LENGTH];
};


}	// namespace Libroot
}	// namespace BPrivate


#endif	// _ICU_TIME_BACKEND_H
