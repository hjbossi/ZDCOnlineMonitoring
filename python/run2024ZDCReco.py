import FWCore.ParameterSet.Config as cms

from Configuration.StandardSequences.Eras import eras
from Configuration.Eras.Era_Run3_2023_ZDC_cff import Run3_2023_ZDC

process = cms.Process('TestZdcRecHit', Run3_2023_ZDC)

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('HeterogeneousCore.CUDACore.ProcessAcceleratorCUDA_cfi')

process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, '141X_dataRun3_Prompt_frozen_v3', '')

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(100)
)

# needed to supress error from cmssw 14
process.add_(cms.Service("AdaptorConfig", native=cms.untracked.vstring("root")))

#-----------------------------------------
# INPUT
#-----------------------------------------

process.source = cms.Source("PoolSource",
  fileNames = cms.untracked.vstring('/store/hidata/HIRun2023A/HIForward0/AOD/16Jan2024-v1/2810000/14f851d2-7c11-4ac4-9650-3428cc184582.root'),
  
  # removing old zdcreco
  inputCommands = cms.untracked.vstring('keep *', 
      'drop *_zdcreco_*_*')
)

#-----------------------------------------
# CMSSW/Hcal non-DQM Related Module import
#-----------------------------------------

process.load('Configuration.StandardSequences.GeometryRecoDB_cff')

# -----------------------------------------
# CMSSW/Hcal ZDC Reconstructor
# -----------------------------------------


process.load("RecoLocalCalo.HcalRecProducers.zdcrecoRun3_cfi")
process.zdcrecoRun3.skipRPD = cms.bool(True) #skip RPD channels due to geometry updates



process.load("RecoLocalCalo.HcalRecAlgos.hcalRecAlgoESProd_cfi")



process.load('HeavyIonsAnalysis.ZDCAnalysis.ZDCRecHitAnalyzer_cfi')
process.zdcanalyzer.ZDCSource = cms.InputTag("zdcrecoRun3")
process.zdcanalyzer.skipRPD = cms.bool(True)  # also skip RPD channels in the analyzer



process.out = cms.OutputModule("PoolOutputModule",
    fileName = cms.untracked.string("ZdcRecHitEventContent.root"),
    outputCommands = cms.untracked.vstring('drop *', 
        'keep doubles_zdcdigi_*_*', 
        'keep ZDCRecHitsSorted_zdc*_*_*')
)

process.TFileService = cms.Service("TFileService",
		fileName = cms.string("RecHitZdcAnalyzer.root")
		)


process.finalize = cms.EndPath(process.out)

#-----------------------------------------
# gpu test
#-----------------------------------------


process.recoPathZDC = cms.Path(
    process.zdcrecoRun3
    + process.zdcanalyzer
)

#---------------



#---------------

process.schedule = cms.Schedule(
    process.recoPathZDC,
    process.finalize
)