#include "Model.h"


Model::Model(Schedule * sche):_sche(sche)
{
	_legList = sche->getLegList();
	_stationList = sche->getStationList();
	_fleetList = sche->getFleetList();


	for (auto&sta : _stationList)
	{
		vector<myNode*> nodes = sta->getNodeList();
		_nodeList.insert(_nodeList.end(), nodes.begin(), nodes.end());
	}

	//check
	for (int i = 0; i < _nodeList.size(); ++i)
	{
		if (i != _nodeList[i]->getId())
		{
			cout << "Error:Model::Model:node id dismatch" << endl;
			exit(0);
		}
	}
}

void Model::init()
{
	cout << "----------------------------------------------------- INIT MODEL --------------------------------------------------------------" << endl;
	_model = IloModel(_env);

	// Var.
	// leg var x_tl
	int countLegVar = 0;
	_legVar = NumVar2Matrix(_env, _fleetList.size());//x_fleet
	for (int t = 0; t < _fleetList.size(); ++t)
	{
		_legVar[t] = IloNumVarArray(_env, _legList.size());//x_fleet_leg
		for (int i = 0; i < _legList.size(); ++i)
		{
			//check
			if (t != _fleetList[t]->getId() || i != _legList[i]->getId())
			{
				cout << "Error:Model::init:leg var x_tl" << endl;
				exit(0);
			}
			
			string name = string("x_t") + to_string(_fleetList[t]->getId()) + string("_leg") + to_string(_legList[i]->getId());
			_legVar[t][i] = IloNumVar(_env, 0, 1, ILOINT, name.c_str());
			_model.add(_legVar[t][i]);
			++countLegVar;
		}
	}

	//ground var y_t_nn
	int countGrcVar = 0;
	_grdArcVar = NumVar2Matrix(_env, _fleetList.size());//y_fleet
	for (int t = 0; t < _fleetList.size(); ++t)
	{
		_grdArcVar[t] = IloNumVarArray(_env, _nodeList.size());//y_fleet_node:cur->next
		for (auto&sta : _stationList)
		{
			vector<myNode*> nodes = sta->getNodeList();
			for (auto&n : nodes)
			{
				//check
				if (countGrcVar != n->getId())
				{
					cout << "Error:Model::init:grc var" << endl;
					exit(0);
				}
				
				int j = n->getId();
				string name = string("y_t") + to_string(_fleetList[t]->getId())
					+ string("_n") + to_string(_nodeList[j]->getId());
				if (n == nodes.back())
				{
					name += string("_n") + to_string(nodes.front()->getId());
				}
				else
				{
					name += string("_n") + to_string(_nodeList[j+1]->getId());
				}
				_grdArcVar[t][j] = IloNumVar(_env, 0, IloInfinity, ILOINT, name.c_str());
				_model.add(_grdArcVar[t][j]);
				++countGrcVar;
			}
		}
	}


	//passenger var q_s_l
	int countPsgVar = 0;
	_psgVar = NumVar2Matrix(_env, Util::scenarioNum);//q_scenario
	for (int s = 0; s < Util::scenarioNum; ++s)
	{
		_psgVar[s] = IloNumVarArray(_env, _legList.size());//x_scenario_leg
		for (auto&leg : _legList)
		{
			int i = leg->getId();
			string name = string("q_s") + to_string(s) + string("_leg") + to_string(leg->getId());
			_legVar[s][i] = IloNumVar(_env, 0, 1, ILOINT, name.c_str());
			_model.add(_legVar[s][i]);
			++countPsgVar;
		}
	}


	cout << ">>> Finish init var." << endl;


	//cover constraints
	_coverRng = IloRangeArray(_env);
	for (int i = 0; i < _legList.size(); ++i)
	{
		IloExpr v(_env);
		for (int t = 0; t < _fleetList.size(); ++t)
		{
			v += _legVar[t][i];//x_t_l
		}

		string name = string("C1_Cover_Leg") + to_string(_legList[i]->getId());
		_coverRng.add(IloRange(_env, 0, v, 1, name.c_str()));
		v.end();
	}
	_model.add(_coverRng);

	//balance constraints
	_blcRng = Rng2Matrix(_env);
	for (int t = 0; t < _fleetList.size();++t)
	{
		_blcRng[t] = IloRangeArray(_env);

		for (auto&sta : _stationList)
		{
			vector<myNode*> nodes = sta->getNodeList();
			for (auto&n : nodes)
			{
				IloExpr v_in(_env);
				//x in
				for (auto&depl : n->getDepLegList())
				{
					v_in += _legVar[t][depl->getId()];
				}
				//y in
				if (n == nodes.front())
				{
					v_in += _grdArcVar[t][nodes.back()->getId() - 1];
				}
				else
				{
					v_in += _grdArcVar[t][n->getId() - 1];
				}

				IloExpr v_out(_env);
				//x out
				for (auto&arrl : n->getArrLegList())
				{
					v_out -= _legVar[t][arrl->getId()];
				}
				//y out
				v_out -= _grdArcVar[t][n->getId()];

				string name = string("C2_Balance_Node") + to_string(n->getId());
				_blcRng[t].add(IloRange(_env, 0, v_in - v_out, 0, name.c_str()));
				v_in.end();
				v_out.end();
			}
		}
		
		_model.add(_blcRng[t]);
	}

	//fleet capacity constraints
	_aftCountRng = IloRangeArray(_env);
	for (auto&t : _fleetList)
	{
		IloExpr v(_env);
		for (auto&leg : _legList)
		{
			if (leg->passCountTime())
			{
				v += _legVar[t->getId()][leg->getId()];
			}
		}

		for (auto&sta : _stationList)
		{
			myNode* countNode = sta->getCountNode();
			v += _grdArcVar[t->getId()][countNode->getId()];

			if (countNode->passCountTime())
			{
				for (auto&leg : countNode->getDepLegList())
				{
					if (leg->getDepTime() > Util::countTime)
					{
						v += _legVar[t->getId()][leg->getId()];
					}
				}
			}

		}
		string name = string("C3_AftNum_Fleet") + to_string(t->getId());
		_aftCountRng.add(IloRange(_env, 0, v, t->getCap(), name.c_str()));
		v.end();

	}

	//demand for each scenario
	
	Rng2Matrix _snrCapRng;//capacity for each scenario
}

void Model::solve()
{
	init();

}
