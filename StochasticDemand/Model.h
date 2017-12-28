#pragma once
#include<ilcplex/ilocplex.h>
#include"Util.h"

#include"Fleet.h"
#include"Leg.h"
#include"Station.h"
#include"Schedule.h"

typedef IloArray<IloNumVarArray> NumVar2Matrix;
typedef IloArray<IloNumArray> Num2Matrix;
typedef IloArray<IloRangeArray> Rng2Matrix;

class Model
{
private:
	Schedule * _sche;

	vector<Leg *> _legList;
	vector<Station *> _stationList;
	vector<Fleet*> _fleetList;

	vector<myNode*> _nodeList;

	// Env
	IloEnv _env;
	IloModel _model;
	IloCplex _solver;

	// Vars.
	NumVar2Matrix _legVar;//x_t_l
	NumVar2Matrix _grdArcVar;//y_t_nn
	NumVar2Matrix _psgVar;//qsl
	
	// Cons.
	IloRangeArray _coverRng;//flight cover
	Rng2Matrix _blcRng;//flow balance
	IloRangeArray _aftCountRng;//aircraft count
	
	Rng2Matrix _snrDmdRng;//demand for each scenario
	Rng2Matrix _snrCapRng;//capacity for each scenario


public:
	Model(Schedule* sche);

	void init();
	void solve();


};

