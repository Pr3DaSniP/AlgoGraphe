#ifndef GRAPHEORIENTE_H
#define GRAPHEORIENTE_H

#include "Graphe.h"

class GrapheOriente : public Graphe {
protected:
	// FP & APP
	vector<int> d_fp;
	vector<int> d_app;

	// DDI & DDE
	vector<int> d_ddi;
	vector<int> d_dde;

	// MATRICE DES DISTANCES
	vector<vector<int>> d_matriceDistance;

	// RANG
	vector<int> d_rang;

	// TARJAN
	vector<int> d_tarjan_num;
	vector<int> d_tarjan_prem;
	vector<int> d_tarjan_pilch;
	vector<int> d_tarjan_cfc;

	// FSR & APSR
	vector<int> d_fsr;
	vector<int> d_apsr;

	// BR
	vector<int> d_br;

	virtual void initialisation() override;
private:
	
	void calculDDI();
	void calculDDE();
	void FS_APS_to_FP_APP();
	void calculMatDistance();
	void calculRang();
	void calculTarjan();
	void dfs(int u, vector<int>& num, vector<int>& cfc, vector<int>& tarj, vector<bool>& entarj);
	void calculGrapheReduit();
	void calculBaseReduit();
	vector<int> distanceFrom(int s);
	void empiler(int x, vector<int>& pilch);
	
public:
	GrapheOriente(vector<int> fs, vector<int> aps);
	GrapheOriente(vector<vector<int>> matrice);
	
	vector<int> getFP();
	vector<int> getAPP();
	vector<int> getDDI();
	vector<int> getDDE();
	vector<vector<int>> getMATRICE_DISTANCE();
	vector<int> getRANG();
	vector<int> getTARJAN_CFC();
	vector<int> getTARJAN_NUM();
	vector<int> getTARJAN_PREM();
	vector<int> getTARJAN_PILCH();
	vector<int> getFSR();
	vector<int> getAPSR();
    vector<int> getBR();

	virtual ~GrapheOriente() = default;
};


#endif // !GRAPHEORIENTE_H
