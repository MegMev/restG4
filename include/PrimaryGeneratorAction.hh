//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
/// \file radioactivedecay/rdecay01/include/PrimaryGeneratorAction.hh
/// \brief Definition of the PrimaryGeneratorAction class
//
//
// $Id: PrimaryGeneratorAction.hh 68017 2013-03-13 13:29:53Z gcosmo $
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef PrimaryGeneratorAction_h
#define PrimaryGeneratorAction_h 1

#include <TH1D.h>
#include <TF3.h>

#include <fstream>
#include <iostream>

#include "DetectorConstruction.hh"
#include "G4IonTable.hh"
#include "G4ParticleGun.hh"
#include "G4VUserPrimaryGeneratorAction.hh"
#include "TRestGeant4Particle.h"
#include "globals.hh"
using namespace std;

const int nSpct = 3000;

class G4Event;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction {
   public:
    PrimaryGeneratorAction(DetectorConstruction* pDetector);
    ~PrimaryGeneratorAction();

   public:
    virtual void GeneratePrimaries(G4Event*);
    G4ParticleGun* GetParticleGun() { return fParticleGun; };

    void SetSpectrum(TH1D* spt, double eMin = 0, double eMax = 0);
    void SetGeneratorSpatialDensity(TString str);

    void SetAngularDistribution(TH1D* ang) { fAngularDistribution = ang; }

   private:
    vector<TRestGeant4Particle> fTempParticles;

    G4ParticleGun* fParticleGun;
    DetectorConstruction* fDetector;
    G4ParticleDefinition* fParticle = nullptr;

    TH1D* fSpectrum;
    TH1D* fAngularDistribution;
    TF3* fGeneratorSpatialDensityFunction;

    Int_t startEnergyBin;
    Int_t endEnergyBin;
    Double_t fSpectrumIntegral;

    Int_t nBiasingVolumes;

    Double_t energyFactor;

    Double_t lastEnergy;

    void SetParticlePosition();
    G4ParticleDefinition* SetParticleDefinition(Int_t particlesourceindex, TRestGeant4Particle p);
    void SetParticleEnergy(Int_t particlesourceindex, TRestGeant4Particle p);
    void SetParticleDirection(Int_t particlesourceindex, TRestGeant4Particle p);

    G4ThreeVector GetIsotropicVector();
    Double_t GetAngle(G4ThreeVector x, G4ThreeVector y);
    Double_t GetCosineLowRandomThetaAngle();

    void GenPositionOnGDMLVolume(double& x, double& y, double& z);
    void GenPositionOnGDMLSurface(double& x, double& y, double& z);
    void GenPositionOnBoxVolume(double& x, double& y, double& z);
    void GenPositionOnBoxSurface(double& x, double& y, double& z);
    void GenPositionOnSphereVolume(double& x, double& y, double& z);
    void GenPositionOnSphereSurface(double& x, double& y, double& z);
    void GenPositionOnCylinderVolume(double& x, double& y, double& z);
    void GenPositionOnCylinderSurface(double& x, double& y, double& z);
    void GenPositionOnPoint(double& x, double& y, double& z);
    void GenPositionOnWall(double& x, double& y, double& z);
    void GenPositionOnPlate(double& x, double& y, double& z);

    G4String fParType;
    G4String fGenType;
    G4double fParEnergy;
    G4double fParGenerator;

    G4String fSpctFilename;

    G4int gammaSpectrum[nSpct];

    G4int nCollections;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
