//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
//
// Copyright (C) 2002 - 2011, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddGeometry.h - Utility Geometric Functions Shared between classes
//
//////////////////////////////////////////////////////////////////////////

#ifndef DDGEOMETRY_H
#define DDGEOMETRY_H
#include "dd/draw/main/ddObject.h"
#include "dd/draw/utilities/ddPoint.h"
#include "dd/draw/utilities/ddRect.h"

class ddGeometry : public ddObject
{
public:
	static bool lineContainsPoint(double x1, double y1, double x2, double y2, double px, double py);
	static int min(int a, int b);
	static int max(int a, int b);
	static int min(double a, double b);
	static int max(double a, double b);
	static double angleFromPoint(ddRect r, ddPoint point);
	static ddPoint edgePointFromAngle(ddRect r, double angle);
	static double range(double min, double max, double num);
	static double lineSize (ddPoint p1, ddPoint p2);
	static bool intersection(ddPoint p1, ddPoint p2, ddPoint p3, ddPoint p4);
	static double ddabs(double value);
	static int ddabs(int value);

private:

};
#endif
