#ifndef hwwBabyMaker_h
#define hwwBabyMaker_h

#include "babyMaker.h"
#include "fastjet/ClusterSequence.hh"
#include "fastjet/contrib/SoftDrop.hh"
#include "fastjet/contrib/Nsubjettiness.hh"

class hwwBabyMaker: public babyMaker
{
    public:
        hwwBabyMaker();
        ~hwwBabyMaker();

        RooUtil::Processor* processor;

        virtual void ProcessObjectsPrePassSelection();
        virtual void ProcessElectrons();
        virtual void ProcessMuons();
        virtual bool PassSelection();

        void ReClusterFatJets();

        class ReCluster
        {
            public:
                LV J_p4;
                LV J_SD_p4;
                LV q0_p4;
                LV q1_p4;
                fastjet::PseudoJet J_pj;
                fastjet::PseudoJet J_SD_pj;
                fastjet::PseudoJet q0_pj;
                fastjet::PseudoJet q1_pj;
                float tau1;
                float tau2;
                float tau3;
                float tau31;
                float tau32;
                float tau21;
                float SD_tau1;
                float SD_tau2;
                float SD_tau3;
                float SD_tau31;
                float SD_tau32;
                float SD_tau21;
                bool found_jet;
                void ReClusterFatJets(LV&);
                static LV getLV(fastjet::PseudoJet&);

        };

        ReCluster recl;

        virtual void AddOutput();
        virtual void FillOutput();

        static bool isPt20Electron(int idx);
        static bool isPt20Muon(int idx);
        static bool isPt10Electron(int idx);
        static bool isPt10Muon(int idx);
        bool isLeptonOverlappingWithJet(int ijet);

        //__________________________________________________________________
        // Lepton module
        class LeptonModule: public RooUtil::Module
        {
            public:
                hwwBabyMaker* babymaker;
                LeptonModule(hwwBabyMaker* parent) { babymaker = parent; }
                virtual void AddOutput();
                virtual void FillOutput();
        };

        //__________________________________________________________________
        // FatJet module
        class FatJetModule: public RooUtil::Module
        {
            public:
                hwwBabyMaker* babymaker;
                FatJetModule(hwwBabyMaker* parent) { babymaker = parent; }
                virtual void AddOutput();
                virtual void FillOutput();
        };

        //__________________________________________________________________
        // Trigger module
        class TriggerModule: public RooUtil::Module
        {
            public:
                hwwBabyMaker* babymaker;
                TriggerModule(hwwBabyMaker* parent) { babymaker = parent; }
                virtual void AddOutput();
                virtual void FillOutput();
        };

        //__________________________________________________________________
        // Jet module
        class JetModule: public RooUtil::Module
        {
            public:
                hwwBabyMaker* babymaker;
                JetModule(hwwBabyMaker* parent) { babymaker = parent; }
                virtual void AddOutput();
                virtual void FillOutput();
        };

        //__________________________________________________________________
        // MET module
        class METModule: public RooUtil::Module
        {
            public:
                hwwBabyMaker* babymaker;
                METModule(hwwBabyMaker* parent) { babymaker = parent; }
                virtual void AddOutput();
                virtual void FillOutput();
        };

        //__________________________________________________________________
        // HWWlvjj Truth Module
        class HWWlvjjTruthModule: public RooUtil::Module
        {
            public:
                hwwBabyMaker* babymaker;
                HWWlvjjTruthModule(hwwBabyMaker* parent) { babymaker = parent; }
                virtual void AddOutput();
                virtual void FillOutput();
                void AddOutput_ggHToWWToLNuQQ();
                void AddOutput_HWW();
                void FillOutput_ggHToWWToLNuQQ();
                void FillOutput_HWW();
        };

        //__________________________________________________________________
        // Higgs Reconstruction Module
        class HiggsRecoModule: public RooUtil::Module
        {
            public:
                hwwBabyMaker* babymaker;
                HiggsRecoModule(hwwBabyMaker* parent) { babymaker = parent; }
                virtual void AddOutput();
                virtual void AddOutput_Htag();
                virtual void FillOutput();
                virtual void FillOutput_Htag();
                std::tuple<LV, int> SelectLepton(LV ref, float dphithresh=TMath::Pi()/2.);
                std::tuple<LV, int> SelectFatJet(LV ref, float dphithresh=TMath::Pi()/2.);
                std::tuple<LV, int> SelectVbosonJet(LV ref, float dphithresh=0.1);
        };

        //__________________________________________________________________
        // Recoil module
        class RecoilModule: public RooUtil::Module
        {
            public:
                hwwBabyMaker* babymaker;
                TString suffix;
                TString jettype;
                float threshold;
                TString bname;
                TString bname_prefix;
                RecoilModule(hwwBabyMaker* parent, TString sfx="", TString jt="jets_p4", float thr=(TMath::Pi() * 2./4.))
                {
                    babymaker = parent;
                    suffix = sfx;
                    jettype = jt;
                    threshold = thr;
                    bname_prefix = TString::Format("Recoil%s", suffix.Data());
                    bname = TString::Format("Recoil%s_p4", suffix.Data());
                }
                virtual void AddOutput();
                virtual void FillOutput();
                void AddOutput_v1();
                void AddOutput_v2();
                void FillOutput_v1();
                void FillOutput_v2();
        };

        //__________________________________________________________________
        // GenPart
        class GenPartModule: public RooUtil::Module
        {
            public:
                hwwBabyMaker* babymaker;
                GenPartModule(hwwBabyMaker* parent) { babymaker = parent; }
                virtual void AddOutput();
                virtual void FillOutput();
        };

        //__________________________________________________________________
        // Event
        class EventModule: public RooUtil::Module
        {
            public:
                hwwBabyMaker* babymaker;
                EventModule(hwwBabyMaker* parent) { babymaker = parent; }
                virtual void AddOutput();
                virtual void FillOutput();
        };

};

#endif