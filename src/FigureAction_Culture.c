#include "FigureAction_private.h"

#include "Building.h"
#include "Terrain.h"

#include "figure/route.h"

static void FigureAction_cultureCommon(figure *f, int numTicks)
{
	switch (f->actionState) {
		case FigureActionState_150_Attack:
			FigureAction_Common_handleAttack(f);
			break;
		case FigureActionState_149_Corpse:
			FigureAction_Common_handleCorpse(f);
			break;
		case FigureActionState_125_Roaming:
			f->isGhost = 0;
			f->roamLength++;
			if (f->roamLength >= f->maxRoamLength) {
				int x, y;
				if (Terrain_getClosestRoadWithinRadius(
						Data_Buildings[f->buildingId].x,
						Data_Buildings[f->buildingId].y,
						Data_Buildings[f->buildingId].size,
						2, &x, &y)) {
					f->actionState = FigureActionState_126_RoamerReturning;
					f->destinationX = x;
					f->destinationY = y;
					figure_route_remove(f);
					f->roamLength = 0;
				} else {
					f->state = FigureState_Dead;
				}
			}
			FigureMovement_roamTicks(f, numTicks);
			break;
		case FigureActionState_126_RoamerReturning:
			FigureMovement_walkTicks(f, numTicks);
			if (f->direction == DirFigure_8_AtDestination ||
				f->direction == DirFigure_9_Reroute || f->direction == DirFigure_10_Lost) {
				f->state = FigureState_Dead;
			}
			break;
	}
}

static void FigureAction_culture(figure *f, int graphicCategory)
{
	f->terrainUsage = FigureTerrainUsage_Roads;
	f->useCrossCountry = 0;
	f->maxRoamLength = 384;
	int buildingId = f->buildingId;
	if (!BuildingIsInUse(buildingId) || Data_Buildings[buildingId].figureId != f->id) {
		f->state = FigureState_Dead;
	}
	FigureActionIncreaseGraphicOffset(f, 12);
	FigureAction_cultureCommon(f, 1);
	if (f->actionState == FigureActionState_149_Corpse) {
		f->graphicId = image_group(graphicCategory) +
			FigureActionCorpseGraphicOffset(f) + 96;
	} else {
		f->graphicId = image_group(graphicCategory) +
			FigureActionDirection(f) + 8 * f->graphicOffset;
	}
}

void FigureAction_priest(figure *f)
{
	FigureAction_culture(f, GROUP_FIGURE_PRIEST);
}

void FigureAction_schoolChild(figure *f)
{
	f->terrainUsage = FigureTerrainUsage_Roads;
	f->useCrossCountry = 0;
	f->maxRoamLength = 96;
	int buildingId = f->buildingId;
	if (!BuildingIsInUse(buildingId) || Data_Buildings[buildingId].type != BUILDING_SCHOOL) {
		f->state = FigureState_Dead;
	}
	FigureActionIncreaseGraphicOffset(f, 12);
	switch (f->actionState) {
		case FigureActionState_150_Attack:
			FigureAction_Common_handleAttack(f);
			break;
		case FigureActionState_149_Corpse:
			FigureAction_Common_handleCorpse(f);
			break;
		case FigureActionState_125_Roaming:
			f->isGhost = 0;
			f->roamLength++;
			if (f->roamLength >= f->maxRoamLength) {
				f->state = FigureState_Dead;
			}
			FigureMovement_roamTicks(f, 2);
			break;
	}
	if (f->actionState == FigureActionState_149_Corpse) {
		f->graphicId = image_group(GROUP_FIGURE_SCHOOL_CHILD) +
			FigureActionCorpseGraphicOffset(f) + 96;
	} else {
		f->graphicId = image_group(GROUP_FIGURE_SCHOOL_CHILD) +
			FigureActionDirection(f) + 8 * f->graphicOffset;
	}
}

void FigureAction_teacher(figure *f)
{
	FigureAction_culture(f, GROUP_FIGURE_TEACHER_LIBRARIAN);
}

void FigureAction_librarian(figure *f)
{
	FigureAction_culture(f, GROUP_FIGURE_TEACHER_LIBRARIAN);
}

void FigureAction_barber(figure *f)
{
	FigureAction_culture(f, GROUP_FIGURE_BARBER);
}

void FigureAction_bathhouseWorker(figure *f)
{
	FigureAction_culture(f, GROUP_FIGURE_BATHHOUSE_WORKER);
}

void FigureAction_doctor(figure *f)
{
	FigureAction_culture(f, GROUP_FIGURE_DOCTOR_SURGEON);
}

void FigureAction_surgeon(figure *f)
{
	FigureAction_culture(f, GROUP_FIGURE_DOCTOR_SURGEON);
}

void FigureAction_missionary(figure *f)
{
	f->terrainUsage = FigureTerrainUsage_Roads;
	f->useCrossCountry = 0;
	f->maxRoamLength = 192;
	int buildingId = f->buildingId;
	if (!BuildingIsInUse(buildingId) || Data_Buildings[buildingId].figureId != f->id) {
		f->state = FigureState_Dead;
	}
	FigureActionIncreaseGraphicOffset(f, 12);
	FigureAction_cultureCommon(f, 1);
	FigureActionUpdateGraphic(f, image_group(GROUP_FIGURE_MISSIONARY));
}

void FigureAction_patrician(figure *f)
{
	f->terrainUsage = FigureTerrainUsage_Roads;
	f->useCrossCountry = 0;
	f->maxRoamLength = 128;
	if (!BuildingIsInUse(f->buildingId)) {
		f->state = FigureState_Dead;
	}
	FigureActionIncreaseGraphicOffset(f, 12);
	FigureAction_cultureCommon(f, 1);
	FigureActionUpdateGraphic(f, image_group(GROUP_FIGURE_PATRICIAN));
}

void FigureAction_laborSeeker(figure *f)
{
	f->terrainUsage = FigureTerrainUsage_Roads;
	f->useCrossCountry = 0;
	f->maxRoamLength = 384;
	int buildingId = f->buildingId;
	if (!BuildingIsInUse(buildingId) || Data_Buildings[buildingId].figureId2 != f->id) {
		f->state = FigureState_Dead;
	}
	FigureActionIncreaseGraphicOffset(f, 12);
	FigureAction_cultureCommon(f, 1);
	FigureActionUpdateGraphic(f, image_group(GROUP_FIGURE_LABOR_SEEKER));
}

void FigureAction_marketTrader(figure *f)
{
	f->terrainUsage = FigureTerrainUsage_Roads;
	f->useCrossCountry = 0;
	f->maxRoamLength = 384;
	
	if (!BuildingIsInUse(f->buildingId) || Data_Buildings[f->buildingId].figureId != f->id) {
		f->state = FigureState_Dead;
	}
	FigureActionIncreaseGraphicOffset(f, 12);
	if (f->actionState == FigureActionState_125_Roaming) {
		// force return on out of stock
		int stock = Building_Market_getMaxFoodStock(f->buildingId) +
			Building_Market_getMaxGoodsStock(f->buildingId);
		if (f->roamLength >= 96 && stock <= 0) {
			f->roamLength = f->maxRoamLength;
		}
	}
	FigureAction_cultureCommon(f, 1);
	FigureActionUpdateGraphic(f, image_group(GROUP_FIGURE_MARKET_LADY));
}

