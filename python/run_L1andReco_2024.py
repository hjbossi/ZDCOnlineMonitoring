# L1Ntuple for ZDC studies with 2023 data
# Hannah Bossi, <hannah.bossi@cern.ch>
# 9/17/2023
import FWCore.ParameterSet.Config as cms
import os
import sys
import itertools


# functions for getting lumisections from filename
import re as RegEx
def get_lumisection(fileName):
    match = RegEx.match(r"run(\d+)_ls(\d+)_stream([A-Za-z0-9]+)_StorageManager.dat",fileName)
    # print("Run Number ", match.group(1),  "LS ", match.group(2), "DataSet ", match.group(3),)     
    return(int(match.group(2)))

from Configuration.Eras.Era_Run3_pp_on_PbPb_cff import Run3_pp_on_PbPb
process = cms.Process('RAW2DIGI', Run3_pp_on_PbPb)

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_cff')
process.load('Configuration.StandardSequences.RawToDigi_Data_cff') # mapper for raw prime
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')


#Replace GT for running over 2024
from Configuration.AlCa.GlobalTag import GlobalTag
process.load("SimCalorimetry.HcalTrigPrimProducers.hcaltpdigi_cff")
process.GlobalTag = GlobalTag(process.GlobalTag, '141X_dataRun3_Prompt_v3')


TFile_outName = "PbPb_387942_RecoL1Ntuple.root"

runNumbers = ["387942",]

# if True validLumiNums are checked
checkLumis = True

# valid LumiSections per run. Note that the range in inclusive
validLumiNums = {
    "387942" : [[20,2000],]
}

ZdcEnergyMethod = "OldMethod"  # options are "Trigger" [Ts2- .4 Ts1], "OldMethod" [Ts2 - Ts1], "TemplateFit"



# To change the number of events, change this part
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(50000),
    output = cms.optional.untracked.allowed(cms.int32,cms.PSet)
)

CONDDIR="forZDC"

# process.es_prefer = cms.ESPrefer('HcalTextCalibrations','es_ascii')
# process.es_ascii = cms.ESSource('HcalTextCalibrations',
#    input = cms.VPSet(
#       cms.PSet(
#          object = cms.string('TPChannelParameters'),
#          file   = cms.FileInPath(CONDDIR+'/DumpTPChannelParameters_Run387473.txt')
#       ),
# )
# )


## Input Source includes RawPrime, Forward, ZeroBias, 
#-----------------------------------
# Input source  
#-----------------------------------
runInputDirs = []
DataType = "RawZB"
TriggerType = "*"
# fileBegin = "/eos/user/m/mnickel/ZDC_Data/{}/".format(DataType)
if DataType =="MinBias":
    rawTag    = cms.InputTag("rawDataRepacker")
    TriggerType = "*"
    runInputDirs = [
        "/eos/cms/store/t0streamer/Data/PhysicsHIMinimumBias0/",
        "/eos/cms/store/t0streamer/Data/PhysicsHIMinimumBias1/",
        "/eos/cms/store/t0streamer/Data/PhysicsHIMinimumBias2/",
        "/eos/cms/store/t0streamer/Data/PhysicsHIMinimumBias3/",
        ]
if DataType =="Forward":
    rawTag    = cms.InputTag("rawDataRepacker")
    TriggerType = "*"
    runInputDirs = [
        "/eos/cms/store/t0streamer/Data/PhysicsHIForward0/",
        "/eos/cms/store/t0streamer/Data/PhysicsHIForward1/",
        "/eos/cms/store/t0streamer/Data/PhysicsHIForward2/",
        "/eos/cms/store/t0streamer/Data/PhysicsHIForward3/",
        "/eos/cms/store/t0streamer/Data/PhysicsHIForward4/",
        "/eos/cms/store/t0streamer/Data/PhysicsHIForward5/",
        "/eos/cms/store/t0streamer/Data/PhysicsHIForward6/",
        "/eos/cms/store/t0streamer/Data/PhysicsHIForward7/",
        "/eos/cms/store/t0streamer/Data/PhysicsHIForward8/",
        ]
if DataType =="ZeroBias":
    rawTag    = cms.InputTag("rawDataCollector")
    TriggerType = "*"
    runInputDirs = [
        "/eos/cms/store/t0streamer/Data/PhysicsHIZeroBias/",
        ]
if DataType =="RawPrime":
    rawTag    = cms.InputTag("rawPrimeDataRepacker")
    TriggerType = "*"
    runInputDirs = [
        "/eos/cms/store/t0streamer/Data/PhysicsHIPhysicsRawPrime0/",
        "/eos/cms/store/t0streamer/Data/PhysicsHIPhysicsRawPrime1/",
        "/eos/cms/store/t0streamer/Data/PhysicsHIPhysicsRawPrime2/",
        "/eos/cms/store/t0streamer/Data/PhysicsHIPhysicsRawPrime3/",
        "/eos/cms/store/t0streamer/Data/PhysicsHIPhysicsRawPrime4/",
        "/eos/cms/store/t0streamer/Data/PhysicsHIPhysicsRawPrime5/",
        "/eos/cms/store/t0streamer/Data/PhysicsHIPhysicsRawPrime6/",
        "/eos/cms/store/t0streamer/Data/PhysicsHIPhysicsRawPrime7/",
        "/eos/cms/store/t0streamer/Data/PhysicsHIPhysicsRawPrime8/",
        "/eos/cms/store/t0streamer/Data/PhysicsHIPhysicsRawPrime9/",
        ]
        
if DataType =="RawZB":
    rawTag    = cms.InputTag("rawDataRepacker")
    TriggerType = "*"
    runInputDirs = [
        "/eos/cms/store/t0streamer/Data/PhysicsHIZeroBiasRAW0/",
        "/eos/cms/store/t0streamer/Data/PhysicsHIZeroBiasRAW1/",
        "/eos/cms/store/t0streamer/Data/PhysicsHIZeroBiasRAW2/",
        ]

if DataType =="PPRef":
    rawTag    = cms.InputTag("rawDataCollector")
    TriggerType = "HLT_PPRefZeroBias_FirstCollisionInTrain_*"
    runInputDirs = [
        "/eos/cms/store/t0streamer/Data/PhysicsPPRefZeroBiasPlusForward0/",
        # "/eos/cms/store/t0streamer/Data/PhysicsPPRefZeroBiasPlusForward1/",
        "/eos/cms/store/t0streamer/Data/PhysicsPPRefZeroBiasPlusForward2/",
        # "/eos/cms/store/t0streamer/Data/PhysicsPPRefZeroBiasPlusForward3/",
        ]


infile    = cms.untracked.vstring()

for runNumber, runInputDir in itertools.product(runNumbers, runInputDirs):
    filedir = runInputDir+'000/'+runNumber[:3]+'/'+runNumber[3:]
    for f in reversed(os.listdir(filedir)):
        validLumi = False
        LumiSection = get_lumisection(f)
        for lumiNum in validLumiNums[runNumber]:
            if (LumiSection >= lumiNum[0] and LumiSection <= lumiNum[1]) : validLumi = True
        if validLumi == False and checkLumis: continue
        if f[-4:] == '.dat' :
            infile.append('file:'+filedir+'/'+f)
process.source = cms.Source('NewEventStreamFileReader',
    fileNames = infile
)


process.options = cms.untracked.PSet(
#    FailPath = cms.untracked.vstring(),
    IgnoreCompletely = cms.untracked.vstring(),
    Rethrow = cms.untracked.vstring(),
#    SkipEvent = cms.untracked.vstring(),
    accelerators = cms.untracked.vstring('*'),
    allowUnscheduled = cms.obsolete.untracked.bool,
    canDeleteEarly = cms.untracked.vstring(),
    deleteNonConsumedUnscheduledModules = cms.untracked.bool(True),
    dumpOptions = cms.untracked.bool(False),
    emptyRunLumiMode = cms.obsolete.untracked.string,
    eventSetup = cms.untracked.PSet(
        forceNumberOfConcurrentIOVs = cms.untracked.PSet(
            allowAnyLabel_=cms.required.untracked.uint32
        ),
        numberOfConcurrentIOVs = cms.untracked.uint32(0)
    ),
    fileMode = cms.untracked.string('FULLMERGE'),
    forceEventSetupCacheClearOnNewRun = cms.untracked.bool(False),
    holdsReferencesToDeleteEarly = cms.untracked.VPSet(),
    makeTriggerResults = cms.obsolete.untracked.bool,
    modulesToIgnoreForDeleteEarly = cms.untracked.vstring(),
    numberOfConcurrentLuminosityBlocks = cms.untracked.uint32(0),
    numberOfConcurrentRuns = cms.untracked.uint32(1),
    numberOfStreams = cms.untracked.uint32(0),
    numberOfThreads = cms.untracked.uint32(1),
    printDependencies = cms.untracked.bool(False),
    sizeOfStackForThreadsInKB = cms.optional.untracked.uint32,
    throwIfIllegalParameter = cms.untracked.bool(True),
    wantSummary = cms.untracked.bool(False)
)

# Production Info
process.configurationMetadata = cms.untracked.PSet(
    annotation = cms.untracked.string('l1Ntuple nevts:100'),
    name = cms.untracked.string('Applications'),
    version = cms.untracked.string('$Revision: 1.19 $')
)

# Output definition
from Configuration.Applications.ConfigBuilder import MassReplaceInputTag

# Additional output definition

# Path and EndPath definitions
process.raw2digi_step = cms.Path(process.RawToDigi)
process.endjob_step = cms.EndPath(process.endOfProcess)

# Schedule definition
process.schedule = cms.Schedule(process.raw2digi_step, process.endjob_step)


from PhysicsTools.PatAlgos.tools.helpers import associatePatAlgosToolsTask
associatePatAlgosToolsTask(process)

# customisation of the process.

# Automatic addition of the customisation function from L1Trigger.Configuration.customiseReEmul
from L1Trigger.Configuration.customiseReEmul import L1TReEmulFromRAW 

#call to customisation function L1TReEmulFromRAW imported from L1Trigger.Configuration.customiseReEmul
process = L1TReEmulFromRAW(process)

# Automatic addition of the customisation function from L1Trigger.L1TNtuples.customiseL1Ntuple
from L1Trigger.L1TNtuples.customiseL1Ntuple import L1NtupleRAWEMU 

#call to customisation function L1NtupleRAWEMU imported from L1Trigger.L1TNtuples.customiseL1Ntuple
process = L1NtupleRAWEMU(process)

# add hcal calibrations
from L1Trigger.Configuration.customiseReEmul import L1TReEmulFromRAWsimHcalTP
process = L1TReEmulFromRAWsimHcalTP(process) 

# Automatic addition of the customisation function from L1Trigger.Configuration.customiseSettings
from L1Trigger.Configuration.customiseSettings import L1TSettingsToCaloParams_2018_v1_4_1 

#call to customisation function L1TSettingsToCaloParams_2018_v1_4_1 imported from L1Trigger.Configuration.customiseSettings
process = L1TSettingsToCaloParams_2018_v1_4_1(process)

# Automatic addition of the customisation function from L1Trigger.Configuration.customiseUtils
from L1Trigger.Configuration.customiseUtils import L1TGlobalMenuXML 

#call to customisation function L1TGlobalMenuXML imported from L1Trigger.Configuration.customiseUtils
process = L1TGlobalMenuXML(process)

# End of customisation functions


# Customisation from command line

# Add early deletion of temporary data products to reduce peak memory need
from Configuration.StandardSequences.earlyDeleteSettings_cff import customiseEarlyDelete
process = customiseEarlyDelete(process)
# End adding early deletion

process.load('HeavyIonsAnalysis.EventAnalysis.hltanalysis_cfi')
process.load('HeavyIonsAnalysis.EventAnalysis.hievtanalyzer_data_cfi')
process.load('HeavyIonsAnalysis.EventAnalysis.hltanalysis_cfi')
process.load('HeavyIonsAnalysis.EventAnalysis.skimanalysis_cfi')
process.load('HeavyIonsAnalysis.EventAnalysis.hltobject_cfi')


# ======================================================================
# ======================== add in the emulator =========================
# unpacked etsums
process.l1UpgradeTree.sumZDCTag = cms.untracked.InputTag("gtStage2Digis","EtSumZDC") 
process.l1UpgradeTree.sumZDCToken = cms.untracked.InputTag("gtStage2Digis","EtSumZDC")

# l1 emulator sums
process.l1UpgradeEmuTree.sumZDCTag = cms.untracked.InputTag("etSumZdcProducer")
process.l1UpgradeEmuTree.sumZDCToken = cms.untracked.InputTag("etSumZdcProducer")

# do not change these settings
process.etSumZdcProducer = cms.EDProducer('L1TZDCProducer',
                                          hcalTPDigis = cms.InputTag("simHcalTriggerPrimitiveDigis"),
#                                          hcalTPDigis = cms.InputTag("hcalDigis"),
                                          bxFirst = cms.int32(-2),
                                          bxLast = cms.int32(3)
)

#Via Hannah, for the simHcal collection
process.simHcalTriggerPrimitiveDigis.inputLabel = cms.VInputTag("hcalDigis", "hcalDigis:ZDC")
process.simHcalTriggerPrimitiveDigis.inputUpgradeLabel = cms.VInputTag("hcalDigis", "hcalDigis:ZDC")


process.etSumZdc = cms.Path(process.etSumZdcProducer)
process.schedule.append(process.etSumZdc)

process.compare = cms.EDAnalyzer("CompareTP",
                                 triggerPrimitives=cms.InputTag("hcalDigis"),
                                 emulTriggerPrimitives=cms.InputTag("simHcalTriggerPrimitiveDigis"),
                                 swapIphi=cms.bool(False),
                                 printSwaps=cms.untracked.bool(False),
                                 swapIeta=cms.bool(False))


#======================================================================
process.zdcrecoRun3 = cms.EDProducer('ZdcHitReconstructor_Run3')
process.zdcrecoRun3.skipRPD = cms.bool(True)
if ZdcEnergyMethod=="TemplateFit" :
    process.zdcrecoRun3.correctionMethodHAD = cms.int32(1)
    process.zdcrecoRun3.correctionMethodEM = cms.int32(1)
if ZdcEnergyMethod=="Trigger" :
    process.zdcrecoRun3.correctionMethodHAD = cms.int32(0)
    process.zdcrecoRun3.correctionMethodEM = cms.int32(0)
    process.zdcrecoRun3.ootpuRatioHAD = cms.double(-1) # Any value less than 0 means the ootpuFrac is always used
    process.zdcrecoRun3.ootpuRatioEM = cms.double(-1) # Otherwise if Ts0/Ts1 > ootpuRatio, ootpuFrac is used
    process.zdcrecoRun3.ootpuFracHAD = cms.double(51.2/256.0)
    process.zdcrecoRun3.ootpuFracEM = cms.double(51.2/256.0)
if ZdcEnergyMethod=="OldMethod" :
    process.zdcrecoRun3.correctionMethodHAD = cms.int32(0)
    process.zdcrecoRun3.correctionMethodEM = cms.int32(0)
    process.zdcrecoRun3.ootpuRatioHAD = cms.double(-1)
    process.zdcrecoRun3.ootpuRatioEM = cms.double(-1)
    process.zdcrecoRun3.ootpuFracHAD = cms.double(1.0)
    process.zdcrecoRun3.ootpuFracEM = cms.double(1.0)






import HLTrigger.HLTfilters.hltHighLevel_cfi
process.hltSelect = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
# process.hltSelect.HLTPaths = ["HLT_HIUPC_ZDC1nOR_SinglePixelTrackLowPt_MaxPixelCluster400_v*", ]
# process.hltSelect.HLTPaths = ["HLT_HIMinimumBias*", ]
process.hltSelect.HLTPaths = [TriggerType]
# process.hltSelect.andOr = cms.bool(True)
# process.hltSelect.throw = cms.bool(False)



process.load('HeavyIonsAnalysis.ZDCAnalysis.ZDCRecHitAnalyzerHC_cfi')
process.zdcanalyzer.ZDCRecHitSource = cms.InputTag("zdcrecoRun3")
process.zdcanalyzer.ZDCDigiSource    = cms.InputTag('hcalDigis', 'ZDC')
process.zdcanalyzer.doZdcRecHits = cms.bool(True)
process.zdcanalyzer.doZdcDigis = cms.bool(True)
process.zdcanalyzer.skipRPD = cms.bool(True)  # also skip RPD channels in the analyzer
process.zdcanalyzer.doHardcodedRecHitsRPD = cms.bool(False) # False to save space
process.zdcanalyzer.doHardcodedDigisRPD = cms.bool(False) # False to save space

# # Uncomment if you want to used non hardcoded ZdcRecHitAnalyzer

# process.load('HeavyIonsAnalysis.ZDCAnalysis.ZDCRecHitAnalyzer_cfi')
# process.zdcanalyzer.ZDCRecHitSource = cms.InputTag("zdcrecoRun3")
# process.zdcanalyzer.ZDCDigiSource    = cms.InputTag('hcalDigis', 'ZDC')
# process.zdcanalyzer.doZdcRecHits = cms.bool(True)
# process.zdcanalyzer.doZdcDigis = cms.bool(True)
# process.zdcanalyzer.skipRPD = cms.bool(True)  # also skip RPD channels in the analyzer


# # Uncomment if you want to include Trigger Energy as the AuxZDCRecHitSource
# # Also need to uncomment process.zdcrecoRun3Trigger in process.recoPathZDC

process.zdcrecoRun3Trigger = process.zdcrecoRun3.clone()
process.zdcrecoRun3Trigger.correctionMethodHAD = cms.int32(0)
process.zdcrecoRun3Trigger.correctionMethodEM = cms.int32(0)
process.zdcrecoRun3Trigger.ootpuRatioHAD = cms.double(-1)
process.zdcrecoRun3Trigger.ootpuRatioEM = cms.double(-1)
process.zdcrecoRun3Trigger.ootpuFracHAD = cms.double(97.0/256.0)
process.zdcrecoRun3Trigger.ootpuFracEM = cms.double(97.0/256.0)

process.zdcanalyzer.AuxZDCRecHitSource = cms.InputTag("zdcrecoRun3Trigger")
process.zdcanalyzer.doAuxZdcRecHits = cms.bool(True)

process.load("RecoLocalCalo.HcalRecAlgos.hcalRecAlgoESProd_cfi")




process.recoPathZDC = cms.Path(
    process.hltanalysis +
    process.zdcrecoRun3 +
    process.zdcrecoRun3Trigger +
    process.zdcanalyzer
)

process.schedule.append(process.recoPathZDC)


# input tag replacement needed for raw prime data
#MassReplaceInputTag(process, new="rawPrimeDataRepacker", old="rawDataCollector")

#input tag needed for regular HI data
MassReplaceInputTag(process, new="rawDataRepacker", old="rawDataCollector")

