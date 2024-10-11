import FWCore.ParameterSet.Config as cms

from Configuration.AlCa.GlobalTag import GlobalTag
from Configuration.StandardSequences.Eras import eras

RUN = '384797'

from Configuration.Eras.Era_Run3_pp_on_PbPb_cff import Run3_pp_on_PbPb
process = cms.Process('RAW2DIGI', Run3_pp_on_PbPb)

# needed for CMSSW14
process.add_(cms.Service("AdaptorConfig", native=cms.untracked.vstring("root")))


process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag = GlobalTag(process.GlobalTag, '141X_dataRun3_Prompt_Candidate_2024_10_08_09_42_50', '')


process.maxEvents = cms.untracked.PSet(input=cms.untracked.int32(1))

# try for now with pp data from 2024 with ZDC included in global
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
        #'/store/data/Run2024G/ZeroBias/RAW/v1/000/384/797/00000/984ca912-94be-4de8-8b40-c99f13865a00.root',
        '/store/hidata/HIRun2023A/HIZeroBias2/RAW/v1/000/375/694/00000/2e63d9bc-bf96-4a99-b607-755d52d7fe93.root',
    ),
)

process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_cff')
process.load("Configuration.StandardSequences.RawToDigi_Data_cff")
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.load('SimCalorimetry.HcalTrigPrimProducers.hcaltpdigi_cff')
process.load("SimCalorimetry.Configuration.hcalDigiSequence_cff")


process.hcalDigis.silent = cms.untracked.bool(False)



process.TFileService = cms.Service("TFileService",
                                   closeFileFast=cms.untracked.bool(True),
                                   fileName=cms.string('analyze_ppData2024.root'))


process.simHcalTriggerPrimitiveDigis.inputLabel = cms.VInputTag("hcalDigis", "hcalDigis:ZDC")
process.simHcalTriggerPrimitiveDigis.inputUpgradeLabel = cms.VInputTag("hcalDigis", "hcalDigis:ZDC")


process.compare = cms.EDAnalyzer("CompareTP",
                                 triggerPrimitives=cms.InputTag("hcalDigis"),
                                 emulTriggerPrimitives=cms.InputTag("simHcalTriggerPrimitiveDigis"),
                                 swapIphi=cms.bool(False),
                                 printSwaps=cms.untracked.bool(False),
                                 swapIeta=cms.bool(False))



process.p = cms.Path(
    process.hcalDigis *
    process.simHcalTriggerPrimitiveDigis *
    process.compare)

from Configuration.Applications.ConfigBuilder import MassReplaceInputTag
MassReplaceInputTag(process, new="rawDataRepacker", old="rawDataCollector")