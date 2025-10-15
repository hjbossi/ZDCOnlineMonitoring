# L1Ntuple for ZDC studies with 2023 data
# Hannah Bossi, <hannah.bossi@cern.ch>
# 9/17/2023
import FWCore.ParameterSet.Config as cms
import os
import sys

#from Configuration.Eras.Era_Run3_pp_on_PbPb_cff import Run3_pp_on_PbPb
from Configuration.Eras.Era_Run3_pp_on_PbPb_2025_cff import Run3_pp_on_PbPb_2025
process = cms.Process('RAW2DIGI', Run3_pp_on_PbPb_2025)

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_cff')
process.load('Configuration.StandardSequences.RawToDigi_DataMapper_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')


from Configuration.AlCa.GlobalTag import GlobalTag
# use the prompt queue for now, will need to update when the full GT becomes available
process.GlobalTag = GlobalTag(process.GlobalTag, '151X_dataRun3_Prompt_Queue', '')


# needed to supress error from cmssw 14
process.add_(cms.Service("AdaptorConfig", native=cms.untracked.vstring("root")))

# To change the number of events, change this part
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(1000),
    output = cms.optional.untracked.allowed(cms.int32,cms.PSet)
)

# Input source if not a streamer file
# process.source = cms.Source("PoolSource",
#     fileNames = cms.untracked.vstring(
#         '/store/hidata/OORun2025/IonPhysics0/RAW/v1/000/394/175/00000/0006d45f-5091-40e4-ab78-e6595bb89c72.root'
#     )
# )

# input source if a streamer file
filedir = '/eos/cms/store/t0streamer/Data/PhysicsCommissioning/000/398/000'
print(filedir)
infile    = cms.untracked.vstring()
for f in reversed(os.listdir(filedir)):
   if f[-4:] == '.dat' :
       infile.append('file:'+filedir+'/'+f)
print(infile)



process.source = cms.Source("NewEventStreamFileReader",
                           fileNames = infile,
)

from CondCore.CondDB.CondDB_cfi import *
process.es_pool = cms.ESSource("PoolDBESSource",
    # timetype = cms.string('runnumber'),
    toGet = cms.VPSet(
        cms.PSet(
            record = cms.string("HcalElectronicsMapRcd"),
            tag = cms.string("HcalElectronicsMap_2021_v2.0_data")
        )
    ),
    connect = cms.string('frontier://FrontierProd/CMS_CONDITIONS')
        # authenticationMethod = cms.untracked.uint32(1)
    )

process.es_prefer = cms.ESPrefer('HcalTextCalibrations', 'es_ascii')
process.es_ascii = cms.ESSource(
    'HcalTextCalibrations',
    input = cms.VPSet(
        cms.PSet(
            object = cms.string('ElectronicsMap'),
            file = cms.FileInPath("emap_2025_full.txt")

             )
        )
    )

process.options = cms.untracked.PSet(
    IgnoreCompletely = cms.untracked.vstring(),
    Rethrow = cms.untracked.vstring(),
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

# Add early deletion of temporary data products to reduce peak memory need
from Configuration.StandardSequences.earlyDeleteSettings_cff import customiseEarlyDelete
process = customiseEarlyDelete(process)
# End adding early deletion

# root output
process.TFileService = cms.Service("TFileService",
    fileName = cms.string("ZDCAnalyzer.root"))

#########################
# ZDC RecHit Producer && Analyzer
#########################
# to prevent crash related to HcalSeverityLevelComputerRcd record
process.load("RecoLocalCalo.HcalRecAlgos.hcalRecAlgoESProd_cfi")
process.load('HeavyIonsAnalysis.ZDCAnalysis.ZDCAnalyzersPbPb_cff')
process.load('HeavyIonsAnalysis.ZDCAnalysis.FSCAnalyzers_cff')
process.zdcreco_step = cms.Path(process.zdcrecoRun3)
process.zdcanalyzer_step = cms.Path(process.zdcanalyzer)
process.schedule.append(process.zdcreco_step)
process.schedule.append(process.zdcanalyzer_step)
process.fsccanalyzer_step = cms.Path(process.fscanalyzer)
process.schedule.append(process.fsccanalyzer_step )
#=======================================================================


# needed for HIN data, but not needed for this commissioning set
#MassReplaceInputTag(process, new="rawDataRepacker", old="rawDataCollector")
