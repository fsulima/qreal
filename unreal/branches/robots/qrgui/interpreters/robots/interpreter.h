#pragma once

#include <QtCore/QObject>

#include "../../models/graphicalModelAssistApi.h"
#include "../../models/logicalModelAssistApi.h"
#include "../../mainwindow/errorReporter.h"
#include "../../mainwindow/mainWindowInterpretersInterface.h"

#include "robotCommunicationInterface.h"
#include "sensorConstants.h"
#include "details/robotParts/robotModel.h"
#include "details/thread.h"
#include "details/blocksTable.h"

#include "../visualDebugger/blockParser.h"

namespace qReal {
namespace interpreters {
namespace robots {

class Interpreter : public QObject
{
	Q_OBJECT

public:
	Interpreter(models::GraphicalModelAssistApi const &graphicalModelApi
			, models::LogicalModelAssistApi const &logicalModelApi
			, qReal::gui::MainWindowInterpretersInterface &mainWindowInterface
			, details::RobotModel * const robotModel);
	~Interpreter();

	details::RobotModel *robotModel();
	void setRobotModel(details::RobotModel * const robotModel);
	void interpret(Id const &currentDiagramId);
	void configureSensors(sensorType::SensorTypeEnum const &port1
			, sensorType::SensorTypeEnum const &port2
			, sensorType::SensorTypeEnum const &port3
			, sensorType::SensorTypeEnum const &port4);
	void stop();
	void stopRobot();
	void setRobotImplementation(details::robotImplementations::AbstractRobotModelImplementation *robotImpl);

private slots:
	void threadStopped();
	void newThread(details::blocks::Block * const startBlock);
	void runTimer();
	void readSensorValues();
	void slotFailure();
	void responseSlot1(int sensorValue);
	void responseSlot2(int sensorValue);
	void responseSlot3(int sensorValue);
	void responseSlot4(int sensorValue);

private:
	enum InterpreterState {
		interpreting
		, idle
	};

	models::GraphicalModelAssistApi const &mGraphicalModelApi;
	models::LogicalModelAssistApi const &mLogicalModelApi;
	qReal::gui::MainWindowInterpretersInterface &mInterpretersInterface;

	InterpreterState mState;
	QList<details::Thread *> mThreads;  // Has ownership
	details::RobotModel *mRobotModel;
	details::BlocksTable *mBlocksTable;  // Has ownership
	BlockParser *mParser;
	QTimer *mTimer;

	Id const findStartingElement(Id const &diagram) const;
	void addThread(details::Thread * const thread);
	void updateSensorValues (QString const &sensorVariableName, int sensorValue);
};

}
}
}
