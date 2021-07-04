/*
 * Copyright 2018-2020, Andrew Lindesay <apl@lindesay.co.nz>.
 * All rights reserved. Distributed under the terms of the MIT License.
 */
#ifndef PROCESS_COORDINATOR_H
#define PROCESS_COORDINATOR_H

#include "ProcessCoordinator.h"

#include <ObjectList.h>

#include "AbstractProcess.h"
#include "AbstractProcessNode.h"


class ProcessCoordinator;


/*! This class carries the state of the current process coordinator so that
    it can be dealt with atomically without having call back to the coordinator.
*/

class ProcessCoordinatorState {
public:
								ProcessCoordinatorState(
									const ProcessCoordinator*
										processCoordinator,
									float progress, const BString& message,
									bool isRunning, status_t errorStatus);
	virtual						~ProcessCoordinatorState();

	const	ProcessCoordinator*	Coordinator() const;
			float				Progress() const;
			BString				Message() const;
			bool				IsRunning() const;
			status_t			ErrorStatus() const;

private:
	const	ProcessCoordinator*	fProcessCoordinator;
			float				fProgress;
			BString				fMessage;
			bool				fIsRunning;
			status_t			fErrorStatus;
};


/*! Clients are able to subclass from this 'interface' in order to accept
    call-backs when a coordinator has exited; either through failure,
    stopping or completion.
*/

class ProcessCoordinatorListener {
public:

/*! Signals to the listener that the coordinator has changed in some way -
	for example, a process has started or stopped or even that the whole
	coordinator has finished.
*/

	virtual void				CoordinatorChanged(
									ProcessCoordinatorState&
									processCoordinatorState) = 0;

};


/*!	Classes implementing this 'interface' are able to consume process
	coordinators.  This may be in order to run them.
*/

class ProcessCoordinatorConsumer {
public:
	virtual	void				Consume(ProcessCoordinator *item) = 0;
};


/*! It is possible to create a number of ProcessNodes (themselves associated
    with AbstractProcess-s) that may have dependencies (predecessors and
    successors) and then an instance of this class is able to coordinate the
    list of ProcessNode-s so that they are all completed in the correct order.
*/

class ProcessCoordinator : public AbstractProcessListener {
public:
								ProcessCoordinator(
									const char* name,
									BMessage* message = NULL);
	virtual						~ProcessCoordinator();

			void				SetListener(
									ProcessCoordinatorListener *listener);

			void				AddNode(AbstractProcessNode* nodes);

			void				ProcessChanged();
				// AbstractProcessListener

			bool				IsRunning();

			void				Start();
			void				Stop();

			status_t			ErrorStatus();

			float				Progress();

	const	BString&			Name() const;
			BMessage*			Message() const;

private:
			bool				_IsRunning(AbstractProcessNode* node);
			void				_CoordinateAndCallListener();
			ProcessCoordinatorState
								_Coordinate();
			ProcessCoordinatorState
								_CreateStatus();
			BString				_CreateStatusMessage();
			int32				_CountNodesCompleted();
			void				_StopSuccessorNodesToErroredOrStoppedNodes();
			void				_StopSuccessorNodes(AbstractProcessNode* node);

private:
			BString				fName;
			BLocker				fLock;
			BObjectList<AbstractProcessNode>
								fNodes;
			ProcessCoordinatorListener*
								fListener;
			BMessage*			fMessage;
			bool				fWasStopped;
};


#endif // PROCESS_COORDINATOR_H
