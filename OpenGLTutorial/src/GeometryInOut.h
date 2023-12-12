#pragma once

#include "GeometryData.h"
#include "Debug.h"

#include <string>
#include <map>
#include <fstream>
#include <utility>

struct glmCmp
{
	bool operator() (const glm::ivec3& lhs, const glm::ivec3& rhs) const
	{
		if (lhs.x == rhs.x)
		{
			if (lhs.y == rhs.y)
			{
				if (lhs.z == rhs.z)
				{
					return false;
				}
				return lhs.z < rhs.z;
			}
			return lhs.y < rhs.y;
		}
		return lhs.x < rhs.x;
	}

	/*bool operator() (unsigned int lhs[3], unsigned int rhs[3]) const
	{
		if (lhs[0] == rhs[0])
		{
			if (lhs[1] == rhs[1])
			{
				if (lhs[2] == rhs[2])
				{
					return false;
				}
				return lhs[0] < rhs[0];
			}
			return lhs[1] < rhs[1];
		}
		return lhs[0] < rhs[0];
	}*/
};

class GeometryInOut
{
public:
	static bool Import(std::string file, GeometryData& geometryData);

private:
	static bool ImportObj(std::string file, GeometryData& geometryData);
};