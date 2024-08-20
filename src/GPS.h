/*
	Plugin-SDK (Grand Theft Auto) source file
	Authors: GTA Community. See more here
	https://github.com/DK22Pac/plugin-sdk
	Do not delete this comment block. Respect others' work!
*/
#include <algorithm>
#include <chrono>
#include <cmath>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <limits>

#include "CFont.h"
#include "CGeneral.h"
#include "CHudColours.h"
#include "CMenuManager.h"
#include "CObject.h"
#include "CPed.h"
#include "CPickup.h"
#include "CPickups.h"
#include "CPools.h"
#include "CRadar.h"
#include "CTheScripts.h"
#include "CVehicle.h"
#include "CWorld.h"
#include "Color.h"
#include "RenderWare.h"
#include "common.h"
#include "d3d9.h"
#include "plugin.h"

#include "Config.h"
#include "DistCache.h"
#include "Logger.h"
#include "util.h"

/*
	#define MAX_NODE_POINTS 50000
	#define GPS_LINE_WIDTH  4.0f
	#define GPS_LINE_R  180
	#define GPS_LINE_G  24
	#define GPS_LINE_B  24
	#define GPS_LINE_A  255
	#define MAX_TARGET_DISTANCE 10.0f
*/

#define MAX_NODE_POINTS 5000

class GPS
{
  private:
	// Config
	Config cfg = Config("SA.GPS.CONF.ini");
	Logger logger = Logger(false);
	// These variables will be used for the gps route following the target blip
	// set by the player
	float targetDistance;
	short targetNodesCount;

	CVector destVec;

	CNodeAddress t_ResultNodes[MAX_NODE_POINTS];
	RwIm2DVertex t_LineVerts[MAX_NODE_POINTS * 4];

	// These will be used for mission objectives
	float missionDistance;
	short missionNodesCount;

	CNodeAddress m_ResultNodes[MAX_NODE_POINTS];
	RwIm2DVertex m_LineVerts[MAX_NODE_POINTS * 4];

	char pathNodesToStream[1024];
	int pathNodes[50000];

	CPed *player;

	bool renderMissionRoute;
	bool renderTargetRoute;

	CVector targetTracePos;

	tRadarTrace *mTrace;

	// Graphics stuff & temp variables moved from heap
	CVector2D tmpNodePoints[MAX_NODE_POINTS];
	CVector2D targetScreen;
	CVector2D tmpPoint;
	CVector2D dir;
	float angle;
	unsigned int vertIndex = 0;
	CVector2D shift[2];
	CPathNode *currentNode;
	CVector nodePosn;

	void DrawRadarOverlayHandle();
	void GameEventHandle();
	void DrawHudEventHandle();

	void Run();

	constexpr bool CheckBMX(CPed *player);
	constexpr bool NavEnabled(CPed *player);

	// Self explanatory.
	void calculatePath(CVector destPosn, short &nodesCount, CNodeAddress *resultNodes, float &gpsDistance);

	void renderPath(CVector tracePos, short color, bool friendly, short &nodesCount, CNodeAddress *resultNodes,
					float &gpsDistance, RwIm2DVertex *lineVerts);

	constexpr void renderMissionTrace(tRadarTrace *trace);

  public:
	GPS();
	~GPS();
} GPSLineRedux;