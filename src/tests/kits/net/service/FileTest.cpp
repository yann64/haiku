/*
 * Copyright 2020, Haiku, Inc.
 * Distributed under the terms of the MIT License.
 */

#include "FileTest.h"

#include <stdlib.h>

#include <File.h>
#include <FileRequest.h>
#include <Url.h>
#include <UrlProtocolRoster.h>
#include <UrlProtocolListener.h>

#include <ThreadedTestCaller.h>
#include <TestUtils.h>

#include "TestServer.h"


using namespace BPrivate::Network;


class StopTestListener : public BDataIO {
public:
	StopTestListener(BUrlRequest* request = NULL)
	{
		SetRequest(request);
	}

	ssize_t Write(const void*, size_t size)
	{
		fRequest->Stop();
		return size;
	}

	void SetRequest(BUrlRequest* request)
	{
		fRequest = request;
	}

private:
	BUrlRequest* fRequest;
};


void
FileTest::StopTest()
{
	StopTestListener listener;
	char tmpl[] = "/tmp/filestoptestXXXXXX";
	int fd = mkstemp(tmpl);
	CHK(fd != -1);
	close(fd);

	BFile file(tmpl, O_WRONLY | O_CREAT);
	CHK(file.InitCheck() == B_OK);
	BString content;
	/* number chosen to be larger than BFileRequest buffer, adjust as needed */
	content.Append('f', 40960);

	CHK(file.WriteExactly(content.String(), content.Length()) == B_OK);

	BUrl url("file://");
	url.SetPath(tmpl);
	BUrlRequest *request = BUrlProtocolRoster::MakeRequest(url, &listener);
	CHK(request != NULL);

	listener.SetRequest(request);
	thread_id thr = request->Run();
	status_t dummy;
	wait_for_thread(thr, &dummy);

	CHK(request->Status() == B_INTERRUPTED);

	delete request;

	request = BUrlProtocolRoster::MakeRequest("file:///", &listener);
	CHK(request != NULL);

	listener.SetRequest(request);
	thr = request->Run();
	wait_for_thread(thr, &dummy);

	CHK(request->Status() == B_INTERRUPTED);

	delete request;
}


/* static */ void
FileTest::AddTests(BTestSuite& parent)
{
	CppUnit::TestSuite *suite = new CppUnit::TestSuite("FileTest");

	suite->addTest(new CppUnit::TestCaller<FileTest>("FileTest: Stop requests",
		&FileTest::StopTest));

	parent.addTest("FileTest", suite);
}
