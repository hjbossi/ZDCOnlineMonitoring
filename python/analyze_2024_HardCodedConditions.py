import FWCore.ParameterSet.Config as cms

from Configuration.AlCa.GlobalTag import GlobalTag
from Configuration.StandardSequences.Eras import eras

RUN = '384797'
GT = '141X_dataRun3_Prompt_Candidate_2024_10_08_09_42_50'

from Configuration.Eras.Era_Run3_pp_on_PbPb_cff import Run3_pp_on_PbPb
process = cms.Process('RAW2DIGI', Run3_pp_on_PbPb)


process.add_(cms.Service("AdaptorConfig", native=cms.untracked.vstring("root")))


#process = cms.Process('PLOT', eras.Run3)

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
# syntax for override of a single condition
#override = 'HcalElectronicsMap_2018_v3.0_data,HcalElectronicsMapRcd,frontier://FrontierProd/CMS_CONDITIONS'
#process.GlobalTag = GlobalTag(process.GlobalTag, GT, override)

# process.GlobalTag = GlobalTag(process.GlobalTag, '140X_dataRun3_Prompt_frozen_v1', '')
process.GlobalTag = GlobalTag(process.GlobalTag, GT, '')

process.maxEvents = cms.untracked.PSet(input=cms.untracked.int32(1000))

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
        '/store/data/Run2024G/ZeroBias/RAW/v1/000/384/797/00000/984ca912-94be-4de8-8b40-c99f13865a00.root',
    ),
)

process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_cff')
process.load('Configuration.StandardSequences.RawToDigi_DataMapper_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.load("SimCalorimetry.Configuration.hcalDigiSequence_cff")
process.load('SimCalorimetry.HcalTrigPrimProducers.hcaltpdigi_cff')



CONDDIR="ZDC_conditions_2024_Updated_noRPD"

process.es_prefer = cms.ESPrefer('HcalTextCalibrations','es_ascii')
process.es_ascii = cms.ESSource('HcalTextCalibrations',
   input = cms.VPSet(
      cms.PSet(
         object = cms.string('ChannelQuality'),
         file   = cms.FileInPath(CONDDIR+'/ChannelQuality_ZDC.txt')
      ),
      cms.PSet(
         object = cms.string('Pedestals'),
         file   = cms.FileInPath(CONDDIR+'/Pedestals_ZDC.txt')
      ),
      cms.PSet(
         object = cms.string('EffectivePedestals'),
         file   = cms.FileInPath(CONDDIR+'/EffectivePedestals_ZDC.txt')
      ),
      cms.PSet(
         object = cms.string('Gains'),
         file   = cms.FileInPath(CONDDIR+'/Gains_ZDC_NonZeroRPD.txt')
      ),
      cms.PSet(
         object = cms.string('RespCorrs'),
         file   = cms.FileInPath(CONDDIR+'/RespCorrs_ZDC.txt')
      ),
      cms.PSet(
        object = cms.string('ElectronicsMap'),
        file   = cms.FileInPath(CONDDIR+'/ElectronicsMap_ZDC.txt')
      ),
      cms.PSet(
        object = cms.string('TPChannelParameters'),
        file   = cms.FileInPath(CONDDIR+'/TPChannelParameters_ZDC.txt')
      ),
      cms.PSet(
        object = cms.string('LUTCorrs'),
        file   = cms.FileInPath(CONDDIR+'/LUTCorrs_ZDC.txt')
      ),
      cms.PSet(
        object = cms.string('QIEData'),
	file   = cms.FileInPath(CONDDIR+'/QIEData_ZDC_AVG.txt')
      ),
      cms.PSet(
        object = cms.string('QIETypes'),
        file   = cms.FileInPath(CONDDIR+'/QIETypes_ZDC.txt')
      ),
      cms.PSet(
        object = cms.string('LutMetadata'),
	file   = cms.FileInPath(CONDDIR+'/LutMetadata_ZDC.txt')
      ),
   cms.PSet(
	   object = cms.string('TimeCorrs'),
      file   = cms.FileInPath(CONDDIR+'/TimeCorrs_ZDC.txt')
   ),
      cms.PSet(
          object = cms.string('LongRecoParams'),
          file   = cms.FileInPath(CONDDIR+'/LongRecoParams.txt')
   ),
   )

)
       


process.TFileService = cms.Service("TFileService",
                                   closeFileFast=cms.untracked.bool(True),
                                   fileName=cms.string('analyze_' + RUN + '.root'))


process.simHcalTriggerPrimitiveDigis.inputLabel = cms.VInputTag("hcalDigis", "hcalDigis:ZDC")
process.simHcalTriggerPrimitiveDigis.inputUpgradeLabel = cms.VInputTag("hcalDigis", "hcalDigis:ZDC")

process.hcalDigis.silent = cms.untracked.bool(False)


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
