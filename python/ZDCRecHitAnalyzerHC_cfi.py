import FWCore.ParameterSet.Config as cms

zdcanalyzer = cms.EDAnalyzer(
   "ZDCRecHitAnalyzerHC",
   ZDCSource    = cms.InputTag('zdcrecoRun3'),
   ZDCDigiSource    = cms.InputTag('hcalDigis', 'ZDC'),
   doZdcRecHits = cms.bool(True),
   doZdcDigis = cms.bool(True),
   skipRPD = cms.bool(True),
   doHardcodedRecHitsRPD = cms.bool(True),
   doHardcodedDigisRPD = cms.bool(True)
 ) # zdcreco

