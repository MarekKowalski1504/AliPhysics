#ifndef _AliNuclexEventCuts_h_
#define _AliNuclexEventCuts_h_

#include <TNamed.h>
#include <string>
using std::string;

#include "AliVEvent.h"

class TList;

class AliNuclexEventCuts : public TNamed {
  public:
    AliNuclexEventCuts();
 
    bool   AcceptEvent (AliVEvent *ev, TList* qaList = 0x0);
    float  GetCentrality (unsigned int estimator = 0) { return fCentPercentiles[estimator]; }
    void AddQAplotsToList(TList *qaList);
    
    void  SetupLHC15o();

    /// While the general philosophy here is to avoid setters and getters (this is not an API we expose)
    /// for some variables (like the max z vertex position) standard the cuts usually follow some patterns
    /// (e.g. the max vertex z position is always symmetric wrt the nominal beam collision point) thus
    /// is convenient having special setters in this case.
    void          SetMaxVertexZposition (float max) { fMinVtz = -fabs(max); fMaxVtz = fabs(max); }
    void          SetCentralityRange(float min, float max) { fMinCentrality = min; fMaxCentrality = max; }

    bool          fRequireTrackVertex;
    float         fMinVtz;
    float         fMaxVtz;
    float         fMaxDeltaSpdTrackAbsolute;
    float         fMaxDeltaSpdTrackNsigmaSPD;
    float         fMaxDeltaSpdTrackNsigmaTrack;
//    float         fMaxDispersionSPDvertex;
//    float         fMaxResolutionSPDvertex;

    bool          fRejectDAQincomplete;           ///< Reject events that have incomplete information

    int           fRejectPileupSPD;               ///< Reject all the events with SPD pile-up vertices with more than fRejectPileupSPD contributors

    int           fCentralityFramework;           ///< 0: skip centrality checks, 1: legacy centrality framework, 2: multiplicity framework
    float         fMinCentrality;                 ///< Minimum centrality to be analised
    float         fMaxCentrality;                 ///< Maximum centrality to be analised
    string        fCentEstimators[2];             ///< Centrality estimators: the first is used as main estimators, that is correlated with the second to monitor spurious events.
    float         fCentPercentiles[2];            ///< Centrality percentiles 
    float         fMaxDeltaEstimators;            ///< Maximum difference between two centrality estimators

    AliVEvent::EOfflineTriggerTypes fTriggerMask; ///< Trigger mask 

    static const string fgkLabels[2];
  private:

    ClassDef(AliNuclexEventCuts,2)
};

#endif

