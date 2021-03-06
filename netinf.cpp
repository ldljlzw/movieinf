#include "stdafx.h"

int main(int argc, char* argv[]) {
  Env = TEnv(argc, argv, TNotify::StdNotify);
  Env.PrepArgs(TStr::Fmt("\nNETINF. build: %s, %s. Time: %s", __TIME__, __DATE__, TExeTm::GetCurTm()));
  TExeTm ExeTm;
  Try
  const TStr InFNm  = Env.GetIfArgPrefixStr("-i:", "example-cascades.txt", "Input cascades (one file)");
  const TStr GroundTruthFNm = Env.GetIfArgPrefixStr("-n:", "example-network.txt", "Input ground-truth network (one file)");
  const TStr OutFNm  = Env.GetIfArgPrefixStr("-o:", "network", "Output file name(s) prefix");
  const TStr Iters  = Env.GetIfArgPrefixStr("-e:", "5", "Number of iterations");
  const double alpha = Env.GetIfArgPrefixFlt("-a:", 1.0, "Alpha for transmission model");
  const int Model = Env.GetIfArgPrefixInt("-m:", 0, "0:exponential, 1:power law, 2:rayleigh");
  const int Top =Env.GetIfArgPrefixInt("-t:", 10, "select top k as friends");
  const int TakeAdditional = Env.GetIfArgPrefixInt("-s:", 1, "How much additional files to create?\n\
    1:info about each edge, 2:objective function value (+upper bound), 3:Precision-recall plot, 4:all-additional-files (default:1)\n");

  bool ComputeBound = false, ComputeInfo = false; bool CompareGroundTruth = false;
  switch (TakeAdditional) {
     case 1 : ComputeInfo = true; break;
     case 2 : ComputeBound = true; break;
     case 3 : CompareGroundTruth = true; break;
     case 4 :
    	 ComputeInfo = true;
    	 // ComputeBound = true;
    	 CompareGroundTruth = true; break;
     default: FailR("Bad -s: parameter.");
  }

  TNetInfBs NIB(ComputeBound, CompareGroundTruth, Top);
  printf("\nLoading input cascades: %s\n", InFNm.CStr());

  // load cascade from file
  TFIn FIn(InFNm);
  NIB.LoadCascadesTxt(FIn, Model, alpha);

  // load ground truth network
  if (CompareGroundTruth) {
	  TFIn FInG(GroundTruthFNm);
	  NIB.LoadGroundTruthTxt(FInG);
  }

  NIB.Init();
  printf("cascades:%d nodes:%d potential edges:%d\nRunning NETINF...\n", NIB.GetCascs(), NIB.GetNodes(), NIB.CascPerEdge.Len());
  NIB.GreedyOpt(Iters.GetInt());

  // plot showing precision/recall using groundtruth
  if (CompareGroundTruth)
	  TGnuPlot::PlotValV(NIB.PrecisionRecall, TStr::Fmt("%s-precision-recall", OutFNm.CStr()), "Precision Recall", "Recall",
						 "Precision", gpsAuto, false, gpwLinesPoints, false);

  // plot objective function
  if (ComputeBound) {
	  TFltPrV Gains;
	  for (int i=0; i<NIB.EdgeInfoH.Len(); i++)
		  Gains.Add(TFltPr((double)(i+1), NIB.EdgeInfoH[i].MarginalGain));

	  TGnuPlot::PlotValV(Gains, TStr::Fmt("%s-objective", OutFNm.CStr()), "Objective Function", "Iters", "Objective Function");
  }

  // save network in plain text
  NIB.SavePlaneTextNet(TStr::Fmt("%s.txt", OutFNm.CStr()));

  // save edge info
  if (ComputeInfo)
	  NIB.SaveEdgeInfo(TStr::Fmt("%s-edge.info", OutFNm.CStr()));

  // save obj+bound info
  if (ComputeBound)
	  NIB.SaveObjInfo(TStr::Fmt("%s-obj", OutFNm.CStr()));

  Catch
  printf("\nrun time: %s (%s)\n", ExeTm.GetTmStr(), TSecTm::GetCurTm().GetTmStr().CStr());
  return 0;
}
