#ifndef ALICALOPID_H
#define ALICALOPID_H
/* Copyright(c) 1998-1999, ALICE Experiment at CERN, All rights reserved. *
 * See cxx source for full Copyright notice     */
/* $Id:  $ */

//_________________________________________________________________________
// Class for PID selection with calorimeters
// The Output of the 2 main methods GetPdg is a PDG number identifying the cluster, 
// being kPhoton, kElectron, kPi0 ... as defined in the header file
//   - GetPdg(const TString calo, const Double_t * pid, const Float_t energy)
//      Reads the PID weights array of the ESDs and depending on its magnitude identifies the particle
//   - GetPdg(const TString calo,const TLorentzVector mom, const AliVCluster * cluster)
//      Recalcultes PID, the bayesian or any new one to be implemented in the future
//      Right now only the possibility to recalculate EMCAL with bayesian and simple PID.
//      In order to recalculate Bayesian, it is necessary to load the EMCALUtils library
//      and do SwitchOnBayesianRecalculation().
//      To change the PID parameters from Low to High like the ones by default, use the constructor 
//      AliCaloPID(flux)
//      where flux is AliCaloPID::kLow or AliCaloPID::kHigh
//      If it is necessary to change the parameters use the constructor 
//      AliCaloPID(AliEMCALPIDUtils *utils) and set the parameters before.
//   - SetPIDBits: Simple PID, depending on the thresholds fDispCut fTOFCut and even the
//     result of the PID bayesian a different PID bit is set. 
//
//  All these methods can be called in the analysis you are interested.
//
//*-- Author: Gustavo Conesa (INFN-LNF)

// --- ROOT system ---
#include <TObject.h> 
class TString ;
class TLorentzVector ;
//class TFormula ;
class TTask;

//--- AliRoot system ---
class AliVCluster;
class AliAODPWG4Particle;
class AliEMCALPIDUtils;
class AliCalorimeterUtils;

class AliCaloPID : public TObject {
	
 public: 
  
  AliCaloPID() ; // ctor
  AliCaloPID(const Int_t particleFlux) ; // ctor, to be used when recalculating bayesian PID
  AliCaloPID(const TTask * emcalpid) ; // ctor, to be used when recalculating bayesian PID and need different parameters
  AliCaloPID(const AliCaloPID & g) ; // cpy ctor
  virtual ~AliCaloPID() ;//virtual dtor

private:
  AliCaloPID & operator = (const AliCaloPID & g) ;//cpy assignment
  
public:
	
  enum PidType {
    kPhoton = 22,
    kPi0 = 111,
    kEta = 221, 
    kElectron = 11, 
    kEleCon = -11, 
    kNeutralHadron = 2112, 
    kChargedHadron = 211, 
    kNeutralUnknown = 130, 
    kChargedUnknown=321
  };
  
  enum TagType {kPi0Decay, kEtaDecay, kOtherDecay, kConversion, kNoTag = -1};
  
  void InitParameters();
  
  Int_t GetPdg(const TString calo, const Double_t * pid, const Float_t energy) const ;
  
  Int_t GetPdg(const TString calo,const TLorentzVector mom, const AliVCluster * cluster) const ;
  
  TString	GetPIDParametersList();
  
  void SetPIDBits(const TString calo,  const AliVCluster * cluster, AliAODPWG4Particle *aodph, const AliCalorimeterUtils* cu);
  
  void Print(const Option_t * opt)const;
  
  //Weight getters
  Float_t  GetEMCALPhotonWeight() const  { return  fEMCALPhotonWeight  ; }
  Float_t  GetEMCALPi0Weight() const     {  return fEMCALPi0Weight  ; }
  Float_t  GetEMCALElectronWeight() const  { return  fEMCALElectronWeight  ; }
  Float_t  GetEMCALChargeWeight() const     {  return fEMCALChargeWeight  ; }
  Float_t  GetEMCALNeutralWeight() const     {  return fEMCALNeutralWeight  ; }
  Float_t  GetPHOSPhotonWeight() const   {  return fPHOSPhotonWeight  ; }
  Float_t  GetPHOSPi0Weight() const   {  return fPHOSPi0Weight  ; }
  Float_t  GetPHOSElectronWeight() const   {  return fPHOSElectronWeight  ; }
  Float_t  GetPHOSChargeWeight() const   {  return fPHOSChargeWeight  ; }
  Float_t  GetPHOSNeutralWeight() const   {  return fPHOSNeutralWeight  ; }
  
//  Bool_t  IsPHOSPIDWeightFormulaOn() const   {  return fPHOSWeightFormula  ; } 
//  TFormula * GetPHOSPhotonWeightFormula() const     {  return fPHOSPhotonWeightFormula  ; } 
//  TFormula * GetPHOSPi0WeightFormula() const    {  return fPHOSPi0WeightFormula  ; }
//  
  //Weight setters
  void SetEMCALPhotonWeight(Float_t  w){  fEMCALPhotonWeight = w ; }
  void SetEMCALPi0Weight(Float_t  w){  fEMCALPi0Weight = w ; }
  void SetEMCALElectronWeight(Float_t  w){  fEMCALElectronWeight = w ; }
  void SetEMCALChargeWeight(Float_t  w){  fEMCALChargeWeight = w ; }
  void SetEMCALNeutralWeight(Float_t  w){  fEMCALNeutralWeight = w ; }
  void SetPHOSPhotonWeight(Float_t  w){  fPHOSPhotonWeight = w ; }
  void SetPHOSPi0Weight(Float_t  w){  fPHOSPi0Weight = w ; }
  void SetPHOSElectronWeight(Float_t  w){  fPHOSElectronWeight = w ; }
  void SetPHOSChargeWeight(Float_t  w){  fPHOSChargeWeight = w ; }
  void SetPHOSNeutralWeight(Float_t  w){  fPHOSNeutralWeight = w ; }
  
//  void UsePHOSPIDWeightFormula(Bool_t par)  { fPHOSWeightFormula  = par; } 
//  void SetPHOSPhotonWeightFormula(TFormula * const photon)    {  fPHOSPhotonWeightFormula  = photon; } 
//  void SetPHOSPi0WeightFormula(TFormula * const pi0)   {  fPHOSPi0WeightFormula  = pi0; }
  
  //PID bits setters and getters
  
  Bool_t IsTrackMatched(const AliVCluster * cluster, const AliCalorimeterUtils* cu) const ;  
  
  void SetDispersionCut(Float_t dcut ) {fDispCut = dcut; }
  Float_t GetDispersionCut() const {return fDispCut ;}   
  
  void SetTOFCut(Float_t tcut ) {fTOFCut = tcut; }
  Float_t GetTOFCut() const {return fTOFCut ;}   
  
  void SetDebug(Int_t deb) {fDebug=deb;}
  Int_t GetDebug() const {return fDebug;}	
  
  void SwitchOnBayesianRecalculation()  {fRecalculateBayesian = kTRUE ; }
  void SwitchOffBayesianRecalculation() {fRecalculateBayesian = kFALSE; }
  enum eventType{kLow,kHigh};
  void SetLowParticleFlux()  {fParticleFlux = kLow;}
  void SetHighParticleFlux() {fParticleFlux = kHigh;}

private:
  
  Float_t      fEMCALPhotonWeight; //Bayesian PID weight for photons in EMCAL 
  Float_t      fEMCALPi0Weight;  //Bayesian PID weight for pi0 in EMCAL 
  Float_t      fEMCALElectronWeight; //Bayesian PID weight for electrons in EMCAL 
  Float_t      fEMCALChargeWeight;  //Bayesian PID weight for charged hadrons in EMCAL 
  Float_t      fEMCALNeutralWeight;  //Bayesian PID weight for neutral hadrons in EMCAL 
  Float_t      fPHOSPhotonWeight; //Bayesian PID weight for photons in PHOS 
  Float_t      fPHOSPi0Weight; //Bayesian PID weight for pi0 in PHOS 
  Float_t      fPHOSElectronWeight; //Bayesian PID weight for electrons in PHOS 
  Float_t      fPHOSChargeWeight; //Bayesian PID weight for charged hadrons in PHOS 
  Float_t      fPHOSNeutralWeight; //Bayesian PID weight for neutral hadrons in PHOS 
  
//  Bool_t  fPHOSWeightFormula ; //Use parametrized weight threshold, function of energy
//  TFormula * fPHOSPhotonWeightFormula ; //Formula for photon weight
//  TFormula * fPHOSPi0WeightFormula ; //Formula for pi0 weight
  
  Float_t fDispCut;    //Cut on dispersion, used in PID evaluation
  Float_t fTOFCut;     //Cut on TOF, used in PID evaluation
  
  Int_t	 fDebug; //Debug level
	
  Bool_t fRecalculateBayesian;        // Recalculate PID bayesian or use simple PID?
  Int_t  fParticleFlux;               // Particle flux for setting PID parameters
  AliEMCALPIDUtils * fEMCALPIDUtils;  // Pointer to EMCALPID to redo the PID Bayesian calculation
	
  ClassDef(AliCaloPID,4)
} ;


#endif //ALICALOPID_H



