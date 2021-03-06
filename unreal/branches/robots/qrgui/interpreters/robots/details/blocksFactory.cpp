#include "blocksFactory.h"

#include "../../../kernel/exception/exception.h"
#include "blocks/timerBlock.h"
#include "blocks/beepBlock.h"
#include "blocks/initialBlock.h"
#include "blocks/initialBlockWithPorts.h"
#include "blocks/finalBlock.h"
#include "blocks/dummyBlock.h"
#include "blocks/waitForTouchSensorBlock.h"
#include "blocks/waitForSonarDistanceBlock.h"
#include "blocks/enginesForwardBlock.h"
#include "blocks/enginesBackwardBlock.h"
#include "blocks/enginesStopBlock.h"
#include "blocks/loopBlock.h"
#include "blocks/forkBlock.h"
#include "blocks/playToneBlock.h"
#include "blocks/functionBlock.h"
#include "blocks/waitForColorBlock.h"
#include "blocks/waitForColorIntensityBlock.h"
#include "blocks/ifBlock.h"

using namespace qReal;
using namespace interpreters::robots::details;
using namespace blocks;

BlocksFactory::BlocksFactory(models::GraphicalModelAssistApi const &graphicalModelApi
		, models::LogicalModelAssistApi const &logicalModelApi
		, RobotModel * const robotModel
		, gui::ErrorReporter * const errorReporter
		, BlocksTable * const blocksTable, BlockParser * const parser)
	: mRobotModel(robotModel)
	, mGraphicalModelApi(graphicalModelApi)
	, mLogicalModelApi(logicalModelApi)
	, mErrorReporter(errorReporter)
	, mBlocksTable(blocksTable)
	, mParser(parser)
{
}

BlockParser * BlocksFactory::getParser()
{
	return mParser;
}

Block *BlocksFactory::block(Id const &element)
{
	Block * newBlock = NULL;
	if (elementMetatypeIs(element, "InitialNode"))
		newBlock = new InitialBlock(*mRobotModel);
	else if (elementMetatypeIs(element, "InitialBlock"))
		newBlock = new InitialBlockWithPorts(*mRobotModel);
	else if (elementMetatypeIs(element, "FinalNode"))
		newBlock = new FinalBlock();
	else if (elementMetatypeIs(element, "Beep"))
		newBlock = new BeepBlock(mRobotModel->brick());
	else if (elementMetatypeIs(element, "Timer"))
		newBlock = new TimerBlock();
	else if (elementMetatypeIs(element, "WaitForTouchSensor"))
		newBlock = new WaitForTouchSensorBlock(mRobotModel);
	else if (elementMetatypeIs(element, "WaitForSonarDistance"))
		newBlock = new WaitForSonarDistanceBlock(mRobotModel);
	else if (elementMetatypeIs(element, "EnginesForward"))
		newBlock = new EnginesForwardBlock(mRobotModel->motorA(), mRobotModel->motorB(), mRobotModel->motorC());
	else if (elementMetatypeIs(element, "EnginesBackward"))
		newBlock = new EnginesBackwardBlock(mRobotModel->motorA(), mRobotModel->motorB(), mRobotModel->motorC());
	else if (elementMetatypeIs(element, "EnginesStop"))
		newBlock = new EnginesStopBlock(mRobotModel->motorA(), mRobotModel->motorB(), mRobotModel->motorC());
	else if (elementMetatypeIs(element, "Loop"))
		newBlock = new LoopBlock();
	else if (elementMetatypeIs(element, "Fork"))
		newBlock = new ForkBlock();
	else if (elementMetatypeIs(element, "PlayTone"))
		newBlock = new PlayToneBlock(mRobotModel->brick());
	else if (elementMetatypeIs(element, "Function"))
		newBlock = new FunctionBlock();
	else if (elementMetatypeIs(element, "WaitForColor"))
		newBlock = new WaitForColorBlock(mRobotModel);
	else if (elementMetatypeIs(element, "WaitForColorIntensity"))
		newBlock = new WaitForColorIntensityBlock(mRobotModel);
	else if (elementMetatypeIs(element, "IfBlock"))
		newBlock = new IfBlock();
	else
		newBlock = new DummyBlock();

	newBlock->init(element, mGraphicalModelApi, mLogicalModelApi, *mBlocksTable, mErrorReporter, mParser);
	return newBlock;
}

bool BlocksFactory::elementMetatypeIs(Id const &element, QString const &metatype)
{
	return element.type() == Id("RobotsMetamodel", "RobotsDiagram", metatype);
}
