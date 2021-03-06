#include "Screen.h"
#include "CityInfo.h"
#include "State.h"
#include "Building.h"
#include "CityView.h"
#include "FileList.h"
#include "Constants.h"

#define DATA_INTERN 1
#include "Grid.h"

struct _Data_Screen Data_Screen;// = { 800, 600, {80, 60} };

struct _Data_CityInfo Data_CityInfo;
struct _Data_CityInfo_Extra Data_CityInfo_Extra;
struct _Data_CityInfo_Resource Data_CityInfo_Resource;

struct _Data_State Data_State;

struct Data_Building Data_Buildings[MAX_BUILDINGS];
struct _Data_Buildings_Extra Data_Buildings_Extra;

struct Data_CityView Data_CityView;

struct _Data_FileList Data_FileList;

const int Constant_SalaryForRank[11] = {0, 2, 5, 8, 12, 20, 30, 40, 60, 80, 100};

const struct MissionId Constant_MissionIds[12] = {
	{0, 0},
	{1, 1},
	{2, 3},
	{4, 5},
	{6, 7},
	{8, 9},
	{10, 11},
	{12, 13},
	{14, 15},
	{16, 17},
	{18, 19},
	{20, 21},
};
